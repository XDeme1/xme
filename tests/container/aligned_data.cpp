#include <xme/container/aligned_data.hpp>
#include <type_traits>

int main() {
    int errors = 0;
    xme::AlignedData<double> f1;
    const xme::AlignedData<double> f2;
    
    static_assert(std::is_same_v<decltype(f1.data()), double*>);
    static_assert(std::is_same_v<decltype(f2.data()), const double*>);

    if(f1.data() != f1.address())
        ++errors;
    if(f2.data() != f2.address())
        ++errors;

    return errors;
}