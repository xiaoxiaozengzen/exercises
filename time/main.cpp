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
 */
void timepoint_class() {
  std::chrono::system_clock::time_point tp_epoch;  // epoch value

  std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<int>> tp_seconds(
      std::chrono::duration<int>(1));

  // copy or move
  std::chrono::system_clock::time_point tp(tp_seconds);

  std::cout << "1 second since system_clock epoch = ";
  std::cout << tp.time_since_epoch().count();
  std::cout << " system_clock periods." << std::endl;

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

void systemclock() {
  std::chrono::duration<int, std::ratio<60 * 60 * 24>> one_day(1);

  std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
  std::chrono::system_clock::time_point tomorrow = today + one_day;

  std::cout << std::boolalpha << "is ready: " << std::chrono::system_clock::is_steady << std::endl;

  std::cout << "today: " << today.time_since_epoch().count() << std::endl;

  std::time_t tt;

  tt = std::chrono::system_clock::to_time_t(today);
  std::cout << "today is: " << ctime(&tt);

  tt = std::chrono::system_clock::to_time_t(tomorrow);
  std::cout << "tomorrow will be: " << ctime(&tt);
}

void time_function() {
  std::chrono::seconds s(1);  // 1 second
  std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(s);

  ms += std::chrono::milliseconds(2500);  // 2500 millisecond

  s = std::chrono::duration_cast<std::chrono::seconds>(ms);  // truncated

  std::cout << "ms: " << ms.count() << std::endl;
  std::cout << "s: " << s.count() << std::endl;

  typedef std::chrono::duration<int, std::ratio<60 * 60 * 24>> days_type;

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
  std::cout << "=======================systemclock=======================" << std::endl;
  systemclock();
  std::cout << "=======================time_function=======================" << std::endl;
  time_function();
  std::cout << "=======================chrono_literals=======================" << std::endl;
  chrono_literals();
}