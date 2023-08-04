#include <xme/math/math.hpp>
#include <algorithm>
#include <iostream>

bool isError(bool b) { return b == false; }

template<std::size_t Size>
constexpr int testSelfOperator() {
    int errors = 0;
    {
        xme::Vector<double, Size> v1{8};
        v1 += 3;
        std::array<bool, Size> results{};
        for (std::int32_t i = 0; i < Size; ++i) {
            results[i] = v1[i] == 11;
        }
        auto error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector += Operator Error\n";
            ++errors;
        }
    }

    {
        xme::Vector<double, Size> v{8};
        v -= 9;
        std::array<bool, Size> results{};
        for (std::int32_t i = 0; i < Size; ++i) {
            results[i] = v[i] == -1;
        }
        auto error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector -= Operator Error\n";
            ++errors;
        } 
    }

    {

        xme::Vector<double, Size> v{3};
        v *= 5;
        std::array<bool, Size> results{};
        for (std::int32_t i = 0; i < Size; ++i) {
            results[i] = v[i] == 15;
        }
        auto error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector *= Operator Error\n";
            ++errors;
        }
    }

    {
        xme::Vector<double, Size> v{20};
        v /= 4;
        std::array<bool, Size> results{};
        for (std::int32_t i = 0; i < Size; ++i) {
            results[i] = v[i] == 5;
        }
        auto error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector /= Operator Error\n";
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