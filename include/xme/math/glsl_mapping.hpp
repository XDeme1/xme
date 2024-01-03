#pragma once
#include <cstdint>
#include "vector.hpp"
#include "matrix.hpp"

namespace xme::math {
using bvec2 = Vector<bool, 2>;
using bvec3 = Vector<bool, 3>;
using bvec4 = Vector<bool, 4>;

using ivec2 = Vector<std::int32_t, 2>;
using ivec3 = Vector<std::int32_t, 3>;
using ivec4 = Vector<std::int32_t, 4>;

using uvec2 = Vector<std::uint32_t, 2>;
using uvec3 = Vector<std::uint32_t, 3>;
using uvec4 = Vector<std::uint32_t, 4>;

using vec2 = Vector<float, 2>;
using vec3 = Vector<float, 3>;
using vec4 = Vector<float, 4>;

using dvec2 = Vector<double, 2>;
using dvec3 = Vector<double, 3>;
using dvec4 = Vector<double, 4>;

using mat2 = Matrix<float, 2, 2>;
using mat3 = Matrix<float, 3, 3>;
using mat4 = Matrix<float, 4, 4>;

using mat2x2 = Matrix<float, 2, 2>;
using mat2x3 = Matrix<float, 2, 3>;
using mat2x4 = Matrix<float, 2, 4>;

using mat3x2 = Matrix<float, 3, 2>;
using mat3x3 = Matrix<float, 3, 3>;
using mat3x4 = Matrix<float, 3, 4>;

using mat4x2 = Matrix<float, 4, 2>;
using mat4x3 = Matrix<float, 4, 3>;
using mat4x4 = Matrix<float, 4, 4>;

using dmat2 = Matrix<double, 2, 2>;
using dmat3 = Matrix<double, 3, 3>;
using dmat4 = Matrix<double, 4, 4>;

using dmat2x2 = Matrix<double, 2, 2>;
using dmat2x3 = Matrix<double, 2, 3>;
using dmat2x4 = Matrix<double, 2, 4>;

using dmat3x2 = Matrix<double, 3, 2>;
using dmat3x3 = Matrix<double, 3, 3>;
using dmat3x4 = Matrix<double, 3, 4>;

using dmat4x2 = Matrix<double, 4, 2>;
using dmat4x3 = Matrix<double, 4, 3>;
using dmat4x4 = Matrix<double, 4, 4>;

//! Alias for lerp.
//! For compatibility with glsl mix
template<CFloatingPoint T, CArithmetic U, std::size_t N>
XME_INLINE constexpr auto mix(const Vector<T, N>& v1, const Vector<T, N>& v2, U percent) {
    return lerp(v1, v2, percent);
}

//! Alias for lerp.
//! For compatibility with glsl mix
template<CFloatingPoint T, CArithmetic U, std::size_t N>
XME_INLINE constexpr auto mix(const Vector<T, N>& v1, const Vector<T, N>& v2,
                              const Vector<U, N>& percent) {
    return lerp(v1, v2, percent);
}
}  // namespace xme::math
