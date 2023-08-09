#include "common.hpp"

int testPlus() {
    int errors = 0;

    xme::vec4 v{1, 5, 3, 4};
    xme::Vector r1 = v + 3;
    xme::Vector r2 = v + xme::vec4{7, 3, 1, -2};

    std::array results{
        r1 == xme::vec4{4, 8, 6, 7},
        r2 == xme::vec4{8, 8, 4, 2},
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
    xme::Vector r2 = v - xme::vec4{1, -7, 2, 3};

    std::array results{
        r1 == xme::vec4{5, 1, -10, 0},
        r2 == xme::vec4{6, 10, -10, -1},
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
    xme::Vector r2 = v * xme::vec4{1, -2, 2, 3};

    std::array results{
        r1 == xme::vec4{21, 9, -24, 6},
        r2 == xme::vec4{7, -6, -16, 6},
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
    xme::Vector r2 = v / xme::vec4{4, 2, -2, 1};

    std::array results{
        r1 == xme::vec4{4, 3, -4, 1},
        r2 == xme::vec4{2, 3, 4, 2},
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