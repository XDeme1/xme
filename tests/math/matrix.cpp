#include <xme/math/matrix.hpp>
#include <xme/math/glsl_mapping.hpp>
#include <iostream> 

namespace math = xme::math;

int test_basic_functions() {
    int errors = 0;
    {
        math::mat2 m{math::vec2{3, 4}, math::vec2{1, 2}};
        bool error = m.determinant() != 2;

        if(error) {
            std::cerr << "xme::Matrix::determinant 2 error\n";
            ++errors;
        }
    }
    {
        math::mat3 m{math::vec3{5, 3, 1}, math::vec3{7, 3, 4}, math::vec3{9, 7, 8}};
        bool error = m.determinant() != -58;
        if(error) {
            std::cerr << "xme::Matrix::determinant 3 error\n";
            ++errors;
        }
    }
    {
        math::mat4 m{math::vec4{5, 3, 1, 2}, math::vec4{6, 7, 3, 4}, math::vec4{9, 7, -3, 8}, math::vec4{9, -8, -3, 1}};
        bool error = m.determinant() != -498;
        std::cout << m.determinant();
        if(error) {
            std::cerr << "xme::Matrix::determinant 4 error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_basic_functions();
    return errors;
}
