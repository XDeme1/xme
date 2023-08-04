#pragma once
#include <xme/math/forward.hpp>

#define MATRIX_OP(op) \
template<typename T, std::size_t Cols, std::size_t Rows> \
constexpr auto operator op (const Matrix<T, Cols, Rows>& m, auto s) noexcept { \
    Matrix<decltype(m[0, 0] op s), Cols, Rows> result{0}; \
    for(auto i = 0u; i < Cols; ++i) \
        result[i] = m[i] + s; \
    return result; \
} \
template<typename T, std::size_t Cols, std::size_t Rows> \
constexpr auto operator op (auto s, const Matrix<T, Cols, Rows>& m) noexcept { \
    Matrix<decltype(s op m[0, 0]), Cols, Rows> result{0}; \
    for (auto i = 0u; i < Cols; ++i) \
        result[i] = s op m[i]; \
    return result; \
}

namespace xme {
    template<typename T, typename U, std::size_t Cols, std::size_t Rows>
    constexpr auto operator+(const Matrix<T, Cols, Rows>& m1, const Matrix<U, Cols, Rows>& m2) noexcept {
        Matrix<decltype(m1[0, 0] + m2[0, 0]), Cols, Rows> result{0};
        for (auto i = 0u; i < Cols; ++i) {
            result[i] = m1[i] + m2[i];
        }
        return result;
    }

    template<typename T, typename U, std::size_t Cols, std::size_t Rows>
    constexpr auto operator-(const Matrix<T, Cols, Rows>& m1, const Matrix<U, Cols, Rows>& m2) noexcept {
        Matrix<decltype(m1[0, 0] - m2[0, 0]), Cols, Rows> result{0};
        for (auto i = 0u; i < Cols; ++i) {
            result[i] = m1[i] - m2[i];
        }
        return result;
    }

    template<typename T, typename U, std::size_t Cols, std::size_t Rows, std::size_t Cols2>
    constexpr auto operator*(const Matrix<T, Cols, Rows>& m1, const Matrix<U, Rows, Cols2>& m2) noexcept {
        Matrix<decltype(m1[0, 0]*m2[0, 0]), Cols, Cols2> result{0};
        for (auto rowIndex = 0; rowIndex < Rows; ++rowIndex) {
            const auto row = m1.row(rowIndex);
            for (auto i = 0; i < Cols2; ++i) {
                result[i][rowIndex] = row.dot(m2[i]);
            } 
        }
        return result;
    }

    template<typename T, typename U, std::size_t Cols, std::size_t Rows>
    constexpr auto operator*(const Matrix<T, Cols, Rows>& m, const Vector<U, Rows>& v) noexcept {
        Vector<decltype(m[0, 0]*v[0]), Rows> result;
        for(auto i = 0; i < Rows; ++i) {
            result[i] = v.dot(m.row(i)); 
        }
        return result;
    }

    MATRIX_OP(+)
    MATRIX_OP(-)
    MATRIX_OP(*)
    MATRIX_OP(/)
}

#undef MATRIX_OP