#include <iostream>
#include <xme/math/glsl_mapping.hpp>
#include <xme/math/vector.hpp>

namespace math = xme::math;

math::vec3 fv3{1.5, 2, 3};

int test_access() {
    int errors = 0;
    {
        math::vec3 v{1, 5, 3};
        bool error = v[0] != 1 || v[1] != 5 || v[2] != 3;
        if(error) {
            std::cerr << "xme::Vector::operator[] error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{2};
        bool error = math::get<0>(v) != 2 || math::get<1>(v) != 2 || math::get<2>(v) != 2;
        if(error) {
            std::cerr << "xme::Vector get error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{1, math::vec2(5, 2)};
        auto b     = begin(v);
        bool error = *(b++) != 1 || *(b++) != 5 || *(b++) != 2;
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
        auto v     = -fv3;
        bool error = v[0] != -1.5 || v[1] != -2 || v[2] != -3;
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
        math::vec3 v{fv3 + 2};
        bool error = v[0] != 3.5 || v[1] != 4 || v[2] != 5;
        if(error) {
            std::cerr << "xme::Vector::operator+ 1 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{fv3 + fv3};
        bool error = v[0] != 3 || v[1] != 4 || v[2] != 6;
        if(error) {
            std::cerr << "xme::Vector::operator+ 2 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{fv3 - 2};
        bool error = v[0] != -0.5 || v[1] != 0 || v[2] != 1;
        if(error) {
            std::cerr << "xme::Vector::operator- 1 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{
            fv3 - math::vec3{math::vec2(5, 1), 2}
        };
        bool error = v[0] != -3.5 || v[1] != 1 || v[2] != 1;
        if(error) {
            std::cerr << "xme::Vector::operator- 2 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{fv3 * 3};
        bool error = v[0] != 4.5 || v[1] != 6 || v[2] != 9;
        if(error) {
            std::cerr << "xme::Vector::operator* 1 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{
            fv3 * math::vec3{5, 3, 4}
        };
        bool error = v[0] != 7.5 || v[1] != 6 || v[2] != 12;
        if(error) {
            std::cerr << "xme::Vector::operator* 2 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v1{5, 10, 20};
        math::vec3 v{v1 / 5};
        bool error = v[0] != 1 || v[1] != 2 || v[2] != 4;
        if(error) {
            std::cerr << "xme::Vector::operator/ 1 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{
            fv3 / math::vec3{1.5, 1, 3}
        };
        bool error = v[0] != 1 || v[1] != 2 || v[2] != 1;
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
        math::vec3 v{2, 5, 3};
        v          = math::vec3{3, 1, 4};
        bool error = v[0] != 3 || v[1] != 1 || v[2] != 4;
        if(error) {
            std::cerr << "xme::Vector assignment error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{2, 5, -1};
        v += 4;
        bool error = v[0] != 6 || v[1] != 9 || v[2] != 3;
        if(error) {
            std::cerr << "xme::Vector::operator+= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{2};
        v += math::vec3{1, 2, 7};
        bool error = v[0] != 3 || v[1] != 4 || v[2] != 9;
        if(error) {
            std::cerr << "xme::Vector::operator+= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{2};
        v -= 2;
        bool error = v[0] != 0 || v[1] != 0 || v[2] != 0;
        if(error) {
            std::cerr << "xme::Vector::operator-= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{2, 5, 0};
        v -= math::vec3{2, 3, -3};
        bool error = v[0] != 0 || v[1] != 2 || v[2] != 3;
        if(error) {
            std::cerr << "xme::Vector::operator-= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{2, -2, 5};
        v *= 3;
        bool error = v[0] != 6 || v[1] != -6 || v[2] != 15;
        if(error) {
            std::cerr << "xme::Vector::operator*= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{1, 5, -2};
        v *= math::vec3{-2, 3, -1};
        bool error = v[0] != -2 || v[1] != 15 || v[2] != 2;
        if(error) {
            std::cerr << "xme::Vector::operator*= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{7, 14, 35};
        v /= 7;
        bool error = v[0] != 1 || v[1] != 2 || v[2] != 5;
        if(error) {
            std::cerr << "xme::Vector::operator/= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec3 v{8, 14, -4};
        v /= math::vec3{2, 4, -1};
        bool error = v[0] != 4 || v[1] != 3.5 || v[2] != 4;
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
        math::vec3 v1{5};
        math::vec3 v2{7};
        bool error = v1 == v2;
        if(error) {
            std::cerr << "xme::Vector::operator== Error\n";
            ++errors;
        }
    }
    {
        math::vec3 v1{2, 5, 3};
        math::vec3 v2{2, 5, 3};
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
        auto l     = math::vec3{4, 3, 3}.length();
        bool error = l != std::sqrt(34.f);
        if(error) {
            std::cerr << "xme::Vector::length error\n";
            ++errors;
        }
    }
    {
        auto d = math::vec3{3, 3, 2}.dot(math::vec3{2, 8, 1});

        bool error = d != 32;
        if(error) {
            std::cerr << "xme::Vector::dot error\n";
            ++errors;
        }
    }
    {
        auto c1    = math::vec3{1, 0, 0}.cross(math::vec3{0, 5, 0});
        auto c2    = math::vec3{-3, 7, 0}.cross(math::vec3{2, 5, 0});
        bool error = c1 != math::vec3{0, 0, 5} || c2 != math::vec3{0, 0, -29};
        if(error) {
            std::cerr << "xme::Vector::cross error\n";
            ++errors;
        }
    }
    {
        auto d1    = math::vec3{}.distance(math::vec3{4, 3, 7});
        auto d2    = math::vec3{4, 3, 7}.distance(math::vec3{});
        bool error = d1 != std::sqrt(74.f) || d2 != std::sqrt(74.f);
        if(error) {
            std::cerr << "xme::Vector::distance error\n";
            ++errors;
        }
    }
    {
        math::vec3 v1{1, 1, 1};
        auto r1    = math::faceforward(v1, math::vec3{1, -1, 0}, math::vec3{0, 1, 0});
        bool error = r1 != math::vec3{1, 1, 1};
        r1         = v1.faceforward(math::vec3{1, 1, 0}, math::vec3{0, 1, 0});
        error      = r1 != math::vec3{-1, -1, -1};
        if(error) {
            std::cerr << "xme::Vector::faceforward error\n";
            ++errors;
        }
    }
    {
        math::vec3 v1{1, 1, 1};
        auto r1 = v1.reflect(math::vec3{0, 1, 0});
        auto r2 = v1.reflect(math::vec3{1, 0, 0});
        auto r3 = v1.reflect(math::vec3{0, 0, 1});

        bool error =
            r1 != math::vec3{1, -1, 1} || r2 != math::vec3{-1, 1, 1} || r3 != math::vec3{1, 1, -1};
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
