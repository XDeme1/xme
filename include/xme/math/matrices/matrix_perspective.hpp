#pragma once
#include <cmath>
#include <xme/setup.hpp>
#include <xme/core/concepts/concepts.hpp>

//! http://www.songho.ca/opengl/gl_projectionmatrix.html
namespace xme::math {
template<floating_point T, std::size_t Cols, std::size_t Rows>
class Matrix;

template<floating_point T>
[[nodiscard]]
XME_INLINE constexpr auto perspective_rh(T fov, T aspect_ratio, T near,
                                         T far) noexcept -> Matrix<T, 4, 4> {
    const auto halfTan = std::tan(fov / 2);

    Matrix<T, 4, 4> result{0};
    result[0][0] = 1 / (aspect_ratio * halfTan);
    result[1][1] = 1 / halfTan;
    result[2][2] = -(far + near) / (far - near);
    result[2][3] = -1;
    result[3][2] = -(2 * far * near) / (far - near);
    return result;
}

template<floating_point T>
[[nodiscard]]
XME_INLINE constexpr auto perspective_lh(T fov, T aspect_ratio, T near,
                                         T far) noexcept -> Matrix<T, 4, 4> {
    const auto halfTan = std::tan(fov / 2);

    Matrix<T, 4, 4> result{0};
    result[0][0] = 1 / (aspect_ratio * halfTan);
    result[1][1] = 1 / halfTan;
    result[2][2] = (far + near) / (far - near);
    result[2][3] = 1;
    result[3][2] = -(2 * far * near) / (far - near);
    return result;
}

template<floating_point T>
[[nodiscard]]
XME_INLINE constexpr auto perspective(T fov, T aspect_ratio, T near,
                                      T far) noexcept -> Matrix<T, 4, 4> {
#if defined(XME_MATH_CLIP_LH)
    return perspective_rh(fov, aspect_ratio, far, near);
#else
    return perspective_rh(fov, aspect_ratio, near, far);
#endif
}

template<floating_point T>
[[nodiscard]]
XME_INLINE constexpr auto perspective_lh(T left, T right, T bottom, T top, T near,
                                         T far) noexcept -> Matrix<T, 4, 4> {
    Matrix<T, 4, 4> result{0};
    result[0][0] = (2 * near) / (right - left);
    result[1][1] = (2 * near) / (top - bottom);
    result[2][0] = -(right + left) / (right - near);
    result[2][1] = -(top + bottom) / (top - bottom);
    result[2][2] = (far + near) / (far - near);
    result[2][3] = 1;
    result[3][2] = -(2 * far * near) / (far - near);
    return result;
}

template<floating_point T>
[[nodiscard]]
XME_INLINE constexpr auto perspective_rh(T left, T right, T bottom, T top, T near,
                                         T far) noexcept -> Matrix<T, 4, 4> {
    Matrix<T, 4, 4> result{0};
    result[0][0] = (2 * near) / (right - left);
    result[1][1] = (2 * near) / (top - bottom);
    result[2][0] = (right + left) / (right - near);
    result[2][1] = (top + bottom) / (top - bottom);
    result[2][2] = -(far + near) / (far - near);
    result[2][3] = -1;
    result[3][2] = -(2 * far * near) / (far - near);
    return result;
}

template<floating_point T>
[[nodiscard]]
XME_INLINE constexpr auto perspective(T left, T right, T bottom, T top, T near,
                                      T far) noexcept -> Matrix<T, 4, 4> {
#if defined(XME_MATH_CLIP_LH)
    return perspective_lh(left, right, bottom, top, near, far);
#else
    return perspective_rh(left, right, bottom, top, near, far);
#endif
}

template<floating_point T>
[[nodiscard]]
XME_INLINE constexpr auto ortho_lh(T left, T right, T bottom, T top, T near,
                                   T far) noexcept -> Matrix<T, 4, 4> {
    Matrix<T, 4, 4> result{1};
    result[0][0] = 2 / (right - left);
    result[1][1] = 2 / (top - bottom);
    result[1][1] = 2 / (far - near);
    result[2][0] = -(right + left) / (right - left);
    result[2][1] = -(top + bottom) / (top - bottom);
    result[2][2] = -(far + near) / (far - near);
    return result;
}

template<floating_point T>
[[nodiscard]]
XME_INLINE constexpr auto ortho_rh(T left, T right, T bottom, T top, T near,
                                   T far) noexcept -> Matrix<T, 4, 4> {
    Matrix<T, 4, 4> result{1};
    result[0][0] = 2 / (right - left);
    result[1][1] = 2 / (top - bottom);
    result[1][1] = -2 / (far - near);
    result[2][0] = -(right + left) / (right - left);
    result[2][1] = -(top + bottom) / (top - bottom);
    result[2][2] = -(far + near) / (far - near);
    return result;
}

template<floating_point T>
[[nodiscard]]
XME_INLINE constexpr auto ortho(T left, T right, T bottom, T top, T near,
                                T far) noexcept -> Matrix<T, 4, 4> {
#if defined(XME_MATH_CLIP_LH)
    return ortho_lh(left, right, bottom, top, near, far);
#else
    return ortho_rh(left, right, bottom, top, near, far);
#endif
}
}  // namespace xme::math
