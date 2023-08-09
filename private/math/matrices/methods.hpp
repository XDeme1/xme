#pragma once
#include <xme/math/matrix.hpp>

namespace xme {
template<typename T, std::size_t Cols, std::size_t Rows>
constexpr auto Matrix<T, Cols, Rows>::row(std::size_t row) const noexcept {
    row_type result;
    for (auto i = 0u; i < row_type::size; ++i)
        result[i] = m_Data[i][row];
    return result;
}

template<typename T, std::size_t Cols, std::size_t Rows>
constexpr auto Matrix<T, Cols, Rows>::column(std::size_t column) const noexcept {
    return m_Data[column];
}

template<typename T, std::size_t Cols, std::size_t Rows>
constexpr auto Matrix<T, Cols, Rows>::transpose() const noexcept {
    Matrix<T, Rows, Cols> result;
    for (auto i = 0; i < Cols; ++i) {
        for (auto j = 0; j < Rows; ++j) {
            result[j][i] = m_Data[i][j];
        }
    }
    return result;
}

template<typename T, std::size_t Cols, std::size_t Rows>
template<typename U>
constexpr auto Matrix<T, Cols, Rows>::translate(const xme::Vector<U, 3>& v) const noexcept {
    return Matrix{
        m_Data[0],
        m_Data[1],
        m_Data[2],
        m_Data[0] * v[0] + m_Data[1] * v[1] + m_Data[2] * v[2] + m_Data[3],
    };
}

template<typename T, std::size_t Cols, std::size_t Rows>
template<typename U>
constexpr auto Matrix<T, Cols, Rows>::scale(const xme::Vector<U, 3>& v) const noexcept {
    return Matrix{
        m_Data[0] * v[0],
        m_Data[1] * v[1],
        m_Data[2] * v[2],
        m_Data[3],
    };
}
} // namespace xme