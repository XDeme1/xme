#pragma once
#include "constants.hpp"
#include "forward.hpp"
#include <cmath>
#include <type_traits>

// For more information see: https://en.wikipedia.org/wiki/Inverse_trigonometric_functions
namespace xme {
template<std::floating_point T>
constexpr auto radians(T deg) noexcept -> T {
    return deg * (static_cast<T>(xme::pi) / 180);
}

template<std::floating_point T>
constexpr auto degrees(T rad) noexcept -> T {
    return rad * (180 / static_cast<T>(xme::pi));
}

template<std::floating_point T, std::size_t Size>
constexpr auto radians(const xme::Vector<T, Size>& deg) noexcept -> xme::Vector<T, Size> {
    xme::Vector<T, Size> result;
    for (std::size_t i = 0; i < Size; ++i)
        result[i] = deg[i] * (static_cast<T>(xme::pi) / 180);
    return result;
}

template<std::floating_point T, std::size_t Size>
constexpr auto degrees(const xme::Vector<T, Size>& rad) noexcept -> xme::Vector<T, Size> {
    xme::Vector<T, Size> result;
    for (std::size_t i = 0; i < Size; ++i)
        result[i] = rad[i] * (180 / static_cast<T>(xme::pi));
    return result;
}

using std::cos;
using std::sin;
using std::tan;

template<typename T>
constexpr auto sec(T s) noexcept -> std::conditional_t<std::integral<T>, double, T> {
    return 1 / xme::cos(s);
}
template<typename T>
constexpr auto csc(T s) noexcept -> std::conditional_t<std::integral<T>, double, T> {
    return 1 / xme::sin(s);
}
template<typename T>
constexpr auto cot(T s) noexcept -> std::conditional_t<std::integral<T>, double, T> {
    return 1 / xme::tan(s);
}

template<typename T>
constexpr auto arcsin(T s) noexcept -> std::conditional_t<std::integral<T>, double, T> {
    return std::asin(s);
}
template<typename T>
constexpr auto arccos(T s) noexcept -> std::conditional_t<std::integral<T>, double, T> {
    return std::acos(s);
}
template<typename T>
constexpr auto arctan(T s) noexcept -> std::conditional_t<std::integral<T>, double, T> {
    return std::atan(s);
}

template<typename T>
constexpr auto arcsec(T s) noexcept -> std::conditional_t<std::integral<T>, double, T> {
    return xme::arccos(1 / s);
}
template<typename T>
constexpr auto arccsc(T s) noexcept -> std::conditional_t<std::integral<T>, double, T> {
    return xme::arcsin(1 / s);
}
template<typename T>
constexpr auto arccot(T s) noexcept -> std::conditional_t<std::integral<T>, double, T> {
    using return_t = std::conditional_t<std::integral<T>, double, T>;
    return static_cast<return_t>(xme::pi) / 2 - arctan(s);
}

template<typename T, std::size_t Size>
constexpr auto sin(const Vector<T, Size>& v) noexcept
    -> Vector<decltype(sin(v[0])), Size> {
    Vector<decltype(sin(v[0])), Size> result;
    for (std::size_t i = 0; i < Size; ++i)
        result[i] = xme::sin(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto cos(const Vector<T, Size>& v) noexcept {
    Vector<decltype(cos(v[0])), Size> result;
    for (std::size_t i = 0; i < Size; ++i)
        result[i] = xme::cos(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto tan(const Vector<T, Size>& v) noexcept
    -> Vector<decltype(tan(v[0])), Size> {
    Vector<decltype(tan(v[0])), Size> result;
    for (std::size_t i = 0; i < Size; ++i)
        result[i] = xme::tan(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto sec(const Vector<T, Size>& v) noexcept
    -> Vector<decltype(sec(v[0])), Size> {
    Vector<decltype(sec(v[0])), Size> result;
    for (std::size_t i = 0; i < Size; ++i)
        result[i] = xme::sec(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto csc(const Vector<T, Size>& v) noexcept {
    Vector<decltype(csc(v[0])), Size> result;
    for (std::size_t i = 0; i < Size; ++i)
        result[i] = xme::csc(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto cot(const Vector<T, Size>& v) noexcept
    -> Vector<decltype(cot(v[0])), Size> {
    Vector<decltype(cot(v[0])), Size> result;
    for (std::size_t i = 0; i < Size; ++i)
        result[i] = xme::cot(v[i]);
    return result;
}
} // namespace xme