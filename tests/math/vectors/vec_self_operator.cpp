#include "common.hpp"

template<std::size_t Size>
constexpr int testSelfOperator() {
    int errors = 0;
    xme::Vector<double, Size> v{8};
    {
        v += 2;
        v += xme::Vector<double, Size>{1};
        bool error1 = std::ranges::any_of(v, [](double n){ return n != 11; });
        if(error1) {
            std::cerr << "Vector<T, Size>::operator+= operator error\n";
            ++errors;
        }
    }

    {
        v -= 4;
        v -= xme::Vector<double, Size>{2};
        bool error = std::ranges::any_of(v, [](double n){ return n != 5; });
        if(error) {
            std::cerr << "Vector<T, Size>::operator-= operator error\n";
            ++errors;
        } 
    }

    {
        v *= 2;
        v *= xme::Vector<double, Size>{2};
        bool error = std::ranges::any_of(v, [](double n){ return n != 20; });
        if(error) {
            std::cerr << "Vector<T, Size>::operator*= operator error\n";
            ++errors;
        }
    }

    {
        v /= 2;
        v /= xme::Vector<double, Size>{2};

        bool error = std::ranges::any_of(v, [](double n){ return n != 5; });
        if(error) {
            std::cerr << "Vector<T, Size>::operator/= operator error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testSelfOperator<2>();
    errors += testSelfOperator<3>();
    errors += testSelfOperator<4>();
    errors += testSelfOperator<5>();
    return errors;
}