// ping_pong_buffer_demo.cpp
//
// 乒乓 buffer(双缓冲 / double buffering)示例 —— 满/空双槽 + 长期运行版。
//
// 与 multi_stage_pipeline.cpp 的区别:
//   - 这里只有【两块固定 buffer】,原地复用、零分配;pipeline 的队列传的是每帧
//     新建的 shared_ptr 指针(动态分配、对象流动)。二者内存模型完全不同。
//   - 同步用"满/空交接"(两个信号量)而非屏障:线程只在拿不到所需状态的 buffer
//     时才阻塞,快的一方能提前填好另一块,用第二块吸收耗时抖动;不像屏障那样
//     每相位强制双方碰面(严格 lockstep)。
//
// 编译: g++ -std=c++17 -pthread -O2 -o ping_pong ping_pong_buffer_demo.cpp

#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

using Clock = std::chrono::steady_clock;
static Clock::time_point g_start;

static long Ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - g_start).count();
}

// 线程安全日志类:每次 operator<< 输出一整行(带相对时间戳),内部用互斥量
// 避免多线程日志交错。风格参考 multi_stage_pipeline.cpp 的 LogLine。
class LogLine {
public:
    void operator<<(const std::string& message) { Emit(message); }
    void operator<<(const char* message) { Emit(message); }
    void operator<<(int message) { Emit(std::to_string(message)); }

private:
    std::string GetTime() {
        return "[" + std::to_string(Ms()) + "ms]";
    }

    void Emit(const std::string& message) {
        std::stringstream ss;
        ss << GetTime() << "\t" << message << "\n";
        std::lock_guard<std::mutex> lk(outMutex_);
        std::cout << ss.str() << std::flush;
    }

    std::mutex outMutex_;
};

static LogLine global_log;

// 计数信号量(C++17 无 std::counting_semaphore,手写一个)。
// 支持 Abort():关闭时唤醒所有等待者并让后续 Acquire 立即失败,避免死锁。
class Semaphore {
public:
    explicit Semaphore(int initial) : count_(initial) {}

    // 返回 false 表示已被 Abort(调用者应退出循环)。
    bool Acquire() {
        std::unique_lock<std::mutex> lk(mtx_);
        cv_.wait(lk, [this]() { return count_ > 0 || aborted_; });
        if (aborted_) return false;
        --count_;
        return true;
    }

    void Release() {
        std::lock_guard<std::mutex> lk(mtx_);
        ++count_;
        cv_.notify_one();
    }

    void Abort() {
        std::lock_guard<std::mutex> lk(mtx_);
        aborted_ = true;
        cv_.notify_all();
    }

private:
    std::mutex mtx_;
    std::condition_variable cv_;
    int count_;
    bool aborted_ = false;
};

// ---------- 乒乓(双缓冲)封装:满/空双槽 + 长期运行 ----------
// 持有两块固定 buffer,用 emptySem_/fullSem_ 做满空交接:
//   生产者: 取一块"空"的 -> 写 -> 置"满"
//   消费者: 取一块"满"的 -> 读 -> 置"空"
// 生产/消费都按 0,1,0,1 轮转,配合信号量计数,保证 FIFO 且在途至多 2 块。
template <typename Buffer>
class PingPongBuffer {
public:
    using ProduceFn = std::function<void(Buffer&, std::uint64_t)>;       // (目标块, 帧号)
    using ConsumeFn = std::function<void(const Buffer&, std::uint64_t)>; // (来源块, 帧号)

    PingPongBuffer(ProduceFn produce, ConsumeFn consume)
        : produce_(std::move(produce)),
          consume_(std::move(consume)),
          emptySem_(kSlots),  // 初始两块都"空"
          fullSem_(0) {}      // 初始没有"满"的

    ~PingPongBuffer() { Stop(); }

    PingPongBuffer(const PingPongBuffer&) = delete;
    PingPongBuffer& operator=(const PingPongBuffer&) = delete;

    void Start() {
        running_.store(true);
        producerThread_ = std::thread(&PingPongBuffer::ProducerLoop, this);
        consumerThread_ = std::thread(&PingPongBuffer::ConsumerLoop, this);
    }

    // 幂等:重复调用只生效一次(参考 multi_stage_pipeline.cpp 的 Stop)。
    void Stop() {
        if (stopped_.exchange(true)) return;
        running_.store(false);
        emptySem_.Abort();  // 释放阻塞在 Acquire 上的线程,否则会死锁
        fullSem_.Abort();
        if (producerThread_.joinable()) producerThread_.join();
        if (consumerThread_.joinable()) consumerThread_.join();
    }

    std::uint64_t ProducedCount() const { return producedCount_.load(); }
    std::uint64_t ConsumedCount() const { return consumedCount_.load(); }

private:
    static constexpr int kSlots = 2;

    // 生产者:取空块 -> 写 -> 置满。局部写索引 w 在 0/1 间翻转。
    void ProducerLoop() {
        int w = 0;
        while (running_.load()) {
            if (!emptySem_.Acquire()) break;  // 等一块"空"buffer;被 Abort 则退出
            if (!running_.load()) break;
            std::uint64_t frame = producedCount_.load();
            global_log << ("producer\tproduce frame " + std::to_string(frame) + " -> buf[" + std::to_string(w) + "]");
            produce_(bufs_[w], frame);
            producedCount_.fetch_add(1);
            w ^= 1;
            fullSem_.Release();               // 这块变"满",通知消费者
        }
    }

    // 消费者:取满块 -> 读 -> 置空。局部读索引 r 同样翻转。
    void ConsumerLoop() {
        int r = 0;
        while (running_.load()) {
            if (!fullSem_.Acquire()) break;   // 等一块"满"buffer
            consume_(bufs_[r], consumedCount_.load());
            consumedCount_.fetch_add(1);
            r ^= 1;
            emptySem_.Release();              // 这块变"空",通知生产者可复用
        }
    }

    ProduceFn produce_;
    ConsumeFn consume_;
    std::array<Buffer, kSlots> bufs_{};  // 仅两块,全程复用,零分配

    Semaphore emptySem_;  // "空"块的数量
    Semaphore fullSem_;   // "满"块的数量
    std::atomic<bool> running_{false};
    std::atomic<bool> stopped_{false};
    std::atomic<std::uint64_t> producedCount_{0};
    std::atomic<std::uint64_t> consumedCount_{0};

    std::thread producerThread_;
    std::thread consumerThread_;
};

// ---------- demo 用的数据与读写实现 ----------
constexpr int kBufElems = 4;                 // 每块 buffer 的元素个数
using Buffer = std::array<int, kBufElems>;   // 一块 buffer

constexpr int kFrames = 6;                   // demo 跑 6 帧后停止
constexpr int kProduceMs = 20;               // 模拟"生产"耗时(如 DMA/采集/上一级计算)
constexpr int kConsumeMs = 40;               // 模拟"消费"耗时(如计算/写出)

static void Produce(Buffer& buf, std::uint64_t frame) {
    for (int i = 0; i < kBufElems; ++i) {
        buf[i] = static_cast<int>(frame) * 100 + i;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(kProduceMs));
}

static void Consume(const Buffer& buf, std::uint64_t frame) {
    long sum = 0;
    for (int v : buf) sum += v;
    std::this_thread::sleep_for(std::chrono::milliseconds(kConsumeMs));
    std::ostringstream ss;
    ss << "consumer\tconsume frame " << frame << " (buf sum=" << sum << ")";
    global_log << ss.str();
}

// ---------- 顺序版本(无双缓冲):每帧先产后消,串行,用作对照 ----------
static void Sequential() {
    Buffer buf{};
    for (int f = 0; f < kFrames; ++f) {
        global_log << ("seq\tproduce frame " + std::to_string(f));
        Produce(buf, f);
        Consume(buf, f);
    }
}

int main() {
    std::cout << "=== Sequential (single buffer, produce-then-consume) ===\n";
    g_start = Clock::now();
    Sequential();
    long seq_ms = Ms();

    std::cout << "\n=== Ping-Pong (double buffer, full/empty handoff, running until kFrames) ===\n";
    g_start = Clock::now();
    PingPongBuffer<Buffer> pp(Produce, Consume);
    pp.Start();
    // 长期运行:等它产出 kFrames 帧后主动停止(实际系统里可由外部事件触发 Stop)。
    while (pp.ProducedCount() < kFrames) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    pp.Stop();  // 置停 + Abort 信号量 + join;析构里还会兜底调用一次(幂等)
    long pp_ms = Ms();

    std::cout << "\n--- timing ---\n";
    std::cout << "sequential total : " << seq_ms << " ms  (~ N*(produce+consume) = "
              << kFrames * (kProduceMs + kConsumeMs) << ")\n";
    std::cout << "ping-pong  total : " << pp_ms << " ms  (~ N*max(produce,consume) + fill/drain), "
              << "produced=" << pp.ProducedCount() << " consumed=" << pp.ConsumedCount() << "\n";
    return 0;
}
