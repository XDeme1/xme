#pragma once
#include <cstddef>
#include <xme/setup.hpp>
#include <xme/math/vector.hpp>

namespace xme::math {
template<XME_CONCEPT(std::floating_point, T), std::size_t Cols, std::size_t Rows>
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

template<typename T, typename U1, typename U2>
constexpr auto rotate(const Matrix<T, 4, 4>& m, U1 angle, const Vector<U2, 3>& n) noexcept
    -> Matrix<T, 4, 4> {
    const auto s{std::sin(angle)};
    const auto c{std::cos(angle)};

    const Vector<T, 3> temp{n * (1 - c)};

    Matrix<T, 4, 4> rotation;

    rotation[0][0] = c + temp[0] * n[0];
    rotation[0][1] = temp[0] * n[1] + s * n[2];
    rotation[0][2] = temp[0] * n[2] - s * n[1];

    rotation[1][0] = temp[1] * n[0] - s * n[2];
    rotation[1][1] = c + temp[1] * n[1];
    rotation[1][2] = temp[1] * n[2] + s * n[0];

    rotation[2][0] = temp[2] * n[0] + s * n[1];
    rotation[2][1] = temp[2] * n[1] - s * n[0];
    rotation[2][2] = c + temp[2] * n[2];

    Matrix<T, 4, 4> result;
    for(std::size_t i = 0; i < 3; ++i) {
        result[i] = m[0] * rotation[i][0] + m[1] * rotation[i][1] + m[2] * rotation[i][2];
    }
    result[3] = m[3];
    return result;
}
}  // namespace xme::math
