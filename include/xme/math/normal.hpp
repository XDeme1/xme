#pragma once
#include "concepts.hpp"
#include <xme/setup.hpp>
#include <limits>

namespace xme::math {
template<CArithmetic, std::size_t>
struct Vector;

//! Linearly interpolates `v1` and `v2`.
//! Uniform operation.
template<std::floating_point T, CArithmetic U, std::size_t N>
XME_INLINE constexpr auto lerp(const Vector<T, N>& v1, const Vector<T, N>& v2, U percent) {
    if constexpr(std::is_same_v<std::remove_cv_t<U>, bool>) {
        return percent ? v2 : v1;
    }
    return v2 * percent + v1 * (1 - percent);
}

//! Linearly interpolates `v1` and `v2`.
//! Non-Uniform operation
template<std::floating_point T, CArithmetic U, std::size_t N>
XME_INLINE constexpr auto
lerp(const Vector<T, N>& v1, const Vector<T, N>& v2, const Vector<U, N>& percent) {
    Vector<T, N> result;
    for(std::size_t i = 0; i < N; ++i) {
        if constexpr(std::is_same_v<std::remove_cv_t<U>, bool>) {
            result[i] = percent[i] ? v2[i] : v1[i];
        }
        else {
            result[i] = v2[i] * percent[i] + v1[i] * (1 - percent[i]);
        }
    }
    return result;
}

//! Returns the sign of the number.
//! returns -1 if negative, 0 if 0, 1 if positive
template<typename T>
    requires(std::signed_integral<T>) || (std::numeric_limits<T>::is_iec559)
XME_INLINE constexpr auto sign(T n) noexcept -> T {
    return (T(0) < n) - (n < T(0));
}

//! Returns the sign of every component in the vector.
//! returns -1 if negative, 0 if 0, 1 if positive
template<typename T, std::size_t N>
    requires(std::signed_integral<T>) || (std::numeric_limits<T>::is_iec559)
XME_INLINE constexpr auto sign(const Vector<T, N>& v) noexcept -> Vector<T, N> {
    Vector<T, N> result;
    for(std::size_t i = 0; i < N; ++i)
        result[i] = sign(v[i]);
    return result;
}
}  // namespace xme::math
