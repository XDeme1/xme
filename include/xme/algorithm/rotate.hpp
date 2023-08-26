#pragma once
#include <concepts>
#include <cstdint>
#include <limits>

namespace xme {

template<std::integral T>
constexpr T rotr(T n, std::uint32_t c) {
    using u = std::make_unsigned_t<T>;
    constexpr u mask = std::numeric_limits<u>::digits - 1;
    c &= mask;

    return (n >> c) | (n << ((-c) & mask));
}

template<std::integral T>
constexpr T rotl(T n, std::uint32_t c) {
    using u = std::make_unsigned_t<T>;
    constexpr u mask = std::numeric_limits<u>::digits - 1;
    c &= mask;

    return (n << c) | (n >> ((-c) & mask));
}
} // namespace xme