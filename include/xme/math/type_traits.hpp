#pragma once
#include "forward.hpp"

namespace xme {
    template<std::size_t N>
    constexpr bool is_power_of_2 = !((N - 1) & N) && N != 0;

    template<typename T>
    constexpr bool is_vector_v = false;

    template<typename T, std::size_t Size>
    constexpr bool is_vector_v<Vector<T, Size>> = true;
}