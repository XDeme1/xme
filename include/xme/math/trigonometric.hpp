#pragma once
#include <cmath>
#include "constants.hpp"
#include "vector.hpp"

// For more information see: https://en.wikipedia.org/wiki/Inverse_trigonometric_functions
namespace xme {
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

template<typename T, std::size_t Size>
constexpr auto sin(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::sin<T>);
}
template<typename T, std::size_t Size>
constexpr auto cos(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::cos<T>);
}
template<typename T, std::size_t Size>
constexpr auto tan(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::tan<T>);
}

template<typename T, std::size_t Size>
constexpr auto sec(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::sec<T>);
}
template<typename T, std::size_t Size>
constexpr auto csc(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::csc<T>);
}
template<typename T, std::size_t Size>
constexpr auto cot(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::cot<T>);
}

template<typename T, std::size_t Size>
constexpr auto arcsin(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::arcsin<T>);
}
template<typename T, std::size_t Size>
constexpr auto arccos(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::arccos<T>);
}
template<typename T, std::size_t Size>
constexpr auto arctan(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::arctan<T>);
}

template<typename T, std::size_t Size>
constexpr auto arcsec(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::arcsec<T>);
}
template<typename T, std::size_t Size>
constexpr auto arccsc(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::arccsc<T>);
}
template<typename T, std::size_t Size>
constexpr auto arccot(const Vector<T, Size>& v) noexcept {
    return detail::VectorPiecewise1{}(v, xme::arccot<T>);
}
} // namespace xme