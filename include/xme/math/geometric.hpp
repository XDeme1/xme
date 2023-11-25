#pragma once
#include <cmath>
#include <xme/setup.hpp>

#include "concepts.hpp"

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector;

template<typename T, std::size_t Size>
constexpr auto dot(const Vector<T, Size>& v1, const Vector<T, Size>& v2) noexcept -> T {
    T result = 0;
    for(std::size_t i = 0; i < Size; ++i)
        result += (v1[i] * v2[i]);
    return result;
}

template<typename T>
constexpr auto cross(const Vector<T, 3>& v1, const Vector<T, 3>& v2) noexcept -> Vector<T, 3> {
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x,
    };
}

template<std::floating_point T, std::size_t Size>
constexpr auto length(const Vector<T, Size>& v) noexcept -> T {
    return std::sqrt(dot(v, v));
}

template<std::floating_point T, std::size_t Size>
constexpr auto distance(const Vector<T, Size>& v1, const Vector<T, Size>& v2) noexcept -> T {
    return (v2 - v1).length();
}

template<std::floating_point T, std::size_t Size>
constexpr auto normalize(const Vector<T, Size>& v) noexcept -> Vector<T, Size> {
    return v * (1 / length(v));
}

//! Negates `v` direction based on the angle between `i` and `n`.
//! If the dot product between `i` and `n` is positive, return `-v`, otherwise return `v`.
//! `v` Vector to orient
//! `i` Incident vector
//! `n` Normal vector
template<typename T, std::size_t N>
constexpr auto faceforward(const Vector<T, N>& v, const Vector<T, N>& i, const Vector<T, N>& n)
    -> Vector<T, N> {
    return dot(n, i) < 0 ? v : -v;
}

template<typename T, std::size_t Size>
constexpr auto reflect(const Vector<T, Size>& v, const Vector<T, Size>& n) noexcept
    -> Vector<T, Size> {
    return v - n * dot(v, n) * 2;
}
}  // namespace xme::math
