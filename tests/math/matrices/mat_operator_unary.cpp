#include "common.hpp"

namespace math = xme::math;

template<std::size_t Cols, std::size_t Rows>
int test_unary() {
    int errors = 0;
    {
        math::Matrix<float, Cols, Rows> m{5};
        static_assert(std::is_same_v<decltype(-m), math::Matrix<float, Cols, Rows>>);

        bool error = -m != math::Matrix<float, Cols, Rows>{-5};
        if(error) {
            std::cerr << "matrix unary operator error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_unary<2, 3>();
    errors += test_unary<5, 3>();
    errors += test_unary<3, 1>();
    errors += test_unary<7, 2>();
    return errors;
}