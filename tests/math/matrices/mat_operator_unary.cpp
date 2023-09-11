#include "common.hpp"

template<std::size_t Cols, std::size_t Rows>
int testUnary() {
    int errors = 0;
    {
        xme::Matrix<float, Cols, Rows> m{5};
        static_assert(std::is_same_v<decltype(-m), xme::Matrix<float, Cols, Rows>>);

        bool error = -m != xme::Matrix<float, Cols, Rows>{-5};
        if(error) {
            std::cerr << "matrix unary operator error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testUnary<2, 3>();
    errors += testUnary<5, 3>();
    errors += testUnary<3, 1>();
    errors += testUnary<7, 2>();
    return errors;
}