#include "common.hpp"
#include <xme/container/tuple.hpp>
int main() {
    float f = 3;
    xme::Vector v1{1, 2, 3};
    xme::Vector v2{1.f, 2, 3, 4};
    xme::Vector v3{2, 1.0, 3, 4, 5};
    xme::Vector v4{f};

    static_assert(std::is_same_v<decltype(v1), xme::Vector<int, 3>>);
    static_assert(std::is_same_v<decltype(v2), xme::Vector<float, 4>>);
    static_assert(std::is_same_v<decltype(v3), xme::Vector<double, 5>>);
    static_assert(std::is_same_v<decltype(v4), xme::Vector<float, 1>>);
    
    return 0;
}