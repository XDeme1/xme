#include <iostream>
#include <xme/math/type_traits.hpp>

int main() {
    int errors = 0;

    using xme::is_power_of_2;
    bool error = !is_power_of_2<1> || !is_power_of_2<2> || !is_power_of_2<4>;
    error |= is_power_of_2<0> || is_power_of_2<3> || is_power_of_2<12>;

    if (error) {
        std::cerr << "is_power_of_2 error\n";
        ++errors;
    }

    return errors;
}