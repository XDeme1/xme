#include "common.hpp"

int powerOf2() {
    int errors = 0;

    std::array results = std::to_array({
        xme::is_power_of_2<1>,
        xme::is_power_of_2<2>,
        xme::is_power_of_2<4>,
        xme::is_power_of_2<8>,
        xme::is_power_of_2<16>,

        !xme::is_power_of_2<0>,
        !xme::is_power_of_2<3>,
        !xme::is_power_of_2<6>,
        !xme::is_power_of_2<12>,
    });

    bool error = std::ranges::any_of(results, isError);
    if(error) {
        ++errors;
        std::cerr << "is_power_of_2 error\n";
    }
    return errors;
}

int main() {
    int errors = 0;

    errors += powerOf2();

    return errors;    
}