#pragma once
#include <type_traits>

namespace xme {
    template<typename T>
    constexpr bool has_single_bit(T v) noexcept {
        static_assert(std::is_unsigned_v<T>, "T must be an unsigned integer type");
        return v && !(v & (v - 1));
    }
}