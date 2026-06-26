#include <iostream>
#include <locale>
#include <type_traits>
#include <string>

/**
 * Localization Library (本地化库) 是 C++ 标准库的一部分，
 * 提供了对不同语言和地区的支持。它允许程序根据用户的语言和地区设置来处理文本、数字、货币等数据。
 *
 * local对象并不直接存储任何数据，而是通过组合不同的facet来提供对各种本地化功能的访问。
 * facet分成了六个大类：
 * 1. collate：
 *    collate：compare，hash，transform
 * 2. ctype：
 *    ctype：is，narrow，scan_is，scan_not，tolower，toupper，widen
 *    codecvt：always_noconv，encoding，in_length，max_length，out，in，unshift
 * 3. monetary：
 * 4. numeric：
 * 5. time：
 * 6. messages：
 */

void MemType() {
    if(std::is_same<std::locale::category, int>::value) {
        std::cout << "std::locale::category is int" << std::endl;
    } else {
        std::cout << "std::locale::category is not int" << std::endl;
    }
    // bitmask
    std::cout << "std::locale::collate: " << std::locale::collate << std::endl;
    std::cout << "std::locale::ctype: " << std::locale::ctype << std::endl;
    std::cout << "std::locale::monetary: " << std::locale::monetary << std::endl;
    std::cout << "std::locale::numeric: " << std::locale::numeric << std::endl;
    std::cout << "std::locale::time: " << std::locale::time << std::endl;
    std::cout << "std::locale::messages: " << std::locale::messages << std::endl;
    std::cout << "std::locale::all: " << std::locale::all << std::endl;
    std::cout << "std::locale::none: " << std::locale::none << std::endl;

    /**
     * class id {
     *  public：
     *   id();
     *   id(const id&) = delete;
     *   id& operator=(const id&) = delete;
     *  };
     */
    if(std::is_same<std::locale::id, int>::value) {
        std::cout << "std::locale::id is int" << std::endl;
    } else {
        std::cout << "std::locale::id is not int" << std::endl;
    }

    /**
     * class facet {
     *  protocted:
     *   explict facet(size_t refs = 0);
     *   virtual ~facet();
     *   facet(const facet&) = delete;
     *   facet& operator=(const facet&) = delete;
     *  };
     * @note 这里的 refs表示引用计数，一般都是0：表示让local对象去管理生命周期
     */
    if(std::is_same<std::locale::facet, int>::value) {
        std::cout << "std::locale::facet is int" << std::endl;
    } else {
        std::cout << "std::locale::facet is not int" << std::endl;
    }
}

class Symbol : public std::locale::facet {
public:
    static std::locale::id id;
    Symbol(std::string sym, int refs = 0) :symbol(sym), std::locale::facet(refs) {}
    virtual ~Symbol() {}
    std::string GetSymbol() const {return symbol;}
private:
    std::string symbol;
};
// lcale库会自动进行分配
std::locale::id Symbol::id;

void Confun() {
    // 1. default constructor
    std::locale loc = std::locale();
    // 2. copy constructor
    std::locale loc2(loc);
    // 3. by name constructor
    std::locale loc3("en_US.UTF8");
    // 4. combining constructors
    // 使用第一个参数中的facets，除了第三个参数指定的类型之外。第二个参数中的facets中符合第三个参数指定类型的会被采纳
    std::locale loc4 = std::locale(loc3, "", std::locale::ctype);

    // 5. custom facet constructor，这是唯一可以使用自定义的facet的方式
    // 必须使用new创建facet对象，并且必须在facet的构造函数中指定refs=0，否则会抛出异常
    std::locale loc5 = std::locale(loc3, new Symbol("$"));
}

void MemFun() {
    std::locale loc = std::locale::classic(); // 等价于 std::locale loc("C");

    std::locale loc2("");
    /**
     * 返回一个当前locale对象的副本，并从函数参数指向的locale中选取模板类型中指定的facet
     */
    loc2 = loc2.combine<std::num_put<char>>(std::locale::classic());

    std::locale loc3("C");
    // 设置后，后续默认构造函数会返回设置的locale对象
    loc3.global(std::locale("C"));
    std::locale loc4;
    std::cout << "loc3 == loc4: " << ((loc3 == loc4)?"True":"False") << std::endl;

    std::locale loc5("");
    std::string name = loc5.name();
    std::cout << "loc.name: " << loc.name() << std::endl;
    std::cout << "loc2.name: " << loc2.name() << std::endl;
    std::cout << "loc3.name: " << loc3.name() << std::endl;
    std::cout << "loc4.name: " << loc4.name() << std::endl;
    std::cout << "loc5.name: " << loc5.name() << std::endl;
}

void facet_example() {
    /**
     * template <class Facet> 
     * const Facet& use_facet (const locale& loc)
     */
    std::locale loc("");
    std::string in = "1234";
    long ret = std::use_facet<std::collate<char>>(loc).hash(&in[0], &in[0] + in.size());
    std::cout << "Hash value: " << ret << std::endl;

    /**
     * template <class Facet> 
     * bool has_facet (const locale& loc) noexcept;
     */
    if(std::has_facet<std::collate<char>>(loc)) {
        std::cout << "Locale has collate facet" << std::endl;
    } else {
        std::cout << "Locale does not have collate facet" << std::endl;
    }

    std::locale loc_def;
    std::locale loc1 = std::locale(loc_def, new Symbol("$"));
    std::string res = std::use_facet<Symbol>(loc1).GetSymbol();
    std::cout << "res: " << res << std::endl;
}

int main() {
    std::cout << "======================MemType======================" << std::endl;
    MemType();
    std::cout << "======================Confun======================" << std::endl;
    Confun();
    std::cout << "======================MemFun======================" << std::endl;
    MemFun();
    std::cout << "======================facet_example======================" << std::endl;
    facet_example();

    return 0;
}