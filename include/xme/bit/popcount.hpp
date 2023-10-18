#pragma once
#include <cstdint>
#include <type_traits>

namespace xme {
//! Intended to use on c++17 and lower. Use std::popcount if possible.
//! Counts the number of bit 1 in value
template<typename T>
constexpr auto popcount(T v) noexcept -> T {
    static_assert(std::is_unsigned_v<T>, "T must be an unsigned integer type");
    if constexpr (sizeof(T) == 1) {
        v = v - ((v >> 1) & 0x55);
        v = (v & 0x33) + ((v >> 2) & 0x33);
        v = (v + (v >> 4)) & 0x0F;
        return v;
    }
    if constexpr (sizeof(T) == 2) {
        v = v - ((v >> 1) & 0x55'55);
        v = (v & 0x33'33) + ((v >> 2) & 0x33'33);
        v = (v + (v >> 4)) & 0x0F'0F;
        v *= 0x01'01;
        return v >> 8;
    }
    if constexpr (sizeof(T) == 4) {
        v = v - ((v >> 1) & 0x55555555);                // add pairs of bits
        v = (v & 0x33333333) + ((v >> 2) & 0x33333333); // quads
        v = (v + (v >> 4)) & 0x0F0F0F0F;                // groups of 8
        v *= 0x01010101;                                // horizontal sum of bytes
        return v >> 24;
    }
    if constexpr (sizeof(T) == 8) {
        v = v - ((v >> 1) & 0x55'55'55'55'55'55'55'55);
        v = (v & 0x33'33'33'33'33'33'33'33) +
            ((v >> 2) & 0x33'33'33'33'33'33'33'33);
        v = (v + (v >> 4)) & 0x0F'0F'0F'0F'0F'0F'0F'0F; 
        v *= 0x01'01'01'01'01'01'01'01;
        return v >> 56;
    }
    if constexpr (sizeof(T) == 16) {
        return xme::popcount(std::uint64_t(v >> 64)) +                  // High part
               xme::popcount(std::uint64_t(v & 0xFFFF'FFFF'FFFF'FFFF)); // Low part
    }
}
} // namespace xme