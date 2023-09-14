#include "../common.hpp"
#include <xme/container/tuple.hpp>

int main() {
    int errors = 0;
    xme::Tuple<int, const int&> t1{1, 5};
    auto&& [a, b] = t1;

    static_assert(std::is_same_v<decltype(get<0>(t1)), int&>);
    static_assert(std::is_same_v<decltype(get<1>(t1)), const int&>);
    static_assert(std::is_same_v<decltype(get<0>(std::move(t1))), int&&>);
    
    static_assert(std::is_same_v<decltype(a), int>);
    static_assert(std::is_same_v<decltype(b), const int&>);

    std::array results{
        get<0>(t1) == 1,
        get<1>(t1) == 5,
        a == 1,
        b == 5,
    };


    bool error = std::ranges::any_of(results, isError);
    if(error) {
        ++errors;
        std::cerr << "xme::get(xme::Tuple) error\n";
    }


    return errors;
}