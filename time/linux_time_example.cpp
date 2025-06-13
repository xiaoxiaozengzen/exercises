#include <sys/time.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

/**
 * 在Linux中有硬件时钟与系统时钟两种时钟:
 * 1. 硬件时钟: 由电池供电, 即使系统断电也能保持时间, 一般在BIOS中设置
 * 2. 系统时钟: kernel中的时钟, 由操作系统维护, 一般在系统启动时从硬件时钟中读取时间。一般调用都是从系统时钟中获取时间。
 * 
 * 硬件时钟(RTC, Real Time Clock)是一个独立的时钟芯片, 它在计算机断电时仍然可以保持时间。
 * 硬件时钟通常由电池供电，因此即使计算机关闭或断电，它也能继续运行。硬件时钟通常在计算机启动时被操作系统读取，并用于设置系统时钟。
 * 一般可以通过命令hwclock来查看和设置硬件时钟。
 * 
 * 系统时钟是操作系统内核维护的时钟，它在计算机启动时从硬件时钟中读取时间，并在计算机运行时不断更新。
 * 系统时钟通常用于计算机的时间戳、文件时间戳、定时器等操作。系统时钟的精度通常比硬件时钟高。
 * 系统时钟的时间可以通过系统调用或库函数来获取，例如time()、gettimeofday()、clock_gettime()等。
 * 也可以通过命令date来查看和设置系统时钟的时间。
 */

/**
 * linux中中断涉及两个全局变量
 * 1.xtime，一个timeval结构类型变量，是从cmos电路中取得的时间，通常是从某一历史时刻开始到现今的时间，也就是为了取得我们操作系统上显示的日期。
 * 这个就是“实时时钟”，它的精确度是毫秒。获取方法是通过sys/time.h头文件上面的gettimeofday函数获取。
 * 
 * 2.jiffies，（比xtime更精确，也更重要),记录着从电脑开机到现在总共的时钟中断次数
 */

/**
 * linux中时间的概念：
 * 1.real time：实际时间，就是wall time，
 * 2.用户cpu时间：用户态下的cpu时间
 * 3.系统cpu时间：内核态下的cpu时间
 * 4.进程cpu时间：用户态+内核态的cpu时间，又可以称为进程运行时间
 * 
 * 时钟时间=进程等待时间+进程阻塞时间+进程运行时间
 * 进程运行时间=用户cpu时间+系统cpu时间
 */

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

  /**
   * time_t time (time_t* timer);
   * @brief 获取当前时间到1970年1月1日00:00:00的秒数
   * @param timer 如果不为NULL，则将当前时间也存储在timer指向的变量中
   * @return 返回当前时间的秒数
   */
  time_t t;
  t = time(NULL);
  std::cout << "time(NULL): " << t << " s" << std::endl;

  /**
   * int gettimeofday( struct timeval *tv, struct timezone *tz );
   * @brief 获取对应时区的当前时间，从1970年1月1日00:00:00到现在的秒数和微秒数
   * @param tv 指向timeval结构体的指针，存储当前时间
   * @param tz 指向timezone结构体的指针，存储时区信息，这个参数过时了，通常传NULL
   * @return 成功返回0，失败返回-1
   * 
   * struct timeval {
   *   time_t      tv_sec;  // 秒数
   *   suseconds_t tv_usec; // 微秒数
   * };
   * 
   * struct timezone {
   *   int tz_minuteswest; // 当前时区与格林威治时间的差值，单位为分钟
   *   int tz_dsttime;     // 夏令时标志
   * };
   */
  struct timeval tv;
  int ret = gettimeofday(&tv, NULL);
  if (ret != 0) {
    std::cout << "gettimeofday failed" << std::endl;
  }
  std::cout << "gettimeofday: " << tv.tv_sec << "s " << tv.tv_usec << "us" << std::endl;

  /**
   * @brief 获取系统的 时钟滴答的频率
   */
  long ticks = sysconf(_SC_CLK_TCK);
  std::cout << "sysconf(_SC_CLK_TCK): " << ticks << " ticks per second" << std::endl;


  /**
   * clock_t times(struct tms *buf)
   * @brief 获取当前进程的CPU时间
   * @param buf 指向tms结构体的指针，存储当前进程的CPU时间，其中时间都是以clock ticks为单位
   * @return 从系统启动到现在的时钟滴答数
   * 
   * typedef long int clock_t;
   * 
   * struct tms {
   *   clock_t tms_utime;  // 用户CPU时间
   *   clock_t tms_stime;  // 系统CPU时间
   *   clock_t tms_cutime; // 子进程用户CPU时间
   *   clock_t tms_cstime; // 子进程系统CPU时间
   * };
   */
  struct tms tms_value;
  clock_t c = times(&tms_value);
  std::cout << "cpu time: " << c << " ticks" << std::endl;
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


  /**
   * clock_t clock(void);
   * @brief 获取当前进程的CPU时间
   * @return 返回自程序开始执行到当前位置为止, 处理器走过的时钟打点数
   * 
   * CLOCKS_PER_SEC 是一个常量，一般为1000000，用于将clock()函数的返回值转换成秒数
   */
  clock_t clocktime;
  std::cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << std::endl;
  clocktime = clock();
  std::cout << "clocktime: " << clocktime << ", s: " << double(clocktime) / CLOCKS_PER_SEC
            << std::endl;

  /**
   * int clock_gettime(clockid_t clk_id, struct timespec *tp);
   * @brief 获取特定的clk_id对应的时间
   * @param clk_id 时钟ID，指定要获取的时钟类型
   * @param tp 指向timespec结构体的指针，存储获取到的时间
   * @return 成功返回0，失败返回-1
   * 
   * struct timespec {
   *   time_t tv_sec;  // 秒数
   *   long   tv_nsec; // 纳秒数
   * };
   * 
   * CLOCK_REALTIME: 实际时间。可以使用命令（date）或是系统调用去修改。如果使用了NTP，也会被NTP修改。当系统休眠（suspend）时，仍然会运行的（系统恢复时，kernel去作补偿）。
   * CLOCK_MONOTONIC: 单调时间。以绝对时间为准，获取的时间为系统重启到现在的时间，更改系统时间对它没有影响。用户不能修改这个时间，但是当系统进入休眠（suspend）时，CLOCK_MONOTONIC会停止增加。
   * CLOCK_MONOTONIC_RAW: 和CLOCK_MONOTONIC类似，但不同之处是MONOTONIC_RAW不会受到NTP的影响。
   * CLOCK_MONOTONIC_COARSE: 单调时间的粗略版本，精度较低，但性能更好。
   * CLOCK_BOOTTIME: 与CLOCK_MONOTONIC类似，但是当系统进入休眠suspend时，会依然增加
   */
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

  /**
   * struct tm {
   *  int tm_sec;   // 秒，范围为0-60
   *  int tm_min;   // 分，范围为0-59
   *  int tm_hour;  // 小时，范围为0-23
   *  int tm_mday;  // 一月中的第几天，范围为1-31
   *  int tm_mon;   // 月份，范围为0-11（0表示1月，11表示12月）
   *  int tm_year;  // 年份，从1900年开始计算
   *  int tm_wday;  // 一周中的第几天，范围为0-6（0表示星期日，6表示星期六）
   *  int tm_yday;  // 一年中的第几天，范围为0-365（0表示1月1日，365表示12月31日）
   *  int tm_isdst; // 夏令时标志，正值表示夏令时，0表示非夏令时，负值表示未知
   * };
   */
  time_t now = time(NULL);
  struct tm* local_time = localtime(&now);
  std::cout << "local time: "
            << local_time->tm_year + 1900 << "-"
            << local_time->tm_mon + 1 << "-"
            << local_time->tm_mday << " "
            << local_time->tm_hour << ":"
            << local_time->tm_min << ":"
            << local_time->tm_sec << std::endl; 
  struct tm* gmt_time = gmtime(&now);
  std::cout << "gmt time: "
            << gmt_time->tm_year + 1900 << "-"
            << gmt_time->tm_mon + 1 << "-"
            << gmt_time->tm_mday << " "
            << gmt_time->tm_hour << ":"
            << gmt_time->tm_min << ":"
            << gmt_time->tm_sec << std::endl;
  char* time_str = asctime(local_time);
  std::cout << "asctime(local_time): " << time_str << std::endl;
  char time_str_buf[100];
  std::size_t size = strftime(time_str_buf, sizeof(time_str_buf), "%Y-%m-%d %H:%M:%S", local_time);
  if (size > 0) {
    std::cout << "size = " << size << std::endl;
    std::cout << "strftime(local_time): " << time_str_buf << std::endl;
  } else {
    std::cerr << "strftime failed" << std::endl;
  }

  return 0;
}