#include "common.hpp"

namespace math = xme::math;

int testPlus() {
    int errors = 0;
    math::Matrix<float, 4> m;
    m += 3;
    std::vector<short> errorList;
    errorList.emplace_back(m[0] == math::vec4{4, 3, 3, 3});
    errorList.emplace_back(m[1] == math::vec4{3, 4, 3, 3});
    errorList.emplace_back(m[2] == math::vec4{3, 3, 4, 3});
    errorList.emplace_back(m[3] == math::vec4{3, 3, 3, 4});

    m += math::Matrix<float, 4>{3};
    errorList.emplace_back(m[0] == math::vec4{7, 3, 3, 3});
    errorList.emplace_back(m[1] == math::vec4{3, 7, 3, 3});
    errorList.emplace_back(m[2] == math::vec4{3, 3, 7, 3});
    errorList.emplace_back(m[3] == math::vec4{3, 3, 3, 7});

    bool error = std::ranges::any_of(errorList, isError);

    if(error) {
        ++errors;
        std::cerr << "mat += operator error\n";
    }
    return errors;
}

int testMinus() {
    int errors = 0;
    math::Matrix<float, 4> m;
    m -= 3;
    std::vector<short> errorList;
    errorList.emplace_back(m[0] == math::vec4{-2, -3, -3, -3});
    errorList.emplace_back(m[1] == math::vec4{-3, -2, -3, -3});
    errorList.emplace_back(m[2] == math::vec4{-3, -3, -2, -3});
    errorList.emplace_back(m[3] == math::vec4{-3, -3, -3, -2});

    m -= math::Matrix<float, 4>{3};
    errorList.emplace_back(m[0] == math::vec4{-5, -3, -3, -3});
    errorList.emplace_back(m[1] == math::vec4{-3, -5, -3, -3});
    errorList.emplace_back(m[2] == math::vec4{-3, -3, -5, -3});
    errorList.emplace_back(m[3] == math::vec4{-3, -3, -3, -5});

    bool error = std::ranges::any_of(errorList, isError);

    if(error) {
        ++errors;
        std::cerr << "mat -= operator error\n";
    }
    return errors;
}


int testMul() {
    int errors = 0;
    math::Matrix<float, 4> m;
    m *= 3;
    std::vector<short> errorList;
    errorList.emplace_back(m[0] == math::vec4{3, 0, 0, 0});
    errorList.emplace_back(m[1] == math::vec4{0, 3, 0, 0});
    errorList.emplace_back(m[2] == math::vec4{0, 0, 3, 0});
    errorList.emplace_back(m[3] == math::vec4{0, 0, 0, 3});

    bool error = std::ranges::any_of(errorList, isError);

    if(error) {
        ++errors;
        std::cerr << "mat *= operator error\n";
    }
    return errors;
}

int testDiv() {
    int errors = 0;
    math::Matrix<float, 4> m;
    m /= 2;
    std::vector<short> errorList;
    errorList.emplace_back(m[0] == math::vec4{0.5, 0, 0, 0});
    errorList.emplace_back(m[1] == math::vec4{0, 0.5, 0, 0});
    errorList.emplace_back(m[2] == math::vec4{0, 0, 0.5, 0});
    errorList.emplace_back(m[3] == math::vec4{0, 0, 0, 0.5});

    bool error = std::ranges::any_of(errorList, isError);

    if(error) {
        ++errors;
        std::cerr << "mat /= operator error\n";
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testPlus();
    errors += testMinus();
    errors += testMul();
    errors += testDiv();
    return errors;
}