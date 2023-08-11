#pragma once
#include <xme/math/matrix.hpp>
#include <xme/math/type_traits.hpp>

#define MATRIX_OP(op)                                                                    \
    template<typename T, std::size_t Cols, std::size_t Rows>                             \
    template<CArithmetic U>                                                              \
    constexpr auto Matrix<T, Cols, Rows>::operator op(U s) const noexcept {              \
        Matrix<decltype(m_Data[0][0] op s), Cols, Rows> result{0};                       \
        for (auto i = 0u; i < Cols; ++i)                                                 \
            result[i] = m_Data[i] op s;                                                  \
        return result;                                                                   \
    }

#define MATRIX_OP2(op)                                                                   \
    MATRIX_OP(op)                                                                        \
    template<typename T, std::size_t Cols, std::size_t Rows>                             \
    template<typename U>                                                                 \
    constexpr auto Matrix<T, Cols, Rows>::operator op(const Matrix<U, Cols, Rows>& m)    \
        const noexcept {                                                                 \
        Matrix<decltype(m_Data[0][0] op m[0][0]), Cols, Rows> result{0};                 \
        for (auto i = 0u; i < Cols; ++i)                                                 \
            result[i] = m_Data[i] op m[i];                                               \
        return result;                                                                   \
    }

#define MATRIX_SELF_OP(op)                                                               \
    template<typename T, std::size_t Cols, std::size_t Rows>                             \
    template<CArithmetic U>                                                              \
    constexpr auto& Matrix<T, Cols, Rows>::operator op(U s) noexcept {                   \
        for (auto i = 0u; i < Cols; ++i)                                                 \
            m_Data[i] op s;                                                              \
        return *this;                                                                    \
    }

#define MATRIX_SELF_OP2(op)                                                              \
    MATRIX_SELF_OP(op)                                                                   \
    template<typename T, std::size_t Cols, std::size_t Rows>                             \
    template<typename U>                                                                 \
    constexpr auto& Matrix<T, Cols, Rows>::operator op(                                  \
        const Matrix<U, Cols, Rows>& m) noexcept {                                       \
        for (auto i = 0u; i < Cols; ++i)                                                 \
            m_Data[i] op m[i];                                                           \
        return *this;                                                                    \
    }

namespace xme {
template<typename T, std::size_t Cols, std::size_t Rows>
constexpr auto Matrix<T, Cols, Rows>::operator+() const noexcept {
    return *this;
}

template<typename T, std::size_t Cols, std::size_t Rows>
constexpr auto Matrix<T, Cols, Rows>::operator-() const noexcept {
    Matrix result;
    for (std::size_t i = 0; i < Cols; ++i)
        result[i] = -m_Data[i];
    return result;
}

MATRIX_OP2(+)
MATRIX_OP2(-)
MATRIX_OP(*)
MATRIX_OP(/)

template<typename T, std::size_t Cols, std::size_t Rows>
template<typename U, std::size_t Rows2>
constexpr auto
Matrix<T, Cols, Rows>::operator*(const Matrix<U, Rows2, Cols>& m) const noexcept {
    Matrix<decltype(m_Data[0][0] * m[0][0]), Rows2, Rows> result{0};
    for (auto rowIndex = 0; rowIndex < Rows; ++rowIndex) {
        const auto row = this->row(rowIndex);
        for (auto columnIndex = 0; columnIndex < Rows2; ++columnIndex)
            result[columnIndex][rowIndex] = row.dot(m[columnIndex]);
    }
    return result;
}

template<typename T, std::size_t Cols, std::size_t Rows>
template<typename U>
constexpr auto Matrix<T, Cols, Rows>::operator*(const Vector<U, Cols>& v) const noexcept {
    Vector<decltype(m_Data[0][0] * v[0]), Rows> result;
    for (auto i = 0u; i < Rows; ++i)
        result[i] = this->row(i).dot(v);
    return result;
}

template<typename T, std::size_t Cols, std::size_t Rows>
template<typename U>
constexpr auto&
Matrix<T, Cols, Rows>::operator=(const Matrix<U, Cols, Rows>& m) noexcept {
    for (std::size_t i = 0; i < Cols; ++i)
        m_Data[i] = m[i];
    return *this;
}

MATRIX_SELF_OP2(+=)
MATRIX_SELF_OP2(-=)
MATRIX_SELF_OP(*=)
MATRIX_SELF_OP(/=)

template<typename T, typename U, std::size_t Cols, std::size_t Rows>
constexpr bool operator==(const Matrix<T, Cols, Rows>& m1,
                          const Matrix<U, Cols, Rows>& m2) noexcept {
    for (std::size_t i = 0; i < Cols; ++i) {
        if (m1[i] != m2[i])
            return false;
    }
    return true;
}

template<typename T, typename U, std::size_t Cols, std::size_t Rows>
constexpr bool operator!=(const Matrix<T, Cols, Rows>& m1,
                          const Matrix<U, Cols, Rows>& m2) noexcept {
    return !operator==(m1, m2);
}
} // namespace xme

#undef MATRIX_OP
#undef MATRIX_OP2
#undef MATRIX_SELF_OP
#undef MATRIX_SELF_OP2