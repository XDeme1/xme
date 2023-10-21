#include "common.hpp"

namespace math = xme::math;

int test_matrix_vector() {
    int errors = 0;
    static_assert(std::is_same_v<decltype(math::mat2{}*math::vec2{}), math::vec2>);
    static_assert(std::is_same_v<decltype(math::mat3{}*math::vec3{}), math::vec3>);
    static_assert(std::is_same_v<decltype(math::mat4{}*math::vec4{}), math::vec4>);
    {
        math::mat4 m{2};
        math::vec4 v{5, 6, 7, 1};

        bool error = (m * v) != math::vec4{10, 12, 14, 2};
        if(error) {
            std::cerr << "mat4 * vec4 multiplication Error\n";
            ++errors;
        }
    }

    static_assert(std::is_same_v<decltype(math::Matrix<float, 4, 1>{}*math::vec4{}), math::Vector<float, 1>>);
    static_assert(std::is_same_v<decltype(math::Matrix<float, 3, 2>{}*math::vec3{}), math::vec2>);
    {
        math::Matrix<float, 4, 2> m{math::vec2{1, 2}, math::vec2{9, 9}, math::vec2{1}, math::vec2{5}};
        math::vec4 v{2};

        bool error = (m * v) != math::vec2{32, 34};
        if(error) {
            std::cerr << "mat4x2 * vec4 multiplication error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_matrix_vector();
    return errors;
}