#include "common.hpp"

namespace math = xme::math;

int test_plus() {
    int errors = 0;

    math::Matrix<float, 2, 3> m{math::vec3{5}, math::vec3{-3}};
    auto r1 = m + 2;
    auto r2 = m + math::Matrix<float, 2, 3>{2};

    std::array results{
        r1[0] == math::vec3{7},
        r1[1] == math::vec3{-1},
        r2[0] == math::vec3{7, 5, 5},
        r2[1] == math::vec3{-3, -1, -3},
    };

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        ++errors;
        std::cerr << "mat + operator error\n";
    }
    return errors;
}

int test_minus() {
    int errors = 0;

    math::Matrix<float, 2, 3> m{math::vec3{5}, math::vec3{-3}};
    auto r1 = m - 2;
    auto r2 = m - math::Matrix<float, 2, 3>{2};
    
    std::array results{
        r1[0] == math::vec3{3},
        r1[1] == math::vec3{-5},
        r2[0] == math::vec3{3, 5, 5},
        r2[1] == math::vec3{-3, -5, -3},
    };

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        ++errors;
        std::cerr << "mat - operator error\n";
    }
    return errors;
}

int test_mult() {
    int errors = 0;

    math::Matrix<float, 2, 3> m{math::vec3{5}, math::vec3{-3}};
    auto r = m * 4;
    
    std::array results{
        r[0] == math::vec3{20},
        r[1] == math::vec3{-12},
    };

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        ++errors;
        std::cerr << "mat * operator error\n";
    }
    return errors;
}

int test_div() {
    int errors = 0;

    math::Matrix<float, 2, 3> m{math::vec3{16}, math::vec3{120}};
    auto r = m / 4;
    
    std::array results{
        r[0] == math::vec3{4},
        r[1] == math::vec3{30},
    };

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        ++errors;
        std::cerr << "mat / operator error\n";
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_plus();
    errors += test_minus();
    errors += test_mult();
    errors += test_div();
    return errors;
}