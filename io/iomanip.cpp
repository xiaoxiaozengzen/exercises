#include <iomanip>
#include <iostream>
#include <ctime>
#include <locale>
#include <chrono>


/**
 * std::ios_base::fmtflags
 * 
 * @brief 一个bitmark类型数据，可以表示各种格式标志。
 * 
 * @details 其大致包含内容如下：
 * 1. independent
 *   - boolalpha: 使用bool类型的字符串表示true和false。
 *   - showbase: 显示数字的基数（如十进制、八进制、十六进制）。
 *   - showpoint: 显示小数点。
 *   - showpos: 显示正号。
 *   - skipws: 跳过空白字符。
 *   - unitbuf: 每次输出后刷新缓冲区。
 *   - uppercase: 小写字母转换为大写。
 * 2. numeric
 *   - dec: 十进制格式。
 *   - hex: 十六进制格式。
 *   - oct: 八进制格式。
 * 3. float format
 *   - fixed: 用定点表示法输出浮点数。
 *   - scientific: 用科学计数法输出浮点数。
 * 4. adjust
 *   - internal: 将输出填充到filed width宽度，填充字符是fill character。
 *   - left: 将输出左对齐。
 *   - right: 将输出右对齐。
 * 
 * @note 有三个额外的标志：
 *   - adjustfield: 相当于 internal | left | right
 *   - basefield: 相当于 dec | hex | oct
 *   - floatfield: 相当于 fixed | scientific
 * 
 * @note 这些标志可以通过 | 运算符组合使用。
 * @note 这些标志用于函数接口：std::ios_base::flags、std::ios_base::setf、std::ios_base::unsetf
 */
void ios_base_flags() {
/**
 * std::ios_base::fmtflags flasgs();
 * std::ios_base::fmtflags flags(std::ios_base::fmtflags fmtfl);
 * @brief 第一个版本：返回当前的格式标志。
 * @brief 第二个版本会取消当前的所有格式标志，并设置为fmtfl。
 * 
 * fmtflags setf(std::ios_base::fmtflags fmtfl);
 * fmtflags setf(std::ios_base::fmtflags fmtfl, std::ios_base::fmtflags mask);
 * @brief 第一个版本：不改变原有的格式标志基础上，fmtfl中指定的格式会被设置。相当于叠加
 * @brief 第二个版本：将fmtl和mask中都有的标志位进行设置；姜mask中设置了但是fmtfl中没有的标志位清除。
 * 
 * void unsetf (fmtflags mask);
 * @brief 将mack中指定的格式标志清除。
 * 
 */

  std::cout << "dec: " << 10 << std::endl;
  std::cout << "float: " << 3.14159265358979323846 << std::endl;

  std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
  std::cout.setf(std::ios_base::showbase);
  std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
  std::cout.setf(std::ios_base::right, std::ios_base::adjustfield);

  std::cout << "dec: " << 10 << std::endl;
  std::cout << "float: " << 3.14159265358979323846 << std::endl;
  std::cout.unsetf(std::ios_base::right);
  std::cout.unsetf(std::ios_base::fixed);
  std::cout.unsetf(std::ios_base::showbase);
  std::cout.unsetf(std::ios_base::hex);
}

/**
 * setiosflags (ios_base::fmtflags mask);
 * 
 * @brief 设置mask中指定的格式标志。
 */
void setiosflags_test() {
    std::cout << "dec: " << 10 << std::endl;
    std::cout << "float: " << 3.14159265358979323 << std::endl;

    std::cout << std::setiosflags(std::ios_base::hex | std::ios_base::showbase | std::ios_base::fixed | std::ios_base::right);
    std::cout << "dec: " << 10 << std::endl;
    std::cout << "float: " << 3.14159265358979323 << std::endl;

    std::cout << std::resetiosflags(std::ios_base::right | std::ios_base::fixed | std::ios_base::showbase | std::ios_base::hex);
    std::cout << "dec: " << 10 << std::endl;
    std::cout << "float: " << 3.14159265358979323 << std::endl;
}

/**
 * setbase (int base);
 * @brief 设置数字的基数。
 * dec: 10
 * oct: 8
 * hex: 16
 */
void set_base_test() {
    std::cout << "dec: " << 10 << std::endl;
    std::cout << "oct: " << std::setbase(8) << 10 << std::endl;
    std::cout << "hex: " << std::setbase(16) << 10 << std::endl;

    // Reset to decimal base
    std::cout << "value: " << 13 << std::endl;
    std::cout.setf(std::ios_base::dec, std::ios_base::basefield);
    std::cout << "dec: " << 13 << std::endl;
}

/**
 * setfill (char_type c);
 * setw (int n);
 * 
 * @note 不会截断字符串，只会在其长度不够的时候填充字符。
 */
void set_fill_test() {
    std::cout << "123456789" << std::endl;
    std::cout << std::setfill('x') << std::setw(20);
    std::cout << "123456789" << std::endl;
    std::cout << std::setw(5);
    std::cout << "123456789" << std::endl;
    
    std::cout << std::setfill(' ') << std::setw(0);
}

/**
 * setprecision (int n);
 * 
 * @brief 设置浮点数的精度。
 * @note 当未设置fixed或scientific时，setprecision设置的n，表示有效数字的个数。
 * @note 当设置了fixed或scientific时，setprecision设置的n，表示小数点后的位数。
 */
void set_precesion_test() {
    double value = 3.14159265358979323846;
    std::cout << "default precision: " << value << std::endl;
    std::cout << std::setprecision(5) << "vaild num 5: " << value << std::endl;
    std::cout.setf(std::ios_base::fixed);
    std::cout << "fixed precision: " << value << std::endl;
    
    std::cout.unsetf(std::ios_base::fixed);
    std::cout << std::setprecision(6);
}

/**
 * template <class moneyT>
 * get_money (moneyT& mon, bool intl = false);
 * 
 * template <class charT>
 * get_time (struct tm* tmb, const charT* fmt);
 * 
 * template <class charT>
 * put_time (const struct tm* tmb, const charT* fmt);
 */
void get_money_test() {
    std::cout << std::put_money(12345.67) << std::endl;
    std::cout << std::put_money(12345.67, true) << std::endl;
    std::cout << std::put_money(12345.67L) << std::endl;

    /**
     * 格式名字：
     * %a - 星期几的缩写
     * %A - 星期几的全称
     * %b - 月份的缩写
     * %B - 月份的全称
     * %c - 日期和时间的缩写
     * %C - 年份的前两位数字
     * %d - 月份中的第几天（01-31）
     * %D - 日期的缩写（MM/DD/YY）
     * %e - 月份中的第几天（1-31），前面不补零
     * %F - 日期的全称（YYYY-MM-DD）
     * %g - ISO 8601年份的前两位数字
     * %G - ISO 8601年份的全称
     * %h - 月份的缩写（与%b相同）
     * %H - 小时（00-23）
     * %I - 小时（01-12）
     * %j - 一年中的第几天（001-366）
     * %m - 月份（01-12）
     * %M - 分钟（00-59）
     * %n - 换行符
     * %p - AM或PM
     * %r - 12小时制的时间（hh:mm:ss AM/PM）
     * %R - 24小时制的时间（hh:mm）
     * %S - 秒（00-59）
     * %t - 制表符
     * %T - 24小时制的时间（hh:mm:ss）
     * %u - ISO 8601星期中的第几天（1-7，其中1表示星期一）
     * %U - 一年中的第几周（00-53），星期日为一周的第一天
     * %V - ISO 8601一年的第几周（01-53），星期一为一周的第一天
     * %w - 星期中的第几天（0-6，其中0表示星期日）
     * %W - 一年中的第几周（00-53），星期一为一周的第一天
     * %x - 日期的缩写（MM/DD/YY）
     * %X - 时间的缩写（HH:MM:SS）
     * %y - 年份的后两位数字（00-99）
     * %Y - 年份的全称（四位数字）
     * %z - 时区偏移量（+hhmm或-hhmm）
     * %Z - 时区名称
     * %% - 百分号字符（%）
     */
    struct std::tm when;
    std::stringstream input_stream;
    input_stream.str("14:30");  // Example input, you can change this to
    input_stream >> std::get_time(&when,"%R");   // extract time (24H format)
    std::cout << ", hour: " << when.tm_hour
              << ", minute: " << when.tm_min
              << std::endl;
    
    std::time_t tt = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());
    struct std::tm * ptm = std::localtime(&tt);
    std::cout << "Current time: " << std::put_time(ptm, "%Y-%m-%d %H:%M:%S") << std::endl;
}

int main() {
    std::cout << "===================== ios_base_flags =====================" << std::endl;
    ios_base_flags();
    std::cout << "===================== setiosflags_test =====================" << std::endl;
    setiosflags_test();
    std::cout << "===================== set_base_test =====================" << std::endl;
    set_base_test();
    std::cout << "===================== set_fill_test =====================" << std::endl;
    set_fill_test();
    std::cout << "===================== set_precesion_test =====================" << std::endl;
    set_precesion_test();
    std::cout << "===================== get_money_test =====================" << std::endl;
    get_money_test();

    return 0;
}