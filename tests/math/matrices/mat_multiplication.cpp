#include <xme/math/math.hpp>
#include <algorithm>
#include <iostream>

namespace math = xme::math;

bool isError(bool b) { return b == false; }

int test_matrix2() {
    int errors = 0;
    math::mat2 m{math::vec2{1, 3}, math::vec2{7, 4}};
    auto r = m * m;
    std::array results = std::to_array({
        r[0] == math::vec2(22, 15),
        r[1] == math::vec2(35, 37),
    });
    
    bool error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "Matrix2x2 Multiplication Error";
        ++errors;
    }
    return errors;    
}

int test_matrix3() {
    int errors = 0;
    math::mat3 m{math::vec3{1, 3, 6}, math::vec3{7, 4, 2}, math::vec3{-5, 2, 8}};
    auto r = m * m;
    auto results = std::to_array({
        r[0] == math::vec3(-8, 27, 60),
        r[1] == math::vec3(25, 41, 66),
        r[2] == math::vec3(-31, 9, 38),
    });
    
    bool error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "Matrix3x3 Multiplication Error";
        ++errors;
    }
    return errors;    
}

int test_matrix() {
    int errors = 0;
    {
        constexpr auto v1 = math::vec2(1, 2);
        math::Matrix<float, 3, 2> m1{v1, v1, v1};
        math::Matrix<float, 2, 3> m2{math::vec3(1), math::vec3(2)};
        auto m3 = m1 * m2;
        auto m4 = m2 * m1;
        static_assert(std::is_same_v<decltype(m3), math::Matrix<float, 2, 2>>);
        static_assert(std::is_same_v<decltype(m4), math::Matrix<float, 3, 3>>);

        auto results = std::to_array({
            m3[0] == math::vec2{3, 6},
            m3[1] == math::vec2{6, 12},

            m4[0] == math::vec3{5},
            m4[1] == math::vec3{5},
            m4[2] == math::vec3{5},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "2x3 x 3x2 && 3x2 x 2x3 Matrix Multiplication Error\n";
            ++errors;
        }
    }

    {
        math::Matrix<float, 4, 2> m1{math::vec2(2), math::vec2(5), math::vec2(7), math::vec2(1)};
        math::Matrix<float, 3, 4> m2{math::vec4(5), math::vec4(2), math::vec4(7)};
        auto m3 = m1 * m2;
        static_assert(std::is_same_v<decltype(m3), math::Matrix<float, 3, 2>>);

        auto results = std::to_array({
            m3[0] == math::vec2(75),
            m3[1] == math::vec2(30),
            m3[2] == math::vec2(105),
        });
        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "2x4 x 4x3 Matrix Multiplication Error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_matrix2();
    errors += test_matrix3();
    errors += test_matrix();
    return errors;
}