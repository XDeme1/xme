#include "common.hpp"

int testAccess() {
    int errros = 0;
    xme::vec4 v1{1, 6, 3, 0};
    xme::Vector<float, 6> v2{9, -5, 2, 7, 3, 1};
    std::array results{
        v1[0] == 1,
        v1[1] == 6,
        v1[2] == 3,
        v1[3] == 0,
        v2[0] == 9,
        v2[1] == -5,
        v2[2] == 2,
        v2[3] == 7,
        v2[4] == 3,
        v2[5] == 1,
    };

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        std::cerr << "Vector<T, Size>::operator[] operator error\n";
        ++errros;
    }
    return errros;
}

int main() {
    int errors = 0;
    errors += testAccess();
    return errors;
}