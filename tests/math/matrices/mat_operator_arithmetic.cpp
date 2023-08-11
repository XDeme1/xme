#include "common.hpp"

int testPlus() {
    int errors = 0;

    xme::Matrix<float, 2, 3> m{xme::vec3{5}, xme::vec3{-3}};
    auto r1 = m + 2;
    auto r2 = m + xme::Matrix<float, 2, 3>{2};

    std::array results{
        r1[0] == xme::vec3{7},
        r1[1] == xme::vec3{-1},
        r2[0] == xme::vec3{7, 0, 0},
        r2[1] == xme::vec3{-3, -1, -3},
    };

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "mat + operator error\n";
    }
    return errors;
}

int testMinus() {
    int errors = 0;

    xme::Matrix<float, 2, 3> m{xme::vec3{5}, xme::vec3{-3}};
    auto r1 = m + 2;
    auto r2 = m + xme::Matrix<float, 2, 3>{2};
    
    std::array results{
        r1[0] == xme::vec3{7},
        r1[1] == xme::vec3{-1},
        r2[0] == xme::vec3{7, 0, 0},
        r2[1] == xme::vec3{-3, -1, -3},
    };

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "mat - operator error\n";
    }
    return errors;
}

int testMult() {
    int errors = 0;

    xme::Matrix<float, 2, 3> m{xme::vec3{5}, xme::vec3{-3}};
    auto r = m * 4;
    
    std::array results{
        r[0] == xme::vec3{20},
        r[1] == xme::vec3{-12},
    };

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "mat * operator error\n";
    }
    return errors;
}

int testDiv() {
    int errors = 0;

    xme::Matrix<float, 2, 3> m{xme::vec3{16}, xme::vec3{120}};
    auto r = m / 4;
    
    std::array results{
        r[0] == xme::vec3{4},
        r[1] == xme::vec3{30},
    };

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "mat / operator error\n";
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