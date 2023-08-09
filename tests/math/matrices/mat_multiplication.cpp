#include <xme/math/math.hpp>
#include <algorithm>
#include <iostream>

bool isError(bool b) { return b == false; }

int testMatrix2() {
    int errors = 0;
    xme::mat2 m{xme::vec2{1, 3}, xme::vec2{7, 4}};
    auto r = m * m;
    std::array results = std::to_array({
        r[0] == xme::vec2(22, 15),
        r[1] == xme::vec2(35, 37),
    });
    
    bool error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "Matrix2x2 Multiplication Error";
        ++errors;
    }
    return errors;    
}

int testMatrix3() {
    int errors = 0;
    xme::mat3 m{xme::vec3{1, 3, 6}, xme::vec3{7, 4, 2}, xme::vec3{-5, 2, 8}};
    auto r = m * m;
    auto results = std::to_array({
        r[0] == xme::vec3(-8, 27, 60),
        r[1] == xme::vec3(25, 41, 66),
        r[2] == xme::vec3(-31, 9, 38),
    });
    
    bool error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "Matrix3x3 Multiplication Error";
        ++errors;
    }
    return errors;    
}

int testMatrix() {
    int errors = 0;
    {
        constexpr auto v1 = xme::vec2(1, 2);
        xme::Matrix<float, 3, 2> m1{v1, v1, v1};
        xme::Matrix<float, 2, 3> m2{xme::vec3(1), xme::vec3(2)};
        auto m3 = m1 * m2;
        auto m4 = m2 * m1;
        static_assert(std::is_same_v<decltype(m3), xme::Matrix<float, 2, 2>>);
        static_assert(std::is_same_v<decltype(m4), xme::Matrix<float, 3, 3>>);

        auto results = std::to_array({
            m3[0] == xme::vec2{3, 6},
            m3[1] == xme::vec2{6, 12},

            m4[0] == xme::vec3{5},
            m4[1] == xme::vec3{5},
            m4[2] == xme::vec3{5},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "2x3 x 3x2 && 3x2 x 2x3 Matrix Multiplication Error\n";
            ++errors;
        }
    }

    {
        xme::Matrix<float, 4, 2> m1{xme::vec2(2), xme::vec2(5), xme::vec2(7), xme::vec2(1)};
        xme::Matrix<float, 3, 4> m2{xme::vec4(5), xme::vec4(2), xme::vec4(7)};
        auto m3 = m1 * m2;
        static_assert(std::is_same_v<decltype(m3), xme::Matrix<float, 3, 2>>);

        auto results = std::to_array({
            m3[0] == xme::vec2(75),
            m3[1] == xme::vec2(30),
            m3[2] == xme::vec2(105),
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
    errors += testMatrix2();
    errors += testMatrix3();
    errors += testMatrix();
    return errors;
}