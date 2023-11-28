#pragma once
#include <cstddef>
#include <xme/math/vector.hpp>

namespace xme::math {
template<std::floating_point T, std::size_t Cols, std::size_t Rows>
class Matrix;

template<typename T, typename U>
constexpr auto translate(const Matrix<T, 4, 4>& m, const Vector<U, 3>& v) noexcept
    -> Matrix<T, 4, 4> {
    return {
        m[0],
        m[1],
        m[2],
        m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3],
    };
}

template<typename T, typename U>
constexpr auto scale(const Matrix<T, 4, 4>& m, const Vector<U, 3>& v) noexcept -> Matrix<T, 4, 4> {
    return {
        m[0] * v[0],
        m[1] * v[1],
        m[2] * v[2],
        m[3],
    };
}

//! Creates a rotation matrx.
//! `m` matrix to rotate.
//! `angle` angle in radians.
//! `n` normal vector specifying which axis to rotate
template<typename T, typename U>
constexpr auto rotate(const Matrix<T, 4, 4>& m, auto angle, const Vector<U, 3>& n) noexcept
    -> Matrix<T, 4, 4> {
    const auto s{std::sin(static_cast<T>(angle))};
    const auto c{std::cos(static_cast<T>(angle))};

    const Vector<T, 3> temp{n * (1 - c)};

    Matrix<T, 3, 3> Rotate;
    Rotate[0][0] = c + temp[0] * n[0];
    Rotate[0][1] = temp[0] * n[1] + s * n[2];
    Rotate[0][2] = temp[0] * n[2] - s * n[1];

    Rotate[1][0] = temp[1] * n[0] - s * n[2];
    Rotate[1][1] = c + temp[1] * n[1];
    Rotate[1][2] = temp[1] * n[2] + s * n[0];

    Rotate[2][0] = temp[2] * n[0] + s * n[1];
    Rotate[2][1] = temp[2] * n[1] - s * n[0];
    Rotate[2][2] = c + temp[2] * n[2];

    return xme::math::Matrix<T, 4, 4>{
        m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2],
        m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2],
        m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2],
        m[3],
    };
}
}  // namespace xme::math
