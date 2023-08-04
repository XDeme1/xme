#include <xme/math/math.hpp>
#include <algorithm>
#include <iostream>

bool isError(bool b) { return b == false; }

int testMatrix2() {
    int errors = 0;
    xme::mat2 m{1, 3, 7, 4};
    auto r = m * m;
    auto results = std::to_array({
        r[0][0] == 22,
        r[0][1] == 15,
        r[1][0] == 35,
        r[1][1] == 37,
    });
    
    auto error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "Matrix2x2 Multiplication Error";
        ++errors;
    }
    return errors;    
}

int testMatrix3() {
    int errors = 0;
    xme::mat3 m{1, 3, 6, 7, 4, 2, -5, 2, 8};
    auto r = m * m;
    auto results = std::to_array({
        r[0][0] == -8,
        r[0][1] == 27, 
        r[0][2] == 60, 
        r[1][0] == 25,
        r[1][1] == 41,
        r[1][2] == 66,
        r[2][0] == -31,
        r[2][1] == 9,
        r[2][2] == 38,
    });
    
    auto error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "Matrix3x3 Multiplication Error";
        ++errors;
    }
    return errors;    
}

int testMatrixVector() {
    int errors = 0;
    {
        xme::mat2 m{};
        xme::vec2 v{5, 6};
        auto r = m * v;
        std::cout << r[0] << ' ' << r[1];
    }
    {
        xme::mat3 m{2};
        xme::vec3 v{5, 6, 7};
        auto r = m * v;
        std::cout << r[0] << ' ' << r[1] << ' ' << r[2];
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testMatrix2();
    errors += testMatrix3();
    errors += testMatrixVector();
    return errors;
}