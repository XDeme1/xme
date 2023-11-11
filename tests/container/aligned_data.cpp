#include <xme/container/aligned_data.hpp>
#include <iostream>
#include <type_traits>

int main() {
    int errors = 0;
    xme::AlignedData<double> f1;
    const xme::AlignedData<double> f2;

    static_assert(std::is_same_v<decltype(f1.data()), double*>);
    static_assert(std::is_same_v<decltype(f2.data()), const double*>);

    bool error = f1.data() != f1.address() || f2.data() != f2.address();
    if(error) {
        std::cerr << "xme::AlignedData error\n";
        ++errors;
    }

    return errors;
}
