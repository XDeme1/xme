#pragma once
#include <concepts>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace xme {
template<std::integral T>
constexpr auto rotr(T n, std::uint32_t c) -> T {
    using u = std::make_unsigned_t<T>;
    constexpr u mask = std::numeric_limits<u>::digits - 1;
    c &= mask;

    return (n >> c) | (n << ((-c) & mask));
}

template<std::integral T>
constexpr auto rotl(T n, std::uint32_t c) -> T {
    using u = std::make_unsigned_t<T>;
    constexpr u mask = std::numeric_limits<u>::digits - 1;
    c &= mask;

    return (n << c) | (n >> ((-c) & mask));
}
} // namespace xme