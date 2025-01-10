#include <sys/time.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char** argv) {
  if (argc != 2) {
    throw std::runtime_error("using like: ./bin <arg>");
  }

  std::string arg = argv[1];

  if (arg == "1") {
    for (int i = 0; i < 10000000; i++) {
      getppid();
    }
  } else {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  // 1. time_t time(time_t *t)
  time_t t;
  t = time(NULL);
  std::cout << "time(NULL): " << t << " s" << std::endl;

  // 2. clock_t clock(void)
  struct timeval tv;
  int ret = gettimeofday(&tv, NULL);
  if (ret != 0) {
    std::cout << "gettimeofday failed" << std::endl;
  }
  std::cout << "gettimeofday: " << tv.tv_sec << "s " << tv.tv_usec << "us" << std::endl;

  // 3. clock_t times(struct tms *buf)
  // 阻塞是不算作用户cpu或者系统cpu时间的
  long ticks = sysconf(_SC_CLK_TCK);
  std::cout << "sysconf(_SC_CLK_TCK): " << ticks << " ticks per second" << std::endl;
  struct tms tms_value;
  clock_t c = times(&tms_value);
  std::cout << "times: " << c << " ticks" << std::endl;
  // 调用进程到目前为止使用的用户CPU时间
  std::cout << "tms_utime: " << tms_value.tms_utime << " ticks"
            << ", s: " << double(tms_value.tms_utime) / ticks << std::endl;
  // 调用进程到目前为止使用的系统cpu时间
  std::cout << "tms_stime: " << tms_value.tms_stime << " ticks"
            << ", s: " << double(tms_value.tms_stime) / ticks << std::endl;
  // 包含等待所有子进程的用户cpu时间
  std::cout << "tms_cutime: " << tms_value.tms_cutime << " ticks"
            << ", s: " << double(tms_value.tms_cutime) / ticks << std::endl;
  // 包含等待所有子进程的系统cpu时间
  std::cout << "tms_cstime: " << tms_value.tms_cstime << " ticks"
            << ", s: " << double(tms_value.tms_cstime) / ticks << std::endl;

  // 4. clock
  // returns total CPU time used by calling process measured in CLOCKS_PER_SEC, or -1 on error
  clock_t clocktime;
  std::cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << std::endl;
  clocktime = clock();
  std::cout << "clocktime: " << clocktime << ", s: " << double(clocktime) / CLOCKS_PER_SEC
            << std::endl;

  // 5.clock_gettime
  // CLOCK_REALTIME：为实际的时间。可以使用命令（date）或是系统调用去修改。如果使用了NTP，
  // 也会被NTP修改。当系统休眠（suspend）时，仍然会运行的（系统恢复时，kernel去作补偿）。
  // CLOCK_MONOTONIC：为单调时间。以绝对时间为准，获取的时间为系统重启到现在的时间，更改系统时间对它没有影响。用户不能修改这个时间，但是当系统进入休眠（suspend）时，CLOCK_MONOTONIC会停止增加。
  // CLOCK_MONOTONIC_RAW: 和CLOCK_MONOTONIC类似，但不同之处是MONOTONIC_RAW不会受到NTP的影响。
  // CLOCK_BOOTTIME：与CLOCK_MONOTONIC类似，但是当系统进入休眠suspend时，会依然增加
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  std::cout << "CLOCK_REALTIME: " << ts.tv_sec << "s " << ts.tv_nsec << "ns" << std::endl;

  clock_gettime(CLOCK_MONOTONIC, &ts);
  std::cout << "CLOCK_MONOTONIC: " << ts.tv_sec << "s " << ts.tv_nsec << "ns" << std::endl;

  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
  std::cout << "CLOCK_MONOTONIC_RAW: " << ts.tv_sec << "s " << ts.tv_nsec << "ns" << std::endl;

  clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);
  std::cout << "CLOCK_MONOTONIC_COARSE: " << ts.tv_sec << "s " << ts.tv_nsec << "ns" << std::endl;

  clock_gettime(CLOCK_BOOTTIME, &ts);
  std::cout << "CLOCK_BOOTTIME: " << ts.tv_sec << "s " << ts.tv_nsec << "ns" << std::endl;

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
  std::cout << "CLOCK_PROCESS_CPUTIME_ID: " << ts.tv_sec << "s " << ts.tv_nsec << "ns" << std::endl;

  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
  std::cout << "CLOCK_THREAD_CPUTIME_ID: " << ts.tv_sec << "s " << ts.tv_nsec << "ns" << std::endl;

  return 0;
}