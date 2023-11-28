#pragma once
#include <cstddef>
#include <xme/math/concepts.hpp>

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector;
template<std::floating_point T, std::size_t Cols, std::size_t Rows>
class Matrix;

template<typename T>
constexpr auto determinant(const Matrix<T, 2, 2>& m) noexcept -> T {
    return m[0][0] * m[1][1] - m[1][0] * m[0][1];
}
template<typename T>
constexpr auto determinant(const Matrix<T, 3, 3>& m) noexcept -> T {

    const auto cofactor01 = m[0][1] * m[1][2] - m[1][1] * m[0][2];
    const auto cofactor12 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    const auto cofactor02 = m[0][1] * m[2][2] - m[2][1] * m[0][2];
    return m[0][0] * cofactor12 - (m[1][0] * cofactor02) + (m[2][0] * cofactor01);
}

template<typename T>
constexpr auto determinant(const Matrix<T, 4, 4>& m) noexcept -> T {
    const auto cf01 = m[0][2] * m[1][3] - m[1][2] * m[0][3];
    const auto cf12 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
    const auto cf23 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    const auto cf02 = m[0][2] * m[2][3] - m[2][2] * m[0][3];
    const auto cf03 = m[0][2] * m[3][3] - m[3][2] * m[0][3];
    const auto cf13 = m[1][2] * m[3][3] - m[3][2] * m[1][3];

    const auto factor0 = m[0][0] * ((m[1][1] * cf23) - (m[2][1] * cf13) + (m[3][1] * cf12));
    const auto factor1 = m[1][0] * ((m[0][1] * cf23) - (m[2][1] * cf03) + (m[3][1] * cf02));
    const auto factor2 = m[2][0] * ((m[0][1] * cf13) - (m[1][1] * cf03) + (m[3][1] * cf01));
    const auto factor3 = m[3][0] * ((m[0][1] * cf12) - (m[1][1] * cf02) + (m[2][1] * cf01));
    return factor0 - factor1 + factor2 - factor3;
}

template<typename T, std::size_t Cols, std::size_t Rows>
constexpr auto transpose(const Matrix<T, Cols, Rows>& m) noexcept -> Matrix<T, Rows, Cols> {
    Matrix<T, Rows, Cols> result{0};
    for(std::size_t i = 0; i < Cols; ++i) {
        for(std::size_t j = 0; j < Rows; ++j) {
            result[j][i] = m[i][j];
        }
    }
    return result;
}

template<typename T, std::size_t N1, std::size_t N2>
constexpr auto outer_product(const Vector<T, N1>& v1, const Vector<T, N2>& v2) noexcept {
    Matrix<T, N2, N1> result{0};
    for(std::size_t i = 0; i < N2; ++i)
        result[i] = v1 * v2[i];
    return result;
}
}  // namespace xme::math
