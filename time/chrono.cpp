#include <chrono>
#include <ctime>
#include <iostream>
#include <ratio>

/**
 * template <intmax_t N, intmax_t D = 1> class ratio;
 */
void ratio_class() {
  typedef std::ratio<1, 3> one_third;
  typedef std::ratio<2, 4> two_fourths;
  std::cout << "one_third= " << one_third::num << "/" << one_third::den << std::endl;
  std::cout << "two_fourths= " << two_fourths::num << "/" << two_fourths::den << std::endl;

  if(std::is_same<one_third::type, std::ratio<1, 3>>::value) {
    std::cout << "one_third::type is std::ratio<1, 3>" << std::endl;
  }

  // 一些定义好的比率
  std::cout << "std::milli : " << std::milli::num << "/" << std::milli::den << std::endl;
  std::cout << "std::kilo : " << std::kilo::num << "/" << std::kilo::den << std::endl;

  typedef std::ratio_add<one_third, two_fourths> sum;

  std::cout << "sum= " << sum::num << "/" << sum::den;
  std::cout << " (which is: " << (double(sum::num) / sum::den) << ")" << std::endl;

  std::cout << "1 kilogram has " << (std::kilo::num / std::kilo::den) << " grams";
  std::cout << std::endl;
}

/**
 * template <class Rep, class Period = ratio<1> >class duration;
 */
void duration_class() {
  typedef std::chrono::duration<int> seconds_type;
  typedef std::chrono::duration<int, std::milli> milliseconds_type;
  typedef std::chrono::duration<int, std::ratio<60 * 60>> hours_type;
  using seconds_double = std::chrono::duration<double, std::ratio<1>>;

  hours_type h_oneday(24);                // 24h
  seconds_type s_oneday(60 * 60 * 24);    // 86400s
  milliseconds_type ms_oneday(s_oneday);  // 86400000ms
  seconds_double s(1.5);
  std::cout << "h_oneday.count() : " << h_oneday.count() << std::endl;
  std::cout << "h_oneday.zero() : " << h_oneday.zero().count() << std::endl;
  std::cout << "h_oneday.min() : " << h_oneday.min().count() << std::endl;
  std::cout << "h_oneday.max() : " << h_oneday.max().count() << std::endl;
  std::cout << "s.count() : " << s.count() << std::endl;
  std::cout << "s.zero() : " << s.zero().count() << std::endl;
  std::cout << "s.min() : " << s.min().count() << std::endl;
  std::cout << "s.max() : " << s.max().count() << std::endl;

  seconds_type s_onehour(60 * 60);  // 3600s
  // hours_type h_onehour (s_onehour);          // NOT VALID (type truncates),
  // use:
  hours_type h_onehour(std::chrono::duration_cast<hours_type>(s_onehour));
  milliseconds_type ms_onehour(s_onehour);  // 3600000ms (ok, no type truncation)

  std::cout << ms_onehour.count() << "ms in 1h" << std::endl;

  std::chrono::duration<int> foo;
  std::chrono::duration<int> bar(10);

  // counts: foo bar
  //         --- ---
  foo = bar;           // 10  10
  foo = foo + bar;     // 20  10
  ++foo;               // 21  10
  --bar;               // 21   9
  foo *= 2;            // 42   9
  foo /= 3;            // 14   9
  bar += (foo % bar);  // 14  14

  std::cout << std::boolalpha;
  std::cout << "foo==bar: " << (foo == bar) << std::endl;
  std::cout << "foo: " << foo.count() << std::endl;
  std::cout << "bar: " << bar.count() << std::endl;
}

/**
 * template <class Clock, class Duration = typename Clock::duration>  class time_point;
 * 
 * 1.表示相对于epoch的时间点，epoch是一个特定的时间点，通常是1970年1月1日00:00:00 UTC。
 * 2.它需要依赖Clock类提供的time_point类型。clock类有system_clock, steady_clock和high_resolution_clock。
 */
void timepoint_class() {
  typedef std::chrono::time_point<std::chrono::system_clock> time_point_type;  // system_clock
  // member type
  if(std::is_same<time_point_type::clock, std::chrono::system_clock>::value) {
    std::cout << "time_point_type::clock is std::chrono::system_clock" << std::endl;
  }
  if(std::is_same<time_point_type::duration, std::chrono::system_clock::duration>::value) {
    std::cout << "time_point_type::duration is std::chrono::system_clock::duration" << std::endl;
  }
  if(std::is_same<time_point_type::rep, std::chrono::system_clock::rep>::value) {
    std::cout << "time_point_type::rep is std::chrono::system_clock::rep" << std::endl;
  }
  if(std::is_same<time_point_type::period, std::chrono::system_clock::period>::value) {
    std::cout << "time_point_type::period is std::chrono::system_clock::period" << std::endl;
  }

  //construct functions
  time_point_type tp;  // default constructor, epoch value
  time_point_type tp_1(time_point_type::duration(1));  // from duration object
  std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<int, std::milli>> tp_2(
      std::chrono::duration<int, std::milli>(10));  // from duration object
  time_point_type tp_3(tp_2);  // copy / from time_point

  // member functions
  std::chrono::duration<int, std::milli> dtn_2 = tp_2.time_since_epoch();  // epoch value
  time_point_type::duration dtn_1 = tp_1.time_since_epoch();  // epoch value
  std::cout << "dtn_1: " << dtn_1.count() << std::endl;
  std::cout << "dtn_2: " << dtn_2.count() << std::endl;

  // display time_point:
  std::time_t tt = std::chrono::system_clock::to_time_t(tp);
  std::cout << "time_point tp is: " << ctime(&tt);
  std::chrono::system_clock::time_point tp1, tp2;                          // epoch value
  std::chrono::system_clock::duration dtn(std::chrono::duration<int>(1));  // 1 second

  //  tp     tp2    dtn
  //  ---    ---    ---
  tp1 += dtn;       //  e+1s   e      1s
  tp2 -= dtn;       //  e+1s   e-1s   1s
  tp2 = tp1 + dtn;  //  e+1s   e+2s   1s
  tp1 = dtn + tp2;  //  e+3s   e+2s   1s
  tp2 = tp2 - dtn;  //  e+3s   e+1s   1s
  dtn = tp1 - tp2;  //  e+3s   e+1s   2s

  std::cout << std::boolalpha;
  std::cout << "tp == tp2: " << (tp1 == tp2) << std::endl;
  std::cout << "tp > tp2: " << (tp1 > tp2) << std::endl;
  std::cout << "dtn: " << dtn.count() << std::endl;
}

/**
 * class system_clock
 * 1.realtime: 该类表示系统的实时时钟，通常用于获取当前的日期和时间。
 * 2.time point: 该类的时间点是有符号的，意味着它可以表示epoch之前的时间。
 * 3.system-wide: 使用该类获取时间点时，这个系统上所有进程调用其接口获取的时间点都是一致的。
 */
void system_clock_class() {
  // member type
  if(std::is_same<std::chrono::system_clock::rep, int>::value) {
    std::cout << "std::chrono::system_clock::rep is int" << std::endl;
  } else {
    std::cout << "std::chrono::system_clock::rep is not int" << std::endl;
  }
  if(std::is_same<std::chrono::system_clock::period, std::ratio<1>>::value) {
    std::cout << "std::chrono::system_clock::period is std::ratio<1>" << std::endl;
  } else {
    std::cout << "std::chrono::system_clock::period is not std::ratio<1>" << std::endl;
  }
  if(std::is_same<std::chrono::system_clock::duration, std::chrono::duration<int>>::value) {
    std::cout << "std::chrono::system_clock::duration is std::chrono::duration<int>" << std::endl;
  } else {
    std::cout << "std::chrono::system_clock::duration is not std::chrono::duration<int>" << std::endl;
  }
  if(std::is_same<std::chrono::system_clock::time_point, std::chrono::time_point<std::chrono::system_clock>>::value) {
    std::cout << "std::chrono::system_clock::time_point is std::chrono::time_point<std::chrono::system_clock>" << std::endl;
  } else {
    std::cout << "std::chrono::system_clock::time_point is not std::chrono::time_point<std::chrono::system_clock>" << std::endl;
  }

  // member constants
  std::cout << "std::chrono::system_clock::is_steady: " << std::chrono::system_clock::is_steady << std::endl;

  // static member functions
  std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();  // 获取当前时间点
  time_t tt = std::chrono::system_clock::to_time_t(tp);  // 转换为time_t类型
  std::cout << "current time: " << ctime(&tt);  // 转换为字符串格式输出
  time_t tt2 = time(nullptr);  // 获取当前时间点
  std::chrono::system_clock::time_point tp2 = std::chrono::system_clock::from_time_t(tt2);  // 转换为time_point类型

  // construct functions
  std::chrono::system_clock clock;  // default constructor
}

/**
 * class steady_clock
 * 1.monotonic: 单调时间钟，表示时间是单调递增的，不会回退。
 * 2.steday：时钟前进的每一个tick都是相同的，表示时间是稳定的。
 */
void steady_clock_class() {
  // 同system_clock，但是静态成员函数只有now()
}

/**
 * class high_resolution_clock
 * 1.high resolution: 提供最高精度的时钟，它可能是steady_clock或system_clock的别名。
 */
void high_resolution_clock_class() {
  // 同system_clock，但是静态成员函数只有now()
}

void time_function() {
  /**
   * template <class ToDuration, class Rep, class Period>
   * constexpr ToDuration duration_cast (const duration<Rep,Period>& dtn);
   * 
   * @brief 将一个duration对象转换为另一个duration对象，其period可以不同。
   */
  std::chrono::seconds s(1);  // 1 second
  std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(s);

  ms += std::chrono::milliseconds(2500);  // 2500 millisecond
  s = std::chrono::duration_cast<std::chrono::seconds>(ms);  // truncated

  std::cout << "ms: " << ms.count() << std::endl;
  std::cout << "s: " << s.count() << std::endl;

  typedef std::chrono::duration<int, std::ratio<60 * 60 * 24>> days_type;

  /**
   * template <class ToDuration, class Clock, class Duration>
   * time_point<Clock,ToDuration> time_point_cast (const time_point<Clock,Duration>& tp);
   * 
   * @brief 将一个time_point对象转换为另一个time_point对象，其duration可以不同。
   */
  std::chrono::time_point<std::chrono::system_clock, days_type> today =
      std::chrono::time_point_cast<days_type>(std::chrono::system_clock::now());
  std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;
}

using namespace std::chrono_literals; // C++14 引入的一个命名空间，用于定义一些时间单位的字面量
/**
 * 主要增加了一些时间单位的字面量，如1h, 1min, 1s, 1ms, 1us, 1ns
 */
void chrono_literals() {
  std::chrono::duration<int, std::ratio<3600>> hour = 10h;
  std::chrono::duration<int, std::ratio<60>> min = 10min;
  std::chrono::duration<int, std::ratio<1>> sec = 10s;
  std::chrono::duration<int, std::milli> ms = 1000ms;
  std::chrono::duration<int, std::micro> us = 1000us;
  std::chrono::duration<int, std::nano> ns = 1000ns;

  std::cout << "hour is " << hour.count() << std::endl;
  std::cout << "min is " << min.count() << std::endl;
  std::cout << "sec is " << sec.count() << std::endl;
  std::cout << "ms is " << ms.count() << std::endl;
  std::cout << "us is " << us.count() << std::endl;
  std::cout << "ns is " << ns.count() << std::endl;
}

int main() {
  std::cout << "=======================ratio_class=======================" << std::endl;
  ratio_class();
  std::cout << "=======================duration_class=======================" << std::endl;
  duration_class();
  std::cout << "=======================timepoint_class=======================" << std::endl;
  timepoint_class();
  std::cout << "=======================system_clock_class=======================" << std::endl;
  system_clock_class();
  std::cout << "=======================steady_clock_class=======================" << std::endl;
  steady_clock_class();
  std::cout << "=======================high_resolution_clock_class=======================" << std::endl;
  high_resolution_clock_class();
  std::cout << "=======================time_function=======================" << std::endl;
  time_function();
  std::cout << "=======================chrono_literals=======================" << std::endl;
  chrono_literals();
}