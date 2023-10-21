#include "common.hpp"

namespace math = xme::math;

int test_access() {
    int errors = 0;
    math::Matrix<float, 2, 3> m{math::vec3(2, 1, 3), math::vec3(8, 7, 6)};
    static_assert(std::is_same_v<decltype(m.row(0)), math::vec2>);
    static_assert(std::is_same_v<decltype(m.column(0)), math::vec3>);
    static_assert(std::is_same_v<decltype(m[0]), math::vec3&>);
    {
        std::array results = std::to_array({
            m.row(0) == math::vec2(2, 8),
            m.row(1) == math::vec2(1, 7),
            m.row(2) == math::vec2(3, 6),
        });

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Matrix::row(std::size_t) Error\n";
            ++errors;
        }
    }

    {
        std::array results = std::to_array({
            m.column(0) == math::vec3(2, 1, 3),
            m.column(1) == math::vec3(8, 7, 6),
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Matrix::column(std::size_t) Error\n";
            ++errors;
        }
    }

    {
        std::array results = std::to_array({
            m[0] == math::vec3(2, 1, 3),
            m[1] == math::vec3(8, 7, 6),
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Matrix::operator[](std::size_t) Error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_access();
    return errors;
}