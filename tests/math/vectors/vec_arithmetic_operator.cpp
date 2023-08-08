#include "common.hpp"

int testPlus() {
    int errors = 0;

    xme::vec4 v{1, 5, 3, 4};
    xme::Vector r1 = v + 3;
    xme::Vector r2 = 1 + v;
    xme::Vector r3 = v + xme::vec4{7, 3, 1, -2};

    std::array results{
        r1 == xme::vec4{4, 8, 6, 7},
        r2 == xme::vec4{2, 6, 4, 5},
        r3 == xme::vec4{8, 8, 4, 2},
    };

    bool error = std::ranges::any_of(results, isError);
    if (error) {
        std::cerr << "Vector + error\n";
        ++errors;
    }
    return errors;
}

int testMinus() {
    int errors = 0;
    xme::vec4 v{7, 3, -8, 2};
    xme::Vector r1 = v - 2;
    xme::Vector r2 = 7 - v;
    xme::Vector r3 = v - xme::vec4{1, -7, 2, 3};

    std::array results{
        r1 == xme::vec4{5, 1, -10, 0},
        r2 == xme::vec4{0, 4, 15, 5},
        r3 == xme::vec4{6, 10, -10, -1},
    };

    bool error = std::ranges::any_of(results, isError);
    if (error) {
        std::cerr << "Vector - error\n";
        ++errors;
    }
    return errors;
}

int testMult() {
    int errors = 0;
    xme::vec4 v{7, 3, -8, 2};
    xme::Vector r1 = v * 3;
    xme::Vector r2 = 2 * v;
    xme::Vector r3 = v * xme::vec4{1, -2, 2, 3};

    std::array results{
        r1 == xme::vec4{21, 9, -24, 6},
        r2 == xme::vec4{14, 6, -16, 4},
        r3 == xme::vec4{7, -6, -16, 6},
    };

    bool error = std::ranges::any_of(results, isError);
    if (error) {
        std::cerr << "Vector * error\n";
        ++errors;
    }
    return errors;
}

int testDiv() {
    int errors = 0;
    xme::vec4 v{8, 6, -8, 2};
    xme::Vector r1 = v / 2;
    xme::Vector r2 = 24 / v;
    xme::Vector r3 = v / xme::vec4{4, 2, -2, 1};

    std::array results{
        r1 == xme::vec4{4, 3, -4, 1},
        r2 == xme::vec4{3, 4, -3, 12},
        r3 == xme::vec4{2, 3, 4, 2},
    };

    bool error = std::ranges::any_of(results, isError);
    if (error) {
        std::cerr << "Vector / error\n";
        ++errors;
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testPlus();
    errors += testMinus();
    errors += testMult();
    errors += testDiv();
    return errors;
}