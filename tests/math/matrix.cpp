#include <iostream>
#include <xme/math/glsl_mapping.hpp>
#include <xme/math/matrix.hpp>

namespace math = xme::math;

int test_access() {
    int errors = 0;
    math::Matrix<float, 2, 3> m{math::vec3(2, 1, 3), math::vec3(8, 7, 6)};
    static_assert(std::is_same_v<decltype(m.row(0)), math::vec2>);
    static_assert(std::is_same_v<decltype(m.column(0)), math::vec3>);
    static_assert(std::is_same_v<decltype(m[0]), math::vec3&>);
    {
        bool error = m.row(0) != math::vec2{2, 8} || m.row(1) != math::vec2{1, 7};
        error |= m.row(2) != math::vec2{3, 6};
        if(error) {
            std::cerr << "xme::Matrix::row error\n";
            ++errors;
        }
    }
    {
        bool error = m.column(0) != math::vec3{2, 1, 3} || m.column(1) != math::vec3{8, 7, 6};
        if(error) {
            std::cerr << "xme::Matrix::column error\n";
            ++errors;
        }
    }
    {
        math::Matrix<float, 2, 3> m1{1};
        bool error = m1[0] != math::vec3{1, 0, 0} || m1[1] != math::vec3{0, 1, 0};
        if(error) {
            std::cerr << "xme::Matrix::operator[] error\n";
            ++errors;
        }
    }
    return errors;
}

int test_operators() {
    int errors = 0;
    {
        math::Matrix<float, 2, 3> m{math::vec3{5}, math::vec3{-3}};
        auto r1 = m + 2;
        auto r2 = m + math::Matrix<float, 2, 3>{2};

        bool error = r1[0] != math::vec3{7} || r1[1] != math::vec3{-1};
        error |= r2[0] != math::vec3{7, 5, 5} || r2[1] != math::vec3{-3, -1, -3};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix + operator error\n";
        }
    }
    {
        math::Matrix<float, 2, 3> m{math::vec3{5}, math::vec3{-3}};
        auto r1 = m - 2;
        auto r2 = m - math::Matrix<float, 2, 3>{2};

        bool error = r1[0] != math::vec3{3} || r1[1] != math::vec3{-5};
        error |= r2[0] != math::vec3{3, 5, 5} || r2[1] != math::vec3{-3, -5, -3};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix - operator error\n";
        }
    }
    {
        math::Matrix<float, 2, 3> m{math::vec3{5}, math::vec3{-3}};
        auto r = m * 4;

        bool error = r[0] != math::vec3{20} || r[1] != math::vec3{-12};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix * operator error\n";
        }
    }
    {
        math::Matrix<float, 2, 3> m{math::vec3{16}, math::vec3{120}};
        auto r = m / 4;

        bool error = r[0] != math::vec3{4} || r[1] != math::vec3{30};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix / operator error\n";
        }
    }
    {
        math::mat3 m{5};
        static_assert(std::is_same_v<decltype(-m), math::mat3>);

        bool error = -m != math::mat3{-5};
        if(error) {
            std::cerr << "xme::Matrix unary operator error\n";
            ++errors;
        }
    }
    return errors;
}

int test_self_operators() {
    int errors = 0;
    {
        math::mat3 m;
        m += 3;

        bool error = m[0] != math::vec3{4, 3, 3} || m[1] != math::vec3{3, 4, 3};
        error |= m[2] != math::vec3{3, 3, 4};

        m += math::mat3{3};

        error |= m[0] != math::vec3{7, 3, 3} || m[1] != math::vec3{3, 7, 3};
        error |= m[2] != math::vec3{3, 3, 7};
        if(error) {
            std::cerr << "xme::Matrix += operator error\n";
            ++errors;
        }
    }
    {
        math::mat3 m;
        m -= 3;

        bool error = m[0] != math::vec3{-2, -3, -3} || m[1] != math::vec3{-3, -2, -3};
        error |= m[2] != math::vec3{-3, -3, -2};

        m -= math::mat3{3};

        error |= m[0] != math::vec3{-5, -3, -3} || m[1] != math::vec3{-3, -5, -3};
        error |= m[2] != math::vec3{-3, -3, -5};
        if(error) {
            std::cerr << "xme::Matrix -= operator error\n";
            ++errors;
        }
    }
    {
        math::mat3 m;
        m *= 3;

        bool error = m[0] != math::vec3{3, 0, 0} || m[1] != math::vec3{0, 3, 0};
        error |= m[2] != math::vec3{0, 0, 3};
        if(error) {
            std::cerr << "xme::Matrix *= operator error\n";
            ++errors;
        }
    }
    {
        math::mat2 m;
        m /= 2;

        bool error = m[0] != math::vec2{0.5, 0} || m[1] != math::vec2{0, 0.5};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix /= operator error\n";
        }
    }
    return errors;
}

int test_matrix_multiplication() {
    int errors = 0;
    static_assert(std::is_same_v<decltype(math::mat2{} * math::vec2{}), math::vec2>);
    static_assert(std::is_same_v<decltype(math::mat3{} * math::vec3{}), math::vec3>);
    static_assert(std::is_same_v<decltype(math::mat4{} * math::vec4{}), math::vec4>);
    static_assert(
      std::is_same_v<decltype(math::Matrix<float, 4, 1>{} * math::vec4{}), math::Vector<float, 1>>);
    static_assert(std::is_same_v<decltype(math::mat3x2{} * math::vec3{}), math::vec2>);
    {
        math::mat4 m{2};
        auto v = m * math::vec4{5, 6, 7, 1};

        bool error = v != math::vec4{10, 12, 14, 2};
        if(error) {
            std::cerr << "xme::Matrix multiplication 1 Error\n";
            ++errors;
        }
    }
    {
        math::Matrix<float, 4, 2> m{
            math::vec2{1, 2},
            math::vec2{9, 9},
            math::vec2{1},
            math::vec2{5}
        };
        auto v = m * math::vec4{2};

        bool error = v != math::vec2{32, 34};
        if(error) {
            std::cerr << "xme::Matrix multiplication 2 error\n";
            ++errors;
        }
    }

    {
        math::mat2 m{
            math::vec2{1, 3},
            math::vec2{7, 4}
        };
        auto r = m * m;

        bool error = r[0] != math::vec2{22, 15} || r[1] != math::vec2{35, 37};
        if(error) {
            std::cerr << "xme::Matrix multiplication 3 Error";
            ++errors;
        }
    }
    return errors;
}

int test_basic_functions() {
    int errors = 0;
    {
        math::mat2 m{
            math::vec2{3, 4},
            math::vec2{1, 2}
        };
        bool error = determinant(m) != 2;

        if(error) {
            std::cerr << "xme::math::Matrix::determinant 2 error\n";
            ++errors;
        }
    }
    {
        math::mat3 m{
            math::vec3{5, 3, 1},
            math::vec3{7, 3, 4},
            math::vec3{9, 7, 8}
        };
        bool error = determinant(m) != -58;
        if(error) {
            std::cerr << "xme::math::Matrix::determinant 3 error\n";
            ++errors;
        }
    }

    {
        auto m     = math::outer_product(math::vec3{1, 5, 2}, math::vec2{5, 3});
        bool error = m[0] != math::vec3{5, 25, 10} || m[1] != math::vec3{3, 15, 6};
        if(error) {
            std::cerr << "xme::math::outer_product error\n";
            ++errors;
        }
    }

    {
        math::mat2 m1{
            math::vec2{1, 5},
            math::vec2{5, 3},
        };
        math::mat2 m2{
            math::vec2{6},
            math::vec2{3, 5},
        };
        auto r     = math::hadamard_product(m1, m2);
        bool error = r[0] != math::vec2{6, 30} || r[1] != math::vec2{15};
        if(error) {
            std::cerr << "xme::Matrix::hadamard_product error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_access();
    errors += test_operators();
    errors += test_self_operators();
    errors += test_matrix_multiplication();
    errors += test_basic_functions();
    return errors;
}
