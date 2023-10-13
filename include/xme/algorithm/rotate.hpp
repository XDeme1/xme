#pragma once
#include <concepts>
#include <cstdint>
#include <limits>

namespace xme {
template<std::unsigned_integral T>
constexpr auto rotr(T n, std::int32_t c) -> T {
    constexpr auto mask = std::numeric_limits<T>::digits - 1;
    c &= mask;

    return (n >> c) | (n << ((-c) & mask));
}

template<std::unsigned_integral T>
constexpr auto rotl(T n, std::int32_t c) -> T {
    constexpr auto mask = std::numeric_limits<T>::digits - 1;
    c &= mask;

    return (n << c) | (n >> ((-c) & mask));
}
} // namespace xme