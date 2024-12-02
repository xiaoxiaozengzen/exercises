#include <tuple>
#include <iostream>

// template<class... Types>
// class tuple;

void Tuple() {
    std::tuple<int,char> first;                             // default
    std::tuple<int,char> second (first);                    // copy
    std::tuple<int,char> third (std::make_tuple(20,'b'));   // move
    std::tuple<long,char> fourth (third);                   // implicit conversion
    std::tuple<int,char> fifth (10,'a');                    // initialization
    std::tuple<int,char> sixth (std::make_pair(30,'c'));    // from pair / move

    std::cout << "sixth contains: " << std::get<0>(sixth);
    std::cout << " and " << std::get<1>(sixth) << '\n';
}

/**
 * Class template designed to access the number of elements in a tuple (as a constexpr).
 */
void TupleSize() {
    // template <class... Types>
    // struct tuple_size<tuple<Types...> > : integral_constant<size_t, sizeof...(Types)> {};
    std::tuple<int,char,double> mytuple (10,'a',3.14);

    std::cout << "mytuple has ";
    std::cout << std::tuple_size<decltype(mytuple)>::value;
    std::cout << " elements." << '\n';
    if(std::is_same<std::size_t, std::tuple_size<decltype(mytuple)>::value_type>::value) {
        std::cout << "The type of value_typee is size_t" << std::endl;
    }
}

/**
 * Class designed to access the type of the Ith element in a tuple.
 */
void TupleElement() {
    // template<
    //     size_t I,
    //     class... Types>
    // class tuple_element< I, tuple<Types...> >;
    auto mytuple = std::make_tuple (10,'a');

    std::tuple_element<0,decltype(mytuple)>::type first = std::get<0>(mytuple);
    std::tuple_element<1,decltype(mytuple)>::type second = std::get<1>(mytuple);

    std::cout << "mytuple contains: " << first << " and " << second << '\n';
}

void Fun() {
    std::tuple<int, char> mytuple = std::make_tuple(10, 'a');

    // template<class... Types>
    // tuple<Types&&...> forward_as_tuple (Types&&... args) noexcept
    // {
    //     return tuple<Types&&...>(std::forward<Types>(args)...);
    // }
    std::tuple<int, char> mytuple2 = std::forward_as_tuple(10, 'a');

    // template<class... Types>  tuple<Types&...> tie (Types&... args) noexcept;
    int myint;
    char mychar;
    std::tuple<int,float,char> mytuple3;
    mytuple3 = std::make_tuple(10, 2.6, 'a');          // packing values into tuple

    std::tie(myint, std::ignore, mychar) = mytuple3;   // unpacking tuple into variables

    std::cout << "myint contains: " << myint << '\n';
    std::cout << "mychar contains: " << mychar << '\n';
    myint = 20;
    std::cout << "mytuple3 contains: " << std::get<0>(mytuple3) << " " << std::get<1>(mytuple3) << " " << std::get<2>(mytuple3) << '\n';

    // template <class... Tuples>  tuple<CTypes...> tuple_cat (Tuples&&... tpls);
    // 拼接多个tuple
    std::tuple<float,std::string> mytuple4 (3.14,"pi");
    std::pair<int,char> mypair (10,'a');

    auto myauto = std::tuple_cat ( mytuple4, std::tuple<int,char>(mypair) );

    std::cout << "myauto contains: " << '\n';
    std::cout << std::get<0>(myauto) << '\n';
    std::cout << std::get<1>(myauto) << '\n';
    std::cout << std::get<2>(myauto) << '\n';
    std::cout << std::get<3>(myauto) << '\n';
}

int main() {
    std::cout << "--------------------------------Tuple--------------------------------" << std::endl;
    Tuple();
    std::cout << "--------------------------------TupleSize--------------------------------" << std::endl;
    TupleSize();
    std::cout << "--------------------------------TupleElement--------------------------------" << std::endl;
    TupleElement();
    std::cout << "--------------------------------Fun--------------------------------" << std::endl;
    Fun();
}