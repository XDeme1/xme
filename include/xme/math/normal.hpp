#pragma once
#include "concepts.hpp"

namespace xme::math {
template<CArithmetic, std::size_t>
struct Vector;

//! Linearly interpolates `v1` and `v2`.
//! Uniform operation.
template<std::floating_point T, CArithmetic U, std::size_t N>
constexpr auto lerp(const Vector<T, N>& v1, const Vector<T, N>& v2, U percent) {
    if constexpr(std::is_same_v<std::remove_cv_t<U>, bool>) {
        return percent ? v2 : v1;
    }
    return v2 * percent + v1 * (1 - percent);
}

//! Linearly interpolates `v1` and `v2`.
//! Non-Uniform operation
template<std::floating_point T, CArithmetic U, std::size_t N>
constexpr auto lerp(const Vector<T, N>& v1, const Vector<T, N>& v2, const Vector<U, N>& percent) {
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

}  // namespace xme::math
