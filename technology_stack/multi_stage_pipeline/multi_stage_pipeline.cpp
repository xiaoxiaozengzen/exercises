#include <cstdint>
#include <exception>
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
#include <functional>

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
            std::unique_lock<std::mutex> lk(mutex_);
            cvStage1_.wait(lk, [this]() {
                return stage1Queue_.size() < queue1Size_ || stopped_;
            });
            if(stopped_) {
                return false;
            }
            stage1Queue_.push_back(frame);
            cvStage1_.notify_one();
        }
        return true;
    }
private:

    void RunStage1() {
        while (true) {
            DataFramePtr frameToProcess = nullptr;
            {
                std::unique_lock<std::mutex> lk(mutex_);
                cvStage1_.wait(lk, [this]() {
                    return !stage1Queue_.empty() || stopped_;
                });
                if(stopped_ && stage1Queue_.empty()) {
                    return;
                }
                frameToProcess = stage1Queue_.front();
                stage1Queue_.pop_front();
            }

            stage1Func_(frameToProcess);
            {
                std::unique_lock<std::mutex> lk(mutex_);
                cvStage2_.wait(lk, [this]() {
                    return stage2Queue_.size() < queue2Size_ || stopped_;
                });
                if(stopped_) {
                    return;
                }
                stage2Queue_.push_back(frameToProcess);
                cvStage2_.notify_one();
            }
        }
    }

    void RunStage2() {
        while(true) {
            DataFramePtr frameToProcess = nullptr;
            {
                std::unique_lock<std::mutex> lk(mutex_);
                cvStage2_.wait(lk, [this]() {
                    return !stage2Queue_.empty() || stopped_;
                });
                if(stopped_ && stage2Queue_.empty()) {
                    return;
                }
                frameToProcess = stage2Queue_.front();
                stage2Queue_.pop_front();
            }

            stage2Func_(frameToProcess);
        }
    }

    

private:
    std::atomic<bool> stopped_{false};

    Mode mode_;
    std::size_t queue1Size_;
    std::size_t queue2Size_;

    std::mutex mutex_;
    std::condition_variable cvStage1_;
    std::condition_variable cvStage2_;
    std::deque<DataFramePtr> stage1Queue_;
    std::deque<DataFramePtr> stage2Queue_;

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
    static std::uint64_t frame_count = 0;
    frame_count++;
    frame->index1 = frame_count;
    global_log << "Stage 1 processed frame with index1: " + std::to_string(frame->index1.load());
    frame->data += "stage1_" + std::to_string(frame->index1) + "_";
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

void stage2Function(DataFramePtr frame, bool do_timeout) {
    if(!frame) {
        global_log << "Received null frame in stage 2.";
        return;
    }
    static std::uint64_t frame_count = 0;
    frame_count++;
    frame->index2 = frame_count;
    global_log << "Stage 2 processed frame with index2: " + std::to_string(frame->index2.load());
    frame->data += "stage2_" + std::to_string(frame->index2) + "_";
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    if(do_timeout) {
        if(frame_count % 8 == 0) {
            std::cerr << "fun2 sleep" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    if(frame->index1 != frame->index2) {
        std::terminate();
    }

    global_log << "Final frame data: " + frame->data;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << " <mode> <timeout>" << std::endl;
        std::cout << "mode: 0 for Serial, 1 for Parallel" << std::endl;
        std::cout << "timeout: 0 is true, other is false" << std::endl;
        return 1;
    }

    Mode mode = (std::atoi(argv[1]) == 0) ? Mode::Serial : Mode::Parallel;
    bool is_timeout = (std::atoi(argv[2]) == 0) ? true : false;
    std::cerr << "--- is_timeout: " << (is_timeout?"True":"False") << std::endl;


    Rate rate(10.0); // 10 Hz
    static std::uint64_t frameIndex = 0;

    TwoStagePipeline pipeline(mode, 2);
    pipeline.setStage1Function(stage1Function);
    std::function<void(DataFramePtr frame)> new_stage2 = std::bind(stage2Function, std::placeholders::_1, is_timeout);
    pipeline.setStage2Function(new_stage2);
    pipeline.Start();

    
    for (int i = 0; i < 20; ++i) {
        frameIndex++;
        global_log << "start frame " + std::to_string(frameIndex);

        DataFramePtr frame = std::make_shared<DataFrame>();
        if (!pipeline.Dispatch(frame)) {
            global_log << "Failed to dispatch frame: " + std::to_string(i);
        }
        rate.sleep();
        global_log << "end frame " + std::to_string(frameIndex);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    pipeline.Stop();
    return 0;
}