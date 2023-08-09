#include "common.hpp"

int testEquality() {
    int errors = 0;
    {
        xme::Vector<float, 5> v1{5};
        xme::Vector<float, 5> v2{7};
        if(v1 == v2) {
            std::cerr << "Vector<T, Size::operator== Error\n";
            ++errors;
        }

        xme::vec4 v3{2, 2, 2, 2};
        xme::vec4 v4{2, 2, 2, 2};
        if(v3 != v4) {
            std::cerr << "Vector<T, Size::operator!= Error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testEquality();
    return errors;
}