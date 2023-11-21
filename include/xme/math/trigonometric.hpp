#pragma once
#include <cmath>
#include <xme/setup.hpp>
#include "constants.hpp"

#if __cpp_concepts
#include "concepts.hpp"
#endif

// For more information see: https://en.wikipedia.org/wiki/Inverse_trigonometric_functions
namespace xme::math {
template<XME_CONCEPT(CArithmetic, T), std::size_t>
struct Vector;

template<XME_CONCEPT(std::floating_point, T)>
constexpr auto radians(T deg) noexcept -> T {
    static_assert(std::is_floating_point<T>::value, "T must be a floating point");
    return deg * (math::pi_v<T> / 180);
}

template<XME_CONCEPT(std::floating_point, T)>
constexpr auto degrees(T rad) noexcept -> T {
    static_assert(std::is_floating_point<T>::value, "T must be a floating point");
    return rad * (180 / math::pi_v<T>);
}

template<XME_CONCEPT(std::floating_point, T), std::size_t Size>
constexpr auto radians(const Vector<T, Size>& deg) noexcept -> Vector<T, Size> {
    static_assert(std::is_floating_point<T>::value, "T must be a floating point");
    Vector<T, Size> result;
    for(std::size_t i = 0; i < Size; ++i)
        result[i] = radians(deg[i]);
    return result;
}

template<XME_CONCEPT(std::floating_point, T), std::size_t Size>
constexpr auto degrees(const Vector<T, Size>& rad) noexcept -> Vector<T, Size> {
    static_assert(std::is_floating_point<T>::value, "T must be a floating point");
    Vector<T, Size> result;
    for(std::size_t i = 0; i < Size; ++i)
        result[i] = degrees(rad[i]);
    return result;
}

using std::cos;
using std::sin;
using std::tan;

template<typename T>
constexpr auto sec(T s) noexcept -> decltype(1 / cos(s)) {
    return 1 / cos(s);
}
template<typename T>
constexpr auto csc(T s) noexcept -> decltype(1 / sin(s)) {
    return 1 / sin(s);
}
template<typename T>
constexpr auto cot(T s) noexcept -> decltype(1 / tan(s)) {
    return 1 / tan(s);
}

template<typename T>
constexpr auto arcsin(T s) noexcept -> decltype(std::asin(s)) {
    return std::asin(s);
}
template<typename T>
constexpr auto arccos(T s) noexcept -> decltype(std::acos(s)) {
    return std::acos(s);
}
template<typename T>
constexpr auto arctan(T s) noexcept -> decltype(std::atan(s)) {
    return std::atan(s);
}

template<typename T>
constexpr auto arcsec(T s) noexcept -> decltype(arccos(s)) {
    using return_t = decltype(arccos(s));
    return arccos(static_cast<return_t>(1) / s);
}
template<typename T>
constexpr auto arccsc(T s) noexcept -> decltype(arcsin(s)) {
    using return_t = decltype(arcsin(s));
    return arcsin(static_cast<return_t>(1) / s);
}
template<typename T>
constexpr auto arccot(T s) noexcept -> decltype(arctan(s)) {
    using return_t = decltype(arctan(s));
    return static_cast<return_t>(xme::math::pi) / 2 - arctan(s);
}

template<typename T, std::size_t Size>
constexpr auto sin(const Vector<T, Size>& v) noexcept -> Vector<decltype(sin(v[0])), Size> {
    Vector<decltype(sin(v[0])), Size> result;
    for(std::size_t i = 0; i < Size; ++i)
        result[i] = sin(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto cos(const Vector<T, Size>& v) noexcept {
    Vector<decltype(cos(v[0])), Size> result;
    for(std::size_t i = 0; i < Size; ++i)
        result[i] = cos(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto tan(const Vector<T, Size>& v) noexcept -> Vector<decltype(tan(v[0])), Size> {
    Vector<decltype(tan(v[0])), Size> result;
    for(std::size_t i = 0; i < Size; ++i)
        result[i] = tan(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto sec(const Vector<T, Size>& v) noexcept -> Vector<decltype(sec(v[0])), Size> {
    Vector<decltype(sec(v[0])), Size> result;
    for(std::size_t i = 0; i < Size; ++i)
        result[i] = sec(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto csc(const Vector<T, Size>& v) noexcept {
    Vector<decltype(csc(v[0])), Size> result;
    for(std::size_t i = 0; i < Size; ++i)
        result[i] = csc(v[i]);
    return result;
}

template<typename T, std::size_t Size>
constexpr auto cot(const Vector<T, Size>& v) noexcept -> Vector<decltype(cot(v[0])), Size> {
    Vector<decltype(cot(v[0])), Size> result;
    for(std::size_t i = 0; i < Size; ++i)
        result[i] = cot(v[i]);
    return result;
}
}  // namespace xme::math
