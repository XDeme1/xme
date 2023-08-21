#include "common.hpp"

int testPlus() {
    int errors = 0;
    xme::Matrix<float, 4> m;
    m += 3;
    std::vector<short> errorList;
    errorList.emplace_back(m[0] == xme::vec4{4, 3, 3, 3});
    errorList.emplace_back(m[1] == xme::vec4{3, 4, 3, 3});
    errorList.emplace_back(m[2] == xme::vec4{3, 3, 4, 3});
    errorList.emplace_back(m[3] == xme::vec4{3, 3, 3, 4});

    m += xme::Matrix<float, 4>{3};
    errorList.emplace_back(m[0] == xme::vec4{7, 3, 3, 3});
    errorList.emplace_back(m[1] == xme::vec4{3, 7, 3, 3});
    errorList.emplace_back(m[2] == xme::vec4{3, 3, 7, 3});
    errorList.emplace_back(m[3] == xme::vec4{3, 3, 3, 7});

    bool error = std::ranges::any_of(errorList, isError);

    if(error) {
        ++errors;
        std::cerr << "mat += operator error\n";
    }
    return errors;
}

int testMinus() {
    int errors = 0;
    xme::Matrix<float, 4> m;
    m -= 3;
    std::vector<short> errorList;
    errorList.emplace_back(m[0] == xme::vec4{-2, -3, -3, -3});
    errorList.emplace_back(m[1] == xme::vec4{-3, -2, -3, -3});
    errorList.emplace_back(m[2] == xme::vec4{-3, -3, -2, -3});
    errorList.emplace_back(m[3] == xme::vec4{-3, -3, -3, -2});

    m -= xme::Matrix<float, 4>{3};
    errorList.emplace_back(m[0] == xme::vec4{-5, -3, -3, -3});
    errorList.emplace_back(m[1] == xme::vec4{-3, -5, -3, -3});
    errorList.emplace_back(m[2] == xme::vec4{-3, -3, -5, -3});
    errorList.emplace_back(m[3] == xme::vec4{-3, -3, -3, -5});

    bool error = std::ranges::any_of(errorList, isError);

    if(error) {
        ++errors;
        std::cerr << "mat -= operator error\n";
    }
    return errors;
}


int testMul() {
    int errors = 0;
    xme::Matrix<float, 4> m;
    m *= 3;
    std::vector<short> errorList;
    errorList.emplace_back(m[0] == xme::vec4{3, 0, 0, 0});
    errorList.emplace_back(m[1] == xme::vec4{0, 3, 0, 0});
    errorList.emplace_back(m[2] == xme::vec4{0, 0, 3, 0});
    errorList.emplace_back(m[3] == xme::vec4{0, 0, 0, 3});

    bool error = std::ranges::any_of(errorList, isError);

    if(error) {
        ++errors;
        std::cerr << "mat *= operator error\n";
    }
    return errors;
}

int testDiv() {
    int errors = 0;
    xme::Matrix<float, 4> m;
    m /= 2;
    std::vector<short> errorList;
    errorList.emplace_back(m[0] == xme::vec4{0.5, 0, 0, 0});
    errorList.emplace_back(m[1] == xme::vec4{0, 0.5, 0, 0});
    errorList.emplace_back(m[2] == xme::vec4{0, 0, 0.5, 0});
    errorList.emplace_back(m[3] == xme::vec4{0, 0, 0, 0.5});

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