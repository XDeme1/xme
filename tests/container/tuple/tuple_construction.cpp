#include "../common.hpp"
#include <xme/container/tuple.hpp>

int testConstruction() {
    int errors = 0;
    {
        int a = 1;
        int& b = a;
        const int& c = a;
        const int&& d = 6;
        xme::Tuple t1{1, 5};
        xme::Tuple t2{a, b};
        xme::Tuple t3{c, d};
        xme::Tuple t4{std::ref(b), std::ref(c)};
        xme::Tuple t5{std::ref(d)};

        static_assert(std::is_same_v<decltype(t1), xme::Tuple<int, int>>);
        static_assert(std::is_same_v<decltype(t2), xme::Tuple<int, int>>);
        static_assert(std::is_same_v<decltype(t3), xme::Tuple<int, int>>);
        static_assert(std::is_same_v<decltype(t4), xme::Tuple<int&, const int&>>);
        static_assert(std::is_same_v<decltype(t5), xme::Tuple<const int&>>);

        if(auto [tmp1, tmp2] = t1; tmp1 != 1 || tmp2 != 5)
            ++errors;

        if(auto [tmp1, tmp2] = t2; tmp1 != 1 || tmp2 != 1)
            ++errors;

        if(auto [tmp1, tmp2] = t3; tmp1 != 1 || tmp2 != 6)
            ++errors;

        if(auto [tmp1, tmp2] = t4; tmp1 != 1 || tmp2 != 1)
            ++errors;

        if(auto [tmp1] = t5; tmp1 != 6)
            ++errors;

        if(errors)
            std::cerr << "Tuple construction error\n";
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testConstruction();
    return errors;
}