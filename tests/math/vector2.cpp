#include <iostream>
#include <xme/math/glsl_mapping.hpp>
#include <xme/math/vector.hpp>

namespace math = xme::math;

math::vec2 fv2{1.5, 2};

int test_access() {
    int errors = 0;
    {
        math::vec2 v{1, 5};
        bool error = v[0] != 1 || v[1] != 5;
        if(error) {
            std::cerr << "xme::Vector::operator[] error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{2};
        bool error = math::get<0>(v) != 2 || math::get<1>(v) != 2;
        if(error) {
            std::cerr << "xme::Vector get error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{1, 5};
        auto b     = begin(v);
        bool error = *(b++) != 1 || *(b++) != 5;
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
        auto v     = -fv2;
        bool error = v[0] != -1.5 || v[1] != -2;
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
        math::vec2 v{fv2 + 2};
        bool error = v[0] != 3.5 || v[1] != 4;
        if(error) {
            std::cerr << "xme::Vector::operator+ 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{fv2 + fv2};
        bool error = v[0] != 3 || v[1] != 4;
        if(error) {
            std::cerr << "xme::Vector::operator+ 2 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{fv2 - 2};
        bool error = v[0] != -0.5 || v[1] != 0;
        if(error) {
            std::cerr << "xme::Vector::operator- 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{
            fv2 - math::vec2{5, 1}
        };
        bool error = v[0] != -3.5 || v[1] != 1;
        if(error) {
            std::cerr << "xme::Vector::operator- 2 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{fv2 * 3};
        bool error = v[0] != 4.5 || v[1] != 6;
        if(error) {
            std::cerr << "xme::Vector::operator* 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{
            fv2 * math::vec2{5, 3}
        };
        bool error = v[0] != 7.5 || v[1] != 6;
        if(error) {
            std::cerr << "xme::Vector::operator* 2 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v1{5, 10};
        math::vec2 v{v1 / 5};
        bool error = v[0] != 1 || v[1] != 2;
        if(error) {
            std::cerr << "xme::Vector::operator/ 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{
            fv2 / math::vec2{1.5, 1}
        };
        bool error = v[0] != 1 || v[1] != 2;
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
        math::vec2 v{2, 5};
        v          = math::vec2{3, 1};
        bool error = v[0] != 3 || v[1] != 1;
        if(error) {
            std::cerr << "xme::Vector assignment error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{2, 5};
        v += 4;
        bool error = v[0] != 6 || v[1] != 9;
        if(error) {
            std::cerr << "xme::Vector::operator+= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{2};
        v += math::vec2{1, 2};
        bool error = v[0] != 3 || v[1] != 4;
        if(error) {
            std::cerr << "xme::Vector::operator+= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{2};
        v -= 2;
        bool error = v[0] != 0 || v[1] != 0;
        if(error) {
            std::cerr << "xme::Vector::operator-= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{2, 5};
        v -= math::vec2{2, 3};
        bool error = v[0] != 0 || v[1] != 2;
        if(error) {
            std::cerr << "xme::Vector::operator-= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{2, -2};
        v *= 3;
        bool error = v[0] != 6 || v[1] != -6;
        if(error) {
            std::cerr << "xme::Vector::operator*= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{1, 5};
        v *= math::vec2{-2, 3};
        bool error = v[0] != -2 || v[1] != 15;
        if(error) {
            std::cerr << "xme::Vector::operator*= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{7, 14};
        v /= 7;
        bool error = v[0] != 1 || v[1] != 2;
        if(error) {
            std::cerr << "xme::Vector::operator/= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{8, 14};
        v /= math::vec2{2, 4};
        bool error = v[0] != 4 || v[1] != 3.5;
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
        math::vec2 v1{5};
        math::vec2 v2{7};
        bool error = v1 == v2;
        if(error) {
            std::cerr << "xme::Vector::operator== Error\n";
            ++errors;
        }
    }
    {
        math::vec2 v1{2, 5};
        math::vec2 v2{2, 5};
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
        auto l     = math::vec2(4, 3).length();
        bool error = l != 5;
        if(error) {
            std::cerr << "xme::Vector::length error\n";
            ++errors;
        }
    }
    {
        auto d = math::vec2{3, 3}.dot(math::vec2{2, 8});

        bool error = d != 30;
        if(error) {
            std::cerr << "xme::Vector::dot error\n";
            ++errors;
        }
    }
    {
        auto d1    = math::vec2{}.distance(math::vec2{4, 3});
        auto d2    = math::vec2{4, 3}.distance(math::vec2{});
        bool error = d1 != 5 || d2 != 5;
        if(error) {
            std::cerr << "xme::Vector::distance error\n";
            ++errors;
        }
    }
    {
        math::vec2 v1{1, 1};
        auto r1    = math::faceforward(v1, math::vec2{1, -1}, math::vec2{0, 1});
        bool error = r1 != math::vec2{1, 1};
        r1         = math::faceforward(v1, math::vec2{1, 1}, math::vec2{0, 1});
        error      = r1 != math::vec2{-1, -1};
        if(error) {
            std::cerr << "xme::Vector::faceforward error\n";
            ++errors;
        }
    }
    {
        math::vec2 v1{1, 1};
        auto r1 = v1.reflect(math::vec2{0, 1});
        auto r2 = v1.reflect(math::vec2{1, 0});

        bool error = r1 != math::vec2{1, -1} || r2 != math::vec2{-1, 1};
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
