#include "common.hpp"

template<std::size_t Size>
constexpr int testSelfOperator() {
    int errors = 0;
    xme::Vector<double, Size> v{8};
    {
        std::vector<short> errorList;
        v += 2;
        v += xme::Vector<double, Size>{1};

        for(std::size_t i = 0; i < Size; ++i)
            errorList.emplace_back(v[i] == 11);

        bool error = std::ranges::any_of(errorList, isError);
        if(error) {
            std::cerr << "Vector<T, Size>::operator+= operator error\n";
            ++errors;
        }
    }

    {
        std::vector<short> errorList;
        v -= 4;
        v -= xme::Vector<double, Size>{2};

        for(std::size_t i = 0; i < Size; ++i)
            errorList.emplace_back(v[i] == 5);

        bool error = std::ranges::any_of(errorList, isError);
        if(error) {
            std::cerr << "Vector<T, Size>::operator-= operator error\n";
            ++errors;
        } 
    }

    {
        std::vector<short> errorList;
        v *= 2;
        v *= xme::Vector<double, Size>{2};

        for(std::size_t i = 0; i < Size; ++i)
            errorList.emplace_back(v[i] == 20);

        bool error = std::ranges::any_of(errorList, isError);
        if(error) {
            std::cerr << "Vector<T, Size>::operator*= operator error\n";
            ++errors;
        }
    }

    {
        std::vector<short> errorList;
        v /= 2;
        v /= xme::Vector<double, Size>{2};
        for(std::size_t i = 0; i < Size; ++i)
            errorList.emplace_back(v[i] == 5);

        bool error = std::ranges::any_of(errorList, isError);
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