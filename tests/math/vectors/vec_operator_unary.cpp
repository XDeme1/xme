#include "common.hpp"

template<std::size_t Size>
int testUnary() {
    int errors = 0;
    static_assert(std::is_same_v<decltype(-xme::Vector<float, Size>{}), xme::Vector<float, Size>>);

    {
        xme::Vector<float, Size> v{5};
        xme::Vector r{-v};
    
        bool error = r != xme::Vector<float, Size>{-5};
        if(error) {
            std::cerr << "Vector::operator-() error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testUnary<2>();
    errors += testUnary<3>();
    errors += testUnary<4>();
    errors += testUnary<5>();
    return errors;
}