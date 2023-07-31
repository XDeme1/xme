#pragma once
#include "../../../private/math/forward.hpp"
#include <cmath>

namespace xme {
template <typename T, typename U, std::size_t Size>
constexpr auto dot(const Vector<T, Size>& v1, const Vector<U, Size>& v2) noexcept {
    decltype(v1[0] + v2[0]) result = 0;
    for (std::size_t i = 0; i < Size; ++i)
        result += (v1[i] * v2[i]);
    return result;
}

template <typename T, std::size_t Size>
constexpr auto lenght(const Vector<T, Size>& v) noexcept {
    return std::sqrt(dot(v, v));
}

template <typename T, typename U>
constexpr auto cross(const Vector<T, 3>& v1, const Vector<U, 3>& v2) noexcept {
    // clang-format off
    return xme::Vector{
        v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0]
    };
    // clang-format on
}

template <typename T, std::size_t Size>
constexpr auto normalize(const Vector<T, Size>& v) noexcept {
    return v * (1 / lenght(v));
}

template <typename T, typename U, std::size_t Size>
constexpr auto reflect(const Vector<T, Size>& v, const Vector<U, Size>& n) noexcept {
    return v - 2 * dot(n, v) * n;
}
} // namespace xme
