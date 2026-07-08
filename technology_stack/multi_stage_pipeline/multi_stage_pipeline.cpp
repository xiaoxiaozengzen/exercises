#include <cstdint>
#include <iostream>
#include <deque>
#include <ratio>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <utility>
#include <atomic>
#include <chrono>
#include <sstream>
#include <iomanip>

#include "rate.hpp"

class LogLine {
public:
    std::string GetTime() {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::seconds duration_s = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
        std::chrono::nanoseconds duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
        std::stringstream ss;
        ss << "[" << duration_s.count() << "." << std::setw(9) << std::setfill('0') << (duration_ns.count() % 1000000000) << "]";
        std::string timeStr = ss.str();
        return timeStr;
    }

    void operator<<(const std::string& message) {
        std::stringstream ss;
        ss << GetTime() << " " << message;
        std::cout << ss.str() << std::endl;
    }

    void operator<<(const char* message) {
        std::stringstream ss;
        ss << GetTime() << " " << message;
        std::cout << ss.str() << std::endl;
    }

    void operator<<(const int& message) {
        std::stringstream ss;
        ss << GetTime() << " " << message;
        std::cout << ss.str() << std::endl;
    }

    void operator<<(const std::atomic<int>& message) {
        std::stringstream ss;
        ss << GetTime() << " " << message.load();
        std::cout << ss.str() << std::endl;
    }
};

LogLine global_log;

struct DataFrame {
    std::atomic<std::uint64_t> index1{0};
    std::atomic<std::uint64_t> index2{0};
    std::string data = "";
};
using DataFramePtr = std::shared_ptr<DataFrame>;

enum class Mode {
    Parallel,
    Serial
};

class TwoStagePipeline {
public:
    TwoStagePipeline(Mode mode, std::size_t queueSize)
     :mode_(mode),
      queue1Size_(queueSize),
      queue2Size_(queueSize) {

    }

    ~TwoStagePipeline() {

    }

    TwoStagePipeline(const TwoStagePipeline&) = delete;
    TwoStagePipeline& operator=(const TwoStagePipeline&) = delete;

    void Stop() {
        if(stopped_.exchange(true)) {
            global_log << "Has Stopping pipeline...";
            return;
        }
        global_log << "Stopping pipeline...";
        if (stage1Thread_.joinable()) {
            stage1Thread_.join();
        }
        if (stage2Thread_.joinable()) {
            stage2Thread_.join();
        }
    }

    void setStage1Function(std::function<void(DataFramePtr)> func) {
        stage1Func_ = std::move(func);
    }

    void setStage2Function(std::function<void(DataFramePtr)> func) {
        stage2Func_ = std::move(func);
    }

    void Start() {
        std::cout << "Starting pipeline in " << (mode_ == Mode::Parallel ? "Parallel" : "Serial") << " mode." << std::endl;
        if(!stage1Func_ || !stage2Func_) {
            global_log << "Stage functions are not set, cannot start pipeline.";
            return;
        }

        if (mode_ == Mode::Parallel) {
            stage1Thread_ = std::thread(&TwoStagePipeline::RunStage1, this);
            stage2Thread_ = std::thread(&TwoStagePipeline::RunStage2, this);
        }
    }

    bool Dispatch(DataFramePtr frame) {
        if(stopped_) {
            global_log << "Pipeline has been stopped, cannot do work.";
            return false;
        }
        if (mode_ == Mode::Serial) {
            stage1Func_(frame);
            stage2Func_(frame);
            return true;
        } 

        {
            std::unique_lock<std::mutex> lk(mutex1_);
            cv1_.wait(lk, [this](){
                return !is_1_in_ready_ || stopped_;
            });
            if(stopped_) {
                return false;
            }
            frame1_ = frame;
            is_1_in_ready_ = true;
            cv1_.notify_one();
        }
        return true;
    }
private:

    void RunStage1() {
        DataFramePtr frame;
        while (true) {
            DataFramePtr frame;
            {
                std::unique_lock<std::mutex> lk(mutex1_);
                cv1_.wait(lk, [this](){
                    return is_1_in_ready_ || stopped_;
                });
                frame = frame1_;
                is_1_in_ready_ = false;
                cv1_.notify_one();
            }
            stage1Func_(frame);
            {
                std::unique_lock<std::mutex> lk(mutex2_);
                cv2_.wait(lk, [this](){
                    return !is_2_in_ready_ || stopped_;
                });
                if(stopped_) {
                    return;
                }
                frame2_ = frame;
                is_2_in_ready_ = true;
                cv2_.notify_one();                
            }
        }
    }

    void RunStage2() {
        while(true) {
            DataFramePtr frame;
            {
                std::unique_lock<std::mutex> lk(mutex2_);
                cv2_.wait(lk, [this](){
                    return is_2_in_ready_ || stopped_;
                });
                frame = frame2_;
                is_2_in_ready_ = false;
                cv2_.notify_one();
            }

            stage2Func_(frame);
        }
        
    }

    

private:
    std::atomic<bool> stopped_{false};

    Mode mode_;
    std::size_t queue1Size_;
    std::size_t queue2Size_;

    std::mutex mutex1_;
    std::condition_variable cv1_;
    std::deque<DataFramePtr> queue1_;
    bool is_1_in_ready_ = false;
    DataFramePtr frame1_ = nullptr;

    std::mutex mutex2_;
    std::condition_variable cv2_;
    std::deque<DataFramePtr> queue2_;
    bool is_2_in_ready_ = false;
    DataFramePtr frame2_ = nullptr;

    std::function<void(DataFramePtr)> stage1Func_;
    std::function<void(DataFramePtr)> stage2Func_;

    std::thread stage1Thread_;
    std::thread stage2Thread_;
};

void stage1Function(DataFramePtr frame) {
    if(!frame) {
        global_log << "Received null frame in stage 1.";
        return;
    }
    frame->index1++;
    global_log << "Stage 1 processed frame with index1: " + std::to_string(frame->index1.load());
    frame->data += "stage1_" + std::to_string(frame->index1) + "_";
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

void stage2Function(DataFramePtr frame) {
    if(!frame) {
        global_log << "Received null frame in stage 2.";
        return;
    }
    frame->index2++;
    global_log << "Stage 2 processed frame with index2: " + std::to_string(frame->index2.load());
    frame->data += "stage2_" + std::to_string(frame->index2) + "_";
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    global_log << "Final frame data: " + frame->data;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " <mode>" << std::endl;
        std::cout << "mode: 0 for Serial, 1 for Parallel" << std::endl;
        return 1;
    }

    Mode mode = (std::atoi(argv[1]) == 0) ? Mode::Serial : Mode::Parallel;

    Rate rate(10.0); // 10 Hz
    static std::uint64_t frameIndex = 0;

    TwoStagePipeline pipeline(mode, 2);
    pipeline.setStage1Function(stage1Function);
    pipeline.setStage2Function(stage2Function);
    pipeline.Start();

    for (int i = 0; i < 20; ++i) {
        DataFramePtr frame = std::make_shared<DataFrame>();
        frame->index1 = frameIndex;
        frame->index2 = frameIndex;
        if (!pipeline.Dispatch(frame)) {
            global_log << "Failed to dispatch frame: " + std::to_string(i);
        }
        rate.sleep();
        frameIndex++;
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    pipeline.Stop();
    return 0;
}