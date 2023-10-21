#include <iostream>
#include "xme/math/glsl_mapping.hpp"
#include <xme/math/vector.hpp>

namespace math = xme::math;

void test_deduction_guide() {
    math::Vector v1{1, 5, 1.5f};
    math::Vector v2{2.5, 2.f};
    math::Vector v3{2ul};
    math::Vector v4{v2};
    static_assert(std::is_same_v<decltype(v1), math::Vector<float, 3>>);
    static_assert(std::is_same_v<decltype(v2), math::Vector<double, 2>>);
    static_assert(std::is_same_v<decltype(v3), math::Vector<unsigned long, 1>>);
    static_assert(std::is_same_v<decltype(v4), decltype(v2)>);
}

int test_access() {
    int errors = 0;
    {
        math::Vector<float, 3> v{1, 5, 3};
        bool error = v[0] != 1 || v[1] != 5 || v[2] != 3;
        if (error) {
            std::cerr << "xme::Vector::operator[] error\n";
            ++errors;
        }
    }
    {
        math::Vector<float, 3> v{2};
        bool error = get<0>(v) != 2 || get<1>(v) != 2 || get<1>(v) != 2;
        if (error) {
            std::cerr << "xme::Vector get error\n";
            ++errors;
        }
    }
    {
        math::Vector<int, 3> v{1, math::Vector<int, 2>{2, 4}};
        auto b = begin(v);
        bool error = *(b++) != 1 || *(b++) != 2 || *(b++) != 4;
        error |= b != end(v);
        if (error) {
            std::cerr << "xme::Vector begin/end error\n";
            ++errors;
        }
    }
    return errors;
}

int test_unary() {
    int errors = 0;
    {
        auto v = -math::Vector<float, 2>{1.5, 2.5};
        bool error = v[0] != -1.5 || v[1] != -2.5;
        if (error) {
            std::cerr << "xme::Vector unary - error\n";
            ++errors;
        }
    }
    return errors;
}

int test_arithmetic() {
    int errors = 0;
    {
        const math::Vector<float, 2> v1{1, 5};
        math::Vector<float, 2> v2{v1 + 2};
        bool error = v2[0] != 3 || v2[1] != 7;
        if (error) {
            std::cerr << "xme::Vector::operator+ 1 error\n";
            ++errors;
        }
    }
    {
        const math::Vector<float, 2> v1{1, 5};
        math::Vector<float, 2> v2{v1 + v1};
        bool error = v2[0] != 2 || v2[1] != 10;
        if (error) {
            std::cerr << "xme::Vector::operator+ 2 error\n";
            ++errors;
        }
    }
    {
        const math::Vector<float, 2> v1{3, 1};
        math::Vector<float, 2> v2{v1 - 2};
        bool error = v2[0] != 1 || v2[1] != -1;
        if (error) {
            std::cerr << "xme::Vector::operator- 1 error\n";
            ++errors;
        }
    }
    {
        const math::Vector<float, 2> v1{6, 6};
        math::Vector<float, 2> v2{v1 - math::Vector<float, 2>{5, 1}};
        bool error = v2[0] != 1 || v2[1] != 5;
        if (error) {
            std::cerr << "xme::Vector::operator- 2 error\n";
            ++errors;
        }
    }
    {
        const math::Vector<float, 2> v1{3, 2};
        math::Vector<float, 2> v2{v1 * 3};
        bool error = v2[0] != 9 || v2[1] != 6;
        if (error) {
            std::cerr << "xme::Vector::operator* 1 error\n";
            ++errors;
        }
    }
    {
        const math::Vector<float, 2> v1{1, 5};
        math::Vector<float, 2> v2{v1 * math::Vector<float, 2>{5, 3}};
        bool error = v2[0] != 5 || v2[1] != 15;
        if (error) {
            std::cerr << "xme::Vector::operator* 2 error\n";
            ++errors;
        }
    }
    {
        const math::Vector<float, 2> v1{20, 15};
        math::Vector<float, 2> v2{v1 / 5};
        bool error = v2[0] != 4 || v2[1] != 3;
        if (error) {
            std::cerr << "xme::Vector::operator/ 1 error\n";
            ++errors;
        }
    }
    {
        const math::Vector<float, 2> v1{18, 16};
        math::Vector<float, 2> v2{v1 / math::Vector<float, 2>{2, 4}};
        bool error = v2[0] != 9 || v2[1] != 4;
        if (error) {
            std::cerr << "xme::Vector::operator/ 2 error\n";
            ++errors;
        }
    }
    return errors;
}

int test_self() {
    int errors = 0;
    {
        math::vec4 v{2, 5, 1, 2};
        v = math::vec4{math::vec2{3, 1}, math::vec2{6, 3}};
        bool error = v[0] != 3 || v[1] != 1 || v[2] != 6 || v[3] != 3;
        if (error) {
            std::cerr << "xme::Vector assignment error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{2, math::vec3{2, 5, 3}};
        v += 4;
        bool error = v[0] != 6 || v[1] != 6 || v[2] != 9 || v[3] != 7;
        if (error) {
            std::cerr << "xme::Vector::operator+= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{math::vec2{2, 2}, 5, 3};
        v += math::vec4{1, 2, 2, 1};
        bool error = v[0] != 3 || v[1] != 4 || v[2] != 7 || v[3] != 4;
        if (error) {
            std::cerr << "xme::Vector::operator+= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{2, 2, math::vec2{5, 3}};
        v -= 2;
        bool error = v[0] != 0 || v[1] != 0 || v[2] != 3 || v[3] != 1;
        if (error) {
            std::cerr << "xme::Vector::operator-= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec4 v{math::vec3{2, 5, 3}, 2};
        v -= math::vec4{2, 3, 7, 1};
        bool error = v[0] != 0 || v[1] != 2 || v[2] != -4 || v[3] != 1;
        if (error) {
            std::cerr << "xme::Vector::operator-= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{2, -2};
        v *= 3;
        bool error = v[0] != 6 || v[1] != -6;
        if (error) {
            std::cerr << "xme::Vector::operator*= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{1, 5};
        v *= math::vec2{-2, 3};
        bool error = v[0] != -2 || v[1] != 15;
        if (error) {
            std::cerr << "xme::Vector::operator*= 2 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{7, 14};
        v /= 7;
        bool error = v[0] != 1 || v[1] != 2;
        if (error) {
            std::cerr << "xme::Vector::operator/= 1 error\n";
            ++errors;
        }
    }
    {
        math::vec2 v{8, 14};
        v /= math::vec2{2, 4};
        bool error = v[0] != 4 || v[1] != 3.5;
        if (error) {
            std::cerr << "xme::Vector::operator/= 2 error\n";
            ++errors;
        }
    }
    return errors;
}

int test_equality() {
    int errors = 0;
    {
        math::Vector<float, 5> v1{5};
        math::Vector<float, 5> v2{7};
        bool error = v1 == v2;
        if(error) {
            std::cerr << "xme::Vector::operator== Error\n";
            ++errors;
        }
    }
    {
        math::vec4 v1{2, 2, 2, 2};
        math::vec4 v2{2, 2, 2, 2};
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
        auto l1 = math::vec3(3, 0, 0).lenght();
        auto l2 = math::vec4(5, 1, 3, 1).lenght();
        bool error = l1 != 3 || l2 != 6;
        if(error) {
            std::cerr << "xme::Vector::lenght error\n";
            ++errors;
        }
    }
    {
        auto d1 = math::vec3{5, 0, 0}.dot(math::vec3{0, 5, 0});
        auto d2 = math::vec3{3, 3, 1}.dot(math::vec3{2, 8, 1});

        bool error = d1 != 0 || d2 != 31;
        if(error) {
            std::cerr << "xme::Vector::dot error\n";
            ++errors;
        }
    }
    {
        auto c1 = math::vec3{1, 0, 0}.cross(math::vec3{0, 5, 0}); 
        auto c2 = math::vec3{-3, 7, 0}.cross(math::vec3{2, 5, 0});
        bool error = c1 != math::vec3{0, 0, 5} || c2 != math::vec3{0, 0, -29};
        if(error) {
            std::cerr << "xme::Vector::cross error\n";
            ++errors;
        }
    }
    {
        auto d1 = math::vec3{}.distance(math::vec3{4, 3, 0}); 
        auto d2 = math::vec3{4, 3, 0}.distance(math::vec3{});
        bool error = d1 != 5 || d2 != 5;
        if(error) {
            std::cerr << "xme::Vector::distance error\n";
            ++errors;
        }
    }
    {
        math::vec3 v1{1, 1, 1};
        auto r1 = v1.reflect(math::vec3{0, 1, 0});
        auto r2 = v1.reflect(math::vec3{1, 0, 0});
        auto r3 = v1.reflect(math::vec3{0, 0, 1});
        
        bool error = r1 != math::vec3{1, -1, 1} || r2 != math::vec3{-1, 1, 1};
        error |= r3 != math::vec3{1, 1, -1};
        if(error) {
            std::cerr << "xme::Vector::reflect error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    test_deduction_guide();
    errors += test_access();
    errors += test_arithmetic();
    errors += test_self();
    errors += test_equality();
    errors += test_operations();
    return errors;
}