#include <iostream>
#include <xme/math/glsl_mapping.hpp>
#include <xme/math/matrix.hpp>

namespace math = xme::math;

int test_access() {
    int errors = 0;
    math::mat4x4 m{
        math::vec4{2, 8, 3, 5},
        math::vec4{1, 7, 5, 3},
        math::vec4{2, 8, 3, 5},
        math::vec4{1, 7, 5, 3}
    };
    static_assert(std::is_same_v<decltype(m.row(0)), math::vec4>);
    static_assert(std::is_same_v<decltype(m.column(0)), math::vec4>);
    static_assert(std::is_same_v<decltype(m[0]), math::vec4&>);
    {
        bool error = m.row(0) != math::vec4{2, 1, 2, 1} || m.row(1) != math::vec4{8, 7, 8, 7};
        error |= m.row(2) != math::vec4{3, 5, 3, 5} || m.row(3) != math::vec4{5, 3, 5, 3};
        if(error) {
            std::cerr << "xme::Matrix::row error\n";
            ++errors;
        }
    }
    {
        bool error = m.column(0) != math::vec4{2, 8, 3, 5} || m.column(1) != math::vec4{1, 7, 5, 3};
        error |= m.column(2) != math::vec4{2, 8, 3, 5} || m.column(3) != math::vec4{1, 7, 5, 3};
        if(error) {
            std::cerr << "xme::Matrix::column error\n";
            ++errors;
        }
    }
    {
        bool error = m[0] != math::vec4{2, 8, 3, 5} || m[1] != math::vec4{1, 7, 5, 3};
        error |= m[2] != math::vec4{2, 8, 3, 5} || m[3] != math::vec4{1, 7, 5, 3};
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
        math::mat4 m{math::vec4{5}, math::vec4{-3}, math::vec4{1}, math::vec4{7}};
        auto r1 = m + 2;
        auto r2 = m + math::mat4{2};

        bool error = r1[0] != math::vec4{7} || r1[1] != math::vec4{-1} || r1[2] != math::vec4{3}
                     || r1[3] != math::vec4{9};
        error |= r2[0] != math::vec4{7, 5, 5, 5} || r2[1] != math::vec4{-3, -1, -3, -3}
                 || r2[2] != math::vec4{1, 1, 3, 1} || r2[3] != math::vec4{7, 7, 7, 9};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix + operator error\n";
        }
    }
    {
        math::mat4 m{math::vec4{5}, math::vec4{-3}, math::vec4{1}, math::vec4{7}};
        auto r1 = m - 2;
        auto r2 = m - math::mat4{2};

        bool error = r1[0] != math::vec4{3} || r1[1] != math::vec4{-5} || r1[2] != math::vec4{-1}
                     || r1[3] != math::vec4{5};
        error |= r2[0] != math::vec4{3, 5, 5, 5} || r2[1] != math::vec4{-3, -5, -3, -3}
                 || r2[2] != math::vec4{1, 1, -1, 1} || r2[3] != math::vec4{7, 7, 7, 5};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix - operator error\n";
        }
    }
    {
        math::mat4 m{math::vec4{5}, math::vec4{-3}, math::vec4{1}, math::vec4{7}};
        auto r = m * 4;

        bool error = r[0] != math::vec4{20} || r[1] != math::vec4{-12} || r[2] != math::vec4{4}
                     || r[3] != math::vec4{28};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix * operator error\n";
        }
    }
    {
        math::mat4 m{math::vec4{16}, math::vec4{120}, math::vec4{60}, math::vec4{40}};
        auto r = m / 4;

        bool error = r[0] != math::vec4{4} || r[1] != math::vec4{30} || r[2] != math::vec4{15}
                     || r[3] != math::vec4{10};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix / operator error\n";
        }
    }
    {
        math::mat4 m{5};
        static_assert(std::is_same_v<decltype(-m), math::mat4>);

        bool error = -m != math::mat4{-5};
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
        math::mat4 m;
        m += 3;

        bool error = m[0] != math::vec4{4, 3, 3, 3} || m[1] != math::vec4{3, 4, 3, 3}
                     || m[2] != math::vec4{3, 3, 4, 3} || m[3] != math::vec4{3, 3, 3, 4};

        m += math::mat4{3};

        error |= m[0] != math::vec4{7, 3, 3, 3} || m[1] != math::vec4{3, 7, 3, 3}
                 || m[2] != math::vec4{3, 3, 7, 3} || m[3] != math::vec4{3, 3, 3, 7};
        if(error) {
            std::cerr << "xme::Matrix += operator error\n";
            ++errors;
        }
    }
    {
        math::mat4 m;
        m -= 3;

        bool error = m[0] != math::vec4{-2, -3, -3, -3} || m[1] != math::vec4{-3, -2, -3, -3}
                     || m[2] != math::vec4{-3, -3, -2, -3} || m[3] != math::vec4{-3, -3, -3, -2};

        m -= math::mat4{3};

        error |= m[0] != math::vec4{-5, -3, -3, -3} || m[1] != math::vec4{-3, -5, -3, -3}
                 || m[2] != math::vec4{-3, -3, -5, -3} || m[3] != math::vec4{-3, -3, -3, -5};
        if(error) {
            std::cerr << "xme::Matrix -= operator error\n";
            ++errors;
        }
    }
    {
        math::mat4 m;
        m *= 3;

        bool error = m[0] != math::vec4{3, 0, 0, 0} || m[1] != math::vec4{0, 3, 0, 0}
                     || m[2] != math::vec4{0, 0, 3, 0} || m[3] != math::vec4{0, 0, 0, 3};
        if(error) {
            std::cerr << "xme::Matrix *= operator error\n";
            ++errors;
        }
    }
    {
        math::mat4 m;
        m /= 2;

        bool error = m[0] != math::vec4{0.5, 0, 0, 0} || m[1] != math::vec4{0, 0.5, 0, 0}
                     || m[2] != math::vec4{0, 0, 0.5, 0} || m[3] != math::vec4{0, 0, 0, 0.5};
        if(error) {
            ++errors;
            std::cerr << "xme::Matrix /= operator error\n";
        }
    }
    return errors;
}

int test_matrix_multiplication() {
    int errors = 0;
    static_assert(std::is_same_v<decltype(math::mat4{} * math::vec4{}), math::vec4>);
    static_assert(std::is_same_v<decltype(math::Matrix<float, 4, 1>{} * math::vec4{}),
        math::Vector<float, 1>>);
    static_assert(std::is_same_v<decltype(math::mat4x2{} * math::vec4{}), math::vec2>);
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
        math::mat4 m{
            math::vec4{1,  3, 5, 3},
            math::vec4{7,  4, 3, 1},
            math::vec4{1,  2, 6, 1},
            math::vec4{-1, 7, 0, 6},
        };
        auto r = m * m;

        bool error = r[0] != math::vec4{24, 46, 44, 29} || r[1] != math::vec4{37, 50, 65, 34}
                     || r[2] != math::vec4{20, 30, 47, 17} || r[3] != math::vec4{42, 67, 16, 40};
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
        math::mat4 m{
            math::vec4{5, 3,  1,  2},
            math::vec4{6, 7,  3,  4},
            math::vec4{9, 7,  -3, 8},
            math::vec4{9, -8, -3, 1}
        };
        bool error = m.determinant() != -498;
        if(error) {
            std::cerr << "xme::Matrix::determinant 4 error\n";
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
