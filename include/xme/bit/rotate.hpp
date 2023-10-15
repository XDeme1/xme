#pragma once
#include <cstdint>
#include <limits>
#include <type_traits>

namespace xme {
template<typename T>
constexpr auto rotr(T n, std::int32_t c) -> T {
    static_assert(std::is_unsigned_v<T>, "T must be an unsigned integer type");
    constexpr auto mask = std::numeric_limits<T>::digits - 1;
    c &= mask;

    return (n >> c) | (n << ((-c) & mask));
}

template<typename T>
constexpr auto rotl(T n, std::int32_t c) -> T {
    static_assert(std::is_unsigned_v<T>, "T must be an unsigned integer type");
    constexpr auto mask = std::numeric_limits<T>::digits - 1;
    c &= mask;

    return (n << c) | (n >> ((-c) & mask));
}
} // namespace xme