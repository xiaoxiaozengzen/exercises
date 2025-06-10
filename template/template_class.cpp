#include <iostream>

/******************************1. 模板类的成员函数明确指出******************************************** */
class A {
 public:
  A() {
    std::cout << "A()" << std::endl;
  }
  ~A() {
    std::cout << "~A()" << std::endl;
  }

  template <typename T>
  void print(T t) {
    std::cout << "A: " << t << std::endl;
  }

  template <typename T>
  T get(T t) {
    return t;
  }
};

class B : public A {
  public:
   B() {
     std::cout << "B()" << std::endl;
   }
   ~B() {
     std::cout << "~B()" << std::endl;
   }

   template <typename T>
   static void print(T t) {
     std::cout << "B: " << t << std::endl;
   }
 };

void class_template_fun() {
  A a;
  a.print(1);
  // 显示指定模板参数
  a.template print<int>(2);
  int ret = a.template get<int>(3);
  std::cout << "ret: " << ret << std::endl;

  B b;
  // 调用B的静态模板函数
  b.B::template print<int>(4);
  b.template print<int>(5);
}

/******************************2. 模板类的虚函数******************************************** */
template <typename T>
class VirtualBase {
 public:
  VirtualBase() {
    std::cout << "VirtualBase()" << std::endl;
  }
  virtual ~VirtualBase() {
    std::cout << "~VirtualBase()" << std::endl;
  }

  virtual void print(T t) {
    std::cout << "VirtualBase::print : " << t << std::endl;
  }

#if 0
/**
 * @brief 模板函数不能是虚函数
 * 
 * @note 因为每个包含虚函数的类具有一个virtual table,包含该类的所有虚函数的地址，因此vtable的大小是确定的。
 * 模板只有被使用时才会被实例化，将其声明为虚函数会使vtable的大小不确定。所以，成员函数模板不能为虚函数。
 */
  template <typename U>
  virtual void print(U u) {
    std::cout << "VirtualBase::print : " << u << std::endl;
  }
#endif
};
void class_template_virtual_fun() {
  VirtualBase<int> vb;
  vb.print(1);
}


/******************************3. 模板类的特化******************************************** */
template <typename T, typename U>
class SpecializationClass {
 public:
  SpecializationClass() {
    std::cout << "SpecializationClass()" << std::endl;
  }
  ~SpecializationClass() {
    std::cout << "~SpecializationClass()" << std::endl;
  }

  /**
   * @brief 模板类的静态成员
   * 
   * @note 同一个类模板实例化的不同的类，彼此之间毫无关系
   * @note 而静态数据成员是属于类的，而不是模板类；模板类实例化的不同的类，它们的静态数据成员不是同一个，请注意。
   */
  static const int value = 10;

#if 0
  /**
   * @brief 使用模板时，不能在相同作用域中使用相同的模板参数名
   * 
   * @note 编译会报错：error: declaration of template parameter ‘T’ shadows template parameter
   * @note 因为模板参数T已经在类模板SpecializationClass中声明了，所以不能在print函数中再次声明T。否则会shadow(遮蔽)掉类模板的T。
   */
  template <typename T>
  void print(T t) {
    std::cout << "SpecializationClass::print : " << t << std::endl;
  }
#endif

  /**
   * @note 可以类外定义
   */
  void print();
};

template <typename T, typename U>
void SpecializationClass<T, U>::print() {
  std::cout << "SpecializationClass::print" << std::endl;
}

/**
 * @note 模板类的成员函数不能偏特化，参考函数模板
 * @note 特化的成员函数必须类外实现 
 * 
 */

/**
 * @brief 模板类的全特化
 */
template <>
class SpecializationClass<int, int> {
 public:
  SpecializationClass() {
    std::cout << "SpecializationClass<int>()" << std::endl;
  }
  ~SpecializationClass() {
    std::cout << "~SpecializationClass<int>()" << std::endl;
  }

  void print(int t) {
    std::cout << "SpecializationClass<int>::print : " << t << std::endl;
  }
};

/**
 * @brief 模板类的部分特化
 * 
 * @note 部分特化是指只特化模板参数的一部分，而不是全部。
 * @note 这里特化了第一个模板参数为double，第二个模板参数为任意类型U。
 */
template <typename U>
class SpecializationClass<double, U> {
 public:
  SpecializationClass() {
    std::cout << "SpecializationClass<double, U>()" << std::endl;
  }
  ~SpecializationClass() {
    std::cout << "~SpecializationClass<double, U>()" << std::endl;
  }
  void print() {
    std::cout << "SpecializationClass<double, U>::print" << std::endl;
  }
  void my_print();
};

template <typename U>
void SpecializationClass<double, U>::my_print() {
  std::cout << "SpecializationClass<double, U>::my_print" << std::endl;
}


void class_template_specialization() {
  SpecializationClass<char, double> sc1;
  std::cout << "SpecializationClass<char, double>::value: " << SpecializationClass<char, double>::value << std::endl;
  sc1.print();

  SpecializationClass<int, int> sc2;
  sc2.print(2);

  SpecializationClass<double, int> sc3;
  sc3.print();
  sc3.my_print();
}

/****************************************4. 成员函数模板*********************************************** */
/**
 * @brief 类模板中的成员函数模板
 * 
 * @note 成员函数模板可以在类模板中定义，也可以在类模板外定义。
 * @note 成员函数模板可以是虚函数，但不能是纯虚函数。
 */
template <typename T>
class TemplateClass {
 public:
  TemplateClass() {
    std::cout << "TemplateClass()" << std::endl;
  }
  ~TemplateClass() {
    std::cout << "~TemplateClass()" << std::endl;
  }

  template <typename U>
  void print(U t) {
    std::cout << "TemplateClass::print : " << t << std::endl;
  }

  /**
   * @brief 不是模板函数，就是一个普通的成员函数
   */
  void my_print(T t) {
    std::cout << "TemplateClass::print : " << t << std::endl;
  }
};

/**
 * @brief 普通类中的模板函数
 */
class TemplateFun {
 public:
  TemplateFun() {
    std::cout << "TemplateFun()" << std::endl;
  }
  ~TemplateFun() {
    std::cout << "~TemplateFun()" << std::endl;
  }

  template <typename T>
  void print(T t) {
    std::cout << "TemplateFun::print : " << t << std::endl;
  }
};


int main() {
  std::cout << "===================== class_template_fun=====================" << std::endl;
  class_template_fun();
  std::cout << "===================== class_template_virtual_fun=====================" << std::endl;
  class_template_virtual_fun();
  std::cout << "===================== class_template_specialization=====================" << std::endl;
  class_template_specialization();
  return 0;
}