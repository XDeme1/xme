#pragma once
#include <cmath>
#include <xme/setup.hpp>
#include <xme/core/concepts/arithmetic.hpp>

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector;

//! Dot product.
template<typename T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto dot(const Vector<T, Size>& v1, const Vector<T, Size>& v2) noexcept -> T {
    T result = 0;
    for(std::size_t i = 0; i < Size; ++i)
        result += (v1[i] * v2[i]);
    return result;
}

//! Cross product.
// Returns a vector orthogonal to both `v1` and `v2`
template<typename T>
[[nodiscard]]
XME_INLINE constexpr auto cross(const Vector<T, 3>& v1,
                                const Vector<T, 3>& v2) noexcept -> Vector<T, 3> {
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x,
    };
}

//! Return the length of `v`
template<CFloatingPoint T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto length(const Vector<T, Size>& v) noexcept -> T {
    return std::sqrt(dot(v, v));
}

//! Returns the distance from `v1` to `v2`
//! `v1` Start vector
//! `v2` End vector
template<CFloatingPoint T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto distance(const Vector<T, Size>& v1,
                                   const Vector<T, Size>& v2) noexcept -> T {
    return (v2 - v1).length();
}

//! Returns a vector with a length of 1
//! `v` Vector to normalize
template<CFloatingPoint T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto normalize(const Vector<T, Size>& v) noexcept -> Vector<T, Size> {
    return v * (1 / length(v));
}

//! Negates `v` direction based on the angle between `i` and `n`.
//! If the dot product between `i` and `n` is positive, return `-v`, otherwise return `v`.
//! `v` Vector to orient
//! `i` Incident vector
//! `n` Normal vector
template<typename T, std::size_t N>
[[nodiscard]]
XME_INLINE constexpr auto faceforward(const Vector<T, N>& v, const Vector<T, N>& i,
                                      const Vector<T, N>& n) -> Vector<T, N> {
    return dot(n, i) < 0 ? v : -v;
}

template<typename T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto reflect(const Vector<T, Size>& v,
                                  const Vector<T, Size>& n) noexcept -> Vector<T, Size> {
    return v - n * dot(v, n) * static_cast<T>(2);
}
}  // namespace xme::math