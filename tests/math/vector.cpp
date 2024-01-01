#include <iostream>
#include <xme/math/vector.hpp>
#include <xme/math/normal.hpp>
#include <xme/math/glsl_mapping.hpp>

namespace math = xme::math;

math::Vector<float, 5> fv5{1.5, 2, 3, 4, 5};
static_assert(std::is_trivial_v<decltype(fv5)>);

void test_deduction_guide() {
    math::Vector v1{1, 5, 1.5f, 1, 2};
    math::Vector v2{2ul, 2ul, 2, 2, 2};
    math::Vector v3{v1};
    static_assert(std::is_same_v<decltype(v1), math::Vector<float, 5>>);
    static_assert(std::is_same_v<decltype(v2), math::Vector<unsigned long, 5>>);
    static_assert(std::is_same_v<decltype(v3), decltype(v1)>);
}

int test_access() {
    int errors = 0;
    {
        math::Vector<float, 5> v{1, 5, 3, 2, 2};
        bool error = v[0] != 1 || v[1] != 5 || v[2] != 3 || v[3] != 2 || v[4] != 2;
        if(error) {
            std::cerr << "xme::Vector::operator[] error\n";
            ++errors;
        }
    }
    return errors;
}

int test_unary() {
    int errors = 0;
    {
        auto v     = -fv5;
        bool error = v[0] != -1.5 || v[1] != -2 || v[2] != -3 || v[3] != -4 || v[4] != -5;
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
        math::Vector<float, 5> v{fv5 + 2.f};
        bool error = v[0] != 3.5 || v[1] != 4 || v[2] != 5 || v[3] != 6 || v[4] != 7;
        if(error) {
            std::cerr << "xme::Vector::operator+ 1 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{fv5 + fv5};
        bool error = v[0] != 3 || v[1] != 4 || v[2] != 6 || v[3] != 8 || v[4] != 10;
        if(error) {
            std::cerr << "xme::Vector::operator+ 2 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{fv5 - 2.f};
        bool error = v[0] != -0.5 || v[1] != 0 || v[2] != 1 || v[3] != 2 || v[4] != 3;
        if(error) {
            std::cerr << "xme::Vector::operator- 1 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{
            fv5 - math::Vector<float, 5>{5, 1, 3, 1, 5}
        };
        bool error = v[0] != -3.5 || v[1] != 1 || v[2] != 0 || v[3] != 3 || v[4] != 0;
        if(error) {
            std::cerr << "xme::Vector::operator- 2 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{fv5 * 3.f};
        bool error = v[0] != 4.5 || v[1] != 6 || v[2] != 9 || v[3] != 12 || v[4] != 15;
        if(error) {
            std::cerr << "xme::Vector::operator* 1 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{
            fv5 * math::Vector<float, 5>{5, 3, 1, 2, 1}
        };
        bool error = v[0] != 7.5 || v[1] != 6 || v[2] != 3 || v[3] != 8 || v[4] != 5;
        if(error) {
            std::cerr << "xme::Vector::operator* 2 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v1{5, 10, 15, 5, 20};
        math::Vector<float, 5> v{v1 / 5.f};
        bool error = v[0] != 1 || v[1] != 2 || v[2] != 3 || v[3] != 1 || v[4] != 4;
        if(error) {
            std::cerr << "xme::Vector::operator/ 1 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{
            fv5 / math::Vector<float, 5>{1.5, 1, 3, 2, 5}
        };
        bool error = v[0] != 1 || v[1] != 2 || v[2] != 1 || v[3] != 2 || v[4] != 1;
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
        math::Vector<float, 5> v{2, 5, 1, 2, 1};
        v          = math::Vector<float, 5>{3, 1, 6, 3, 2};
        bool error = v[0] != 3 || v[1] != 1 || v[2] != 6 || v[3] != 3 || v[4] != 2;
        if(error) {
            std::cerr << "xme::Vector assignment error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{2, 5, 3, 1, 2};
        v += 4.f;
        bool error = v[0] != 6 || v[1] != 9 || v[2] != 7 || v[3] != 5 || v[4] != 6;
        if(error) {
            std::cerr << "xme::Vector::operator+= 1 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{2, 2, 5, 3, 7};
        v += math::Vector<float, 5>{1, 2, 2, 1, 3};
        bool error = v[0] != 3 || v[1] != 4 || v[2] != 7 || v[3] != 4 || v[4] != 10;
        if(error) {
            std::cerr << "xme::Vector::operator+= 2 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{2, 2, 5, 3, 3};
        v -= 2.f;
        bool error = v[0] != 0 || v[1] != 0 || v[2] != 3 || v[3] != 1 || v[4] != 1;
        if(error) {
            std::cerr << "xme::Vector::operator-= 1 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{2, 5, 3, 2, 8};
        v -= math::Vector<float, 5>{2, 3, 7, 1, 5};
        bool error = v[0] != 0 || v[1] != 2 || v[2] != -4 || v[3] != 1 || v[4] != 3;
        if(error) {
            std::cerr << "xme::Vector::operator-= 2 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{2, -2, 3, 1, 5};
        v *= 3.f;
        bool error = v[0] != 6 || v[1] != -6 || v[2] != 9 || v[3] != 3 || v[4] != 15;
        if(error) {
            std::cerr << "xme::Vector::operator*= 1 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{1, 5, 3, 1, 4};
        v *= math::Vector<float, 5>{-2, 3, 3, -1, 2};
        bool error = v[0] != -2 || v[1] != 15 || v[2] != 9 || v[3] != -1 || v[4] != 8;
        if(error) {
            std::cerr << "xme::Vector::operator*= 2 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{7, 14, 21, 28, 35};
        v /= 7.f;
        bool error = v[0] != 1 || v[1] != 2 || v[2] != 3 || v[3] != 4 || v[4] != 5;
        if(error) {
            std::cerr << "xme::Vector::operator/= 1 error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v{8, 14, 3, 10, 5};
        v /= math::Vector<float, 5>{2, 4, 3, 2, 5};
        bool error = v[0] != 4 || v[1] != 3.5 || v[2] != 1 || v[3] != 5 || v[4] != 1;
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
        math::Vector<float, 5> v1{5.f};
        math::Vector<float, 5> v2{7.f};
        bool error = v1 == v2;
        if(error) {
            std::cerr << "xme::Vector::operator== Error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v1{2, 2, 2, 2, 2};
        math::Vector<float, 5> v2{2, 2, 2, 2, 2};
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
        auto l     = math::Vector<double, 5>(4, 4, 5, 3, 1).length();
        bool error = l != std::sqrt(67);
        if(error) {
            std::cerr << "xme::Vector::length error\n";
            ++errors;
        }
    }
    {
        auto d =
          math::dot(math::Vector<float, 5>{3, 3, 1, 1, 2}, math::Vector<float, 5>{2, 8, 1, 2, 1});

        bool error = d != 35;
        if(error) {
            std::cerr << "xme::Vector::dot error\n";
            ++errors;
        }
    }
    {
        auto d1 = math::distance(math::Vector<float, 5>{}, math::Vector<float, 5>{4, 3, 0, 1, 2});
        auto d2 = math::distance(math::Vector<float, 5>{4, 3, 0, 1, 2}, math::Vector<float, 5>{});
        bool error = d1 != std::sqrt(30.f) || d2 != std::sqrt(30.f);
        if(error) {
            std::cerr << "xme::Vector::distance error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 5> v1{1.f, 1.f, 1.f, 1.f, 1.f};
        auto r1 = math::reflect(v1, math::Vector<float, 5>{0, 1, 0, 0, 0});
        auto r2 = math::reflect(v1, math::Vector<float, 5>{1, 0, 0, 0, 0});
        auto r3 = math::reflect(v1, math::Vector<float, 5>{0, 0, 1, 0, 0});

        bool error = r1 != math::Vector<float, 5>{1, -1, 1, 1, 1}
                     || r2 != math::Vector<float, 5>{-1, 1, 1, 1, 1};
        error |= r3 != math::Vector<float, 5>{1, 1, -1, 1, 1};
        if(error) {
            std::cerr << "xme::Vector::reflect error\n";
            ++errors;
        }
    }

    return errors;
}

int test_normal() {
    int errors = 0;
    {
        auto r1    = math::lerp(math::vec3{3}, math::vec3{2}, 0.5L);
        auto r2    = math::lerp(math::vec3{5}, math::vec3{1}, math::Vector<bool, 3>{1, 0, 1});
        bool error = r2 != math::vec3{1, 5, 1};
        error |= r1 != math::vec3{2.5};
        if(error) {
            std::cerr << "xme::math::lerp error\n";
            ++errors;
        }
    }
    {
        auto r     = math::sign(math::vec4{1, 0, -1, INFINITY});
        bool error = r != math::vec4{1, 0, -1, 1};
        if(error) {
            std::cerr << "xme::math::sign error\n";
            ++errors;
        }
        return errors;
    }
}

int main() {
    int errors = 0;
    test_deduction_guide();
    errors += test_access();
    errors += test_arithmetic();
    errors += test_self();
    errors += test_equality();
    errors += test_operations();
    errors += test_normal();
    return errors;
}
