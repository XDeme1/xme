#pragma once
#include "forward.hpp"

namespace xme {
    template<std::size_t N>
    constexpr bool is_power_of_2 = !((N - 1) & N) && N != 0;
}