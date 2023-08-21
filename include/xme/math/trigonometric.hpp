#pragma once
#include "constants.hpp"
#include <cmath>

// For more information see: https://en.wikipedia.org/wiki/Inverse_trigonometric_functions
namespace xme {

template<std::floating_point T>
constexpr auto radians(T degree) noexcept -> T {
    return degree * (static_cast<T>(xme::pi) / 180);
}

template<std::floating_point T>
constexpr auto degrees(T radian) noexcept -> T {
    return radian * (180 / static_cast<T>(xme::pi));
}

template<std::floating_point T>
constexpr auto sin(T s) noexcept -> T {
    return std::sin(s);
}
template<std::floating_point T>
constexpr auto cos(T s) noexcept -> T {
    return std::cos(s);
}
template<std::floating_point T>
constexpr auto tan(T s) noexcept -> T {
    return std::tan(s);
}

template<std::floating_point T>
constexpr auto sec(T s) noexcept -> T {
    return 1 / xme::cos(s);
}
template<std::floating_point T>
constexpr auto csc(T s) noexcept -> T {
    return 1 / xme::sin(s);
}
template<std::floating_point T>
constexpr auto cot(T s) noexcept -> T {
    return 1 / xme::tan(s);
}

template<std::floating_point T>
constexpr auto arcsin(T s) noexcept -> T {
    return std::asin(s);
}
template<std::floating_point T>
constexpr auto arccos(T s) noexcept -> T {
    return std::acos(s);
}
template<std::floating_point T>
constexpr auto arctan(T s) noexcept -> T {
    return std::atan(s);
}

template<std::floating_point T>
constexpr auto arcsec(T s) noexcept -> T {
    return xme::arccos(1 / s);
}
template<std::floating_point T>
constexpr auto arccsc(T s) noexcept -> T {
    return xme::arcsin(1 / s);
}
template<std::floating_point T>
constexpr auto arccot(T s) noexcept -> T {
    return static_cast<T>(xme::pi) / 2 - arctan(s);
}
} // namespace xme