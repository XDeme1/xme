#include <xme/math/math.hpp>
#include <algorithm>
#include <iostream>

bool isError(bool b) { return b == false; }

template<std::size_t Size>
int testMatrix() {
    int errors = 0;
    {
        xme::Matrix<float, Size, Size> m;

        std::array<bool, Size*Size> results{};
        for (auto i = 0; i < Size; ++i) {
            for (auto j = 0; j < Size; ++j) {
                if(i == j)
                    results[i*Size+j] = m[j][i] == 1;
                else
                    results[i*Size+j] = m[j][i] == 0;
            }
        }

        auto error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Matrix Error\n";
            ++errors;
        }
    }

    {
        xme::Matrix<float, Size, Size> m{5};

        std::array<bool, Size*Size> results{};
        for (auto i = 0; i < Size; ++i) {
            for (auto j = 0; j < Size; ++j) {
                if(i == j)
                    results[i*Size+j] = m[j][i] == 5;
                else
                    results[i*Size+j] = m[j][i] == 0;
            }
        }

        auto error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Matrix Error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testMatrix<2>(); 
    errors += testMatrix<3>(); 
    errors += testMatrix<4>(); 
    errors += testMatrix<5>(); 
    return errors;
}