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

template<typename T, std::size_t Size>
constexpr auto length(const Vector<T, Size>& v) noexcept {
    return std::sqrt(dot(v, v));
}

template<typename T, std::size_t Size>
constexpr auto normalize(const Vector<T, Size>& v) noexcept -> Vector<T, Size> {
    return v * (1 / length(v));
}

template<typename T, std::size_t Size>
constexpr auto reflect(const Vector<T, Size>& v, const Vector<T, Size>& n) noexcept
    -> Vector<T, Size> {
    return v - n * dot(v, n) * 2;
}

template<typename T, std::size_t Size>
constexpr auto distance(const Vector<T, Size>& v1, const Vector<T, Size>& v2) noexcept {
    return (v2 - v1).length();
}
}  // namespace xme::math
