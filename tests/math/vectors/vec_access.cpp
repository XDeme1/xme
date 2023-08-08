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

int testRanges() {
    int errors = 0;
    xme::vec4 v{5, 2, 3, 1};
    static_assert(std::is_same_v<decltype(v.begin()), float*>);
    std::array results{
        *v.begin() == 5,
        *v.begin()+1 == 2,
        *v.begin()+2 == 3,
        *v.begin()+3 == 1,
        v.begin()+4 == v.end(),            
    };
    
    bool error = std::ranges::all_of(results, isError);
    if(error) {
        std::cerr << "Vector::begin() && Vector::end() error\n";
        ++errors;
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testAccess();
    errors += testRanges();
    return errors;
}