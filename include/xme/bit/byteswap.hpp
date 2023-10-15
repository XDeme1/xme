#pragma once
#include <type_traits>

namespace xme {
//! Swaps the byte ordering of the type.
//! Swaps between little endian and big endian.
template<typename T>
constexpr auto byteswap(T value) noexcept -> T {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    if constexpr (sizeof(T) == 1)
        return value;

    if constexpr (sizeof(T) == 2) {
        return (static_cast<std::make_unsigned_t<T>>(value) >> 8) |
               (static_cast<std::make_unsigned_t<T>>(value) << 8);
    }
    if constexpr (sizeof(T) == 4) {
        return (static_cast<std::make_unsigned_t<T>>(value) >> 24) |
               ((static_cast<std::make_unsigned_t<T>>(value) & 0x00ff'0000) >> 8) |
               ((static_cast<std::make_unsigned_t<T>>(value) & 0x0000'ff00) << 8) |
               (static_cast<std::make_unsigned_t<T>>(value) << 24);
    }
    if constexpr (sizeof(T) == 8) {
        return (static_cast<std::make_unsigned_t<T>>(value) >> 56) |
                ((static_cast<std::make_unsigned_t<T>>(value) & 0x00ff'0000'0000'0000) >> 40) |
                ((static_cast<std::make_unsigned_t<T>>(value) & 0x0000'ff00'0000'0000) >> 24) |
                ((static_cast<std::make_unsigned_t<T>>(value) & 0x0000'00ff'0000'0000) >> 8) |
                ((static_cast<std::make_unsigned_t<T>>(value) & 0x0000'0000'0000'ff00) << 40) |
                ((static_cast<std::make_unsigned_t<T>>(value) & 0x0000'0000'00ff'0000) << 24) |
                ((static_cast<std::make_unsigned_t<T>>(value) & 0x0000'0000'ff00'0000) << 8) |
                (static_cast<std::make_unsigned_t<T>>(value) << 56);
    }
}
} // namespace xme