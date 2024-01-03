#pragma once
#include <cmath>
#include <xme/setup.hpp>
#include <xme/core/concepts/concepts.hpp>
#include <xme/math/constants.hpp>

// For more information see: https://en.wikipedia.org/wiki/Inverse_trigonometric_functions
namespace xme::math {
template<CFloatingPoint T>
[[nodiscard]]
XME_INLINE constexpr auto radians(T deg) noexcept -> T {
    return deg * (math::pi_v<T> / 180);
}

template<CFloatingPoint T>
[[nodiscard]]
XME_INLINE constexpr auto degrees(T rad) noexcept -> T {
    return rad * (180 / math::pi_v<T>);
}

using std::cos;
using std::sin;
using std::tan;

template<typename T>
[[nodiscard]]
XME_INLINE constexpr auto sec(T s) noexcept -> decltype(1 / cos(s)) {
    return 1 / cos(s);
}
template<typename T>
[[nodiscard]]
XME_INLINE constexpr auto csc(T s) noexcept -> decltype(1 / sin(s)) {
    return 1 / sin(s);
}
template<typename T>
[[nodiscard]]
XME_INLINE constexpr auto cot(T s) noexcept -> decltype(1 / tan(s)) {
    return 1 / tan(s);
}

template<typename T>
[[nodiscard]]
XME_INLINE constexpr auto arcsin(T s) noexcept -> decltype(std::asin(s)) {
    return std::asin(s);
}
template<typename T>
[[nodiscard]]
XME_INLINE constexpr auto arccos(T s) noexcept -> decltype(std::acos(s)) {
    return std::acos(s);
}
template<typename T>
[[nodiscard]]
XME_INLINE constexpr auto arctan(T s) noexcept -> decltype(std::atan(s)) {
    return std::atan(s);
}
}  // namespace xme::math