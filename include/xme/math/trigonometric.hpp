#pragma once
#include <cmath>
#include "constants.hpp"

// For more information see: https://en.wikipedia.org/wiki/Inverse_trigonometric_functions
namespace xme {
constexpr auto radians(auto degree) noexcept { return degree * (xme::pi / 180); }
constexpr auto degrees(auto radian) noexcept { return radian * (180 / xme::pi); }

constexpr auto sin(auto s) noexcept { return std::sin(s); }
constexpr auto cos(auto s) noexcept { return std::cos(s); }
constexpr auto tan(auto s) noexcept { return std::tan(s); }

constexpr auto sec(auto s) noexcept { return 1 / xme::cos(s); }
constexpr auto csc(auto s) noexcept { return 1 / xme::sin(s); }
constexpr auto cot(auto s) noexcept { return 1 / xme::tan(s); }

constexpr auto arcsin(auto s) noexcept { return std::asin(s); }
constexpr auto arccos(auto s) noexcept { return std::acos(s); }
constexpr auto arctan(auto s) noexcept { return std::atan(s); }

constexpr auto arcsec(auto s) noexcept { return xme::arccos(1 / s); }
constexpr auto arccsc(auto s) noexcept { return xme::arcsin(1 / s); }
constexpr auto arccot(auto s) noexcept { return xme::pi / 2 - arctan(s); }
} // namespace xme