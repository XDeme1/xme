#include <iostream>
#include <cmath>
#include <xme/math/glsl_mapping.hpp>
#include <xme/math/vector.hpp>

namespace math = xme::math;

math::vec4 fv4{1.5, 2, 3, 4};

int test_access() {
    int errors = 0;
    {
        math::vec4 v{math::vec2(1, 5), 3, 4};
        bool error = v[0] != 1 || v[1] != 5 || v[2] != 3 || v[3] != 4;
        if(error) {
            std::cerr << "xme::Vector::operator[] error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{2};
        bool error = math::get<0>(v) != 2 || math::get<1>(v) != 2 || math::get<2>(v) != 2
                     || math::get<3>(v) != 2;
        if(error) {
            std::cerr << "xme::Vector get error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{1, 5, math::vec2(2, 4)};
        auto b     = begin(v);
        bool error = *(b++) != 1 || *(b++) != 5 || *(b++) != 2 || *(b++) != 4;
        error |= b != end(v);
        if(error) {
            std::cerr << "xme::Vector begin/end error\n";
            ++errors;
        }
    }
    return errors;
}

int test_unary() {
    int errors = 0;
    {
        auto v     = -fv4;
        bool error = v[0] != -1.5 || v[1] != -2 || v[2] != -3 || v[3] != -4;
        if(error) {
            std::cerr << "xme::Vector unary - error\n";
            ++errors;
        }
    }
    return errors;
}

int test_arithmetic() {
    int errors = 0;
    {
        math::vec4 v{fv4 + 2};
        bool error = v[0] != 3.5 || v[1] != 4 || v[2] != 5 || v[3] != 6;
        if(error) {
            std::cerr << "xme::Vector::operator+ 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{fv4 + fv4};
        bool error = v[0] != 3 || v[1] != 4 || v[2] != 6 || v[3] != 8;
        if(error) {
            std::cerr << "xme::Vector::operator+ 2 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{fv4 - 2};
        bool error = v[0] != -0.5 || v[1] != 0 || v[2] != 1 || v[3] != 2;
        if(error) {
            std::cerr << "xme::Vector::operator- 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{
            fv4 - math::vec4{5, math::vec2(1, 2), 3}
        };
        bool error = v[0] != -3.5 || v[1] != 1 || v[2] != 1 || v[3] != 1;
        if(error) {
            std::cerr << "xme::Vector::operator- 2 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{fv4 * 3};
        bool error = v[0] != 4.5 || v[1] != 6 || v[2] != 9 || v[3] != 12;
        if(error) {
            std::cerr << "xme::Vector::operator* 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{
            fv4 * math::vec4{math::vec2(5, 3), math::vec2(4, 3)}
        };
        bool error = v[0] != 7.5 || v[1] != 6 || v[2] != 12 || v[3] != 12;
        if(error) {
            std::cerr << "xme::Vector::operator* 2 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v1{math::vec3(5, 10, 20), 50};
        math::vec4 v{v1 / 5};
        bool error = v[0] != 1 || v[1] != 2 || v[2] != 4 || v[3] != 10;
        if(error) {
            std::cerr << "xme::Vector::operator/ 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{
            fv4 / math::vec4{1.5, math::vec3(1, 3, 2)}
        };
        bool error = v[0] != 1 || v[1] != 2 || v[2] != 1 || v[3] != 2;
        if(error) {
            std::cerr << "xme::Vector::operator/ 2 error\n";
            ++errors;
        }
    }
    return errors;
}

int test_self() {
    int errors = 0;
    {
        math::vec4 v{2, 5, 3, 5};
        v          = math::vec4{3, 1, 4, 1};
        bool error = v[0] != 3 || v[1] != 1 || v[2] != 4 || v[3] != 1;
        if(error) {
            std::cerr << "xme::Vector assignment error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{2, 5, -1, 5};
        v += 4;
        bool error = v[0] != 6 || v[1] != 9 || v[2] != 3 || v[3] != 9;
        if(error) {
            std::cerr << "xme::Vector::operator+= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{2};
        v += math::vec4{1, 2, 7, -3};
        bool error = v[0] != 3 || v[1] != 4 || v[2] != 9 || v[3] != -1;
        if(error) {
            std::cerr << "xme::Vector::operator+= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{2};
        v -= 2;
        bool error = v[0] != 0 || v[1] != 0 || v[2] != 0 || v[3] != 0;
        if(error) {
            std::cerr << "xme::Vector::operator-= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{2, 5, 0, -3};
        v -= math::vec4{2, 3, -3, 2};
        bool error = v[0] != 0 || v[1] != 2 || v[2] != 3 || v[3] != -5;
        if(error) {
            std::cerr << "xme::Vector::operator-= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{2, -2, 5, -5};
        v *= 3;
        bool error = v[0] != 6 || v[1] != -6 || v[2] != 15 || v[3] != -15;
        if(error) {
            std::cerr << "xme::Vector::operator*= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{1, 5, -2, -1};
        v *= math::vec4{-2, 3, -1, -5};
        bool error = v[0] != -2 || v[1] != 15 || v[2] != 2 || v[3] != 5;
        if(error) {
            std::cerr << "xme::Vector::operator*= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{7, 14, 35, 63};
        v /= 7;
        bool error = v[0] != 1 || v[1] != 2 || v[2] != 5 || v[3] != 9;
        if(error) {
            std::cerr << "xme::Vector::operator/= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{8, 14, -4, 9};
        v /= math::vec4{2, 4, -1, 3};
        bool error = v[0] != 4 || v[1] != 3.5 || v[2] != 4 || v[3] != 3;
        if(error) {
            std::cerr << "xme::Vector::operator/= 2 error\n";
            ++errors;
        }
    }
    return errors;
}

int test_equality() {
    int errors = 0;
    {
        math::vec4 v1{5};
        math::vec4 v2{7};
        bool error = v1 == v2;
        if(error) {
            std::cerr << "xme::Vector::operator== Error\n";
            ++errors;
        }
    }
    {
        math::vec4 v1{2, 5, 3, -3};
        math::vec4 v2{2, 5, 3, -3};
        bool error = v1 != v2;
        if(error) {
            std::cerr << "xme::Vector::operator!= Error\n";
            ++errors;
        }
    }
    return errors;
}

int test_operations() {
    int errors = 0;
    {
        auto l     = math::vec4{4, 3, 3, 5}.length();
        bool error = l != std::sqrt(59.f);
        if(error) {
            std::cerr << "xme::Vector::length error\n";
            ++errors;
        }
    }
    {
        auto d = math::dot(math::vec4{3, 3, 2, 5}, math::vec4{2, 8, 1, 2});

        bool error = d != 42;
        if(error) {
            std::cerr << "xme::Vector::dot error\n";
            ++errors;
        }
    }
    {
        auto d1    = math::distance(math::vec4{}, math::vec4{4, 3, 7, 3});
        auto d2    = math::distance(math::vec4{4, 3, 7, 3}, math::vec4{});
        bool error = d1 != std::sqrt(83.f) || d2 != std::sqrt(83.f);
        if(error) {
            std::cerr << "xme::Vector::distance error\n";
            ++errors;
        }
    }
    {
        math::vec4 v1{1, 1, 1, 1};
        auto r1    = math::faceforward(v1, math::vec4{1, -1, 0, 0}, math::vec4{0, 1, 0, 0});
        bool error = r1 != math::vec4{1, 1, 1, 1};

        r1    = math::faceforward(v1, math::vec4{1, 1, 0, 0}, math::vec4{0, 1, 0, 0});
        error = r1 != math::vec4{-1, -1, -1, -1};
        if(error) {
            std::cerr << "xme::Vector::faceforward error\n";
            ++errors;
        }
    }
    {
        math::vec4 v1{1, 1, 1, 1};
        auto r1 = math::reflect(v1, math::vec4{0, 1, 0, 0});
        auto r2 = math::reflect(v1, math::vec4{1, 0, 0, 0});
        auto r3 = math::reflect(v1, math::vec4{0, 0, 1, 0});

        bool error = r1 != math::vec4{1, -1, 1, 1} || r2 != math::vec4{-1, 1, 1, 1}
                     || r3 != math::vec4{1, 1, -1, 1};
        if(error) {
            std::cerr << "xme::Vector::reflect error\n";
            ++errors;
        }
    }

    return errors;
}

int main() {
    int errors = 0;
    errors += test_access();
    errors += test_arithmetic();
    errors += test_self();
    errors += test_equality();
    errors += test_operations();
    return errors;
}
