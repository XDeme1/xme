#pragma once
#include <cstddef>

namespace xme {
template<std::size_t N>
inline constexpr bool is_power_of_2 = !((N - 1) & N) && N != 0;

template<std::size_t N>
inline constexpr bool is_power_of_3 = (is_power_of_3<N / 3> && is_power_of_3<N % 3> == 0);

template<>
inline constexpr bool is_power_of_3<0> = false;
template<>
inline constexpr bool is_power_of_3<1> = true;
} // namespace xme