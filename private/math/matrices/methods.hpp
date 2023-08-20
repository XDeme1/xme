#pragma once
#include <xme/math/matrix.hpp>

namespace xme {
template<typename T, std::size_t Cols, std::size_t Rows>
constexpr auto Matrix<T, Cols, Rows>::row(std::size_t row) const noexcept {
    row_type result;
    for (auto i = 0u; i < row_type::size; ++i)
        result[i] = m_data[i][row];
    return result;
}

template<typename T, std::size_t Cols, std::size_t Rows>
constexpr auto Matrix<T, Cols, Rows>::column(std::size_t column) const noexcept {
    return m_data[column];
}

template<typename T, std::size_t Cols, std::size_t Rows>
constexpr auto Matrix<T, Cols, Rows>::transpose() const noexcept {
    Matrix<T, Rows, Cols> result;
    for (auto i = 0; i < Cols; ++i) {
        for (auto j = 0; j < Rows; ++j) {
            result[j][i] = m_data[i][j];
        }
    }
    return result;
}

template<typename T, std::size_t Cols, std::size_t Rows>
template<typename U>
constexpr auto
Matrix<T, Cols, Rows>::translate(const xme::Vector<U, 3>& v) const noexcept {
    return Matrix{
        m_data[0],
        m_data[1],
        m_data[2],
        m_data[0] * v[0] + m_data[1] * v[1] + m_data[2] * v[2] + m_data[3],
    };
}

template<typename T, std::size_t Cols, std::size_t Rows>
template<typename U>
constexpr auto Matrix<T, Cols, Rows>::scale(const xme::Vector<U, 3>& v) const noexcept {
    return Matrix{
        m_data[0] * v[0],
        m_data[1] * v[1],
        m_data[2] * v[2],
        m_data[3],
    };
}

template<typename T, std::size_t Cols, std::size_t Rows>
template<typename U>
constexpr auto Matrix<T, Cols, Rows>::rotate(auto angle, const xme::Vector<U, 3>& v) const noexcept {
    const auto s{std::sin(angle)};
    const auto c{std::cos(angle)};
    
    const Vector<T, 3> normal = v.normalized();
    const Vector<T, 3> temp{normal * (1 - c)};
    
    Matrix<T, 4> rotation;

    rotation[0][1] = temp[0] * normal[1] + s * normal[2];
    rotation[0][2] = temp[0] * normal[2] - s * normal[1];

    rotation[1][0] = temp[1] * normal[0] - s * normal[2];
    rotation[1][2] = temp[1] * normal[2] + s * normal[0];

    rotation[2][0] = temp[2] * normal[0] + s * normal[1];
    rotation[2][1] = temp[2] * normal[1] - s * normal[0];

	Matrix<T, 4> result;
    for(std::size_t i = 0; i < 3; ++i) {
        rotation[i][i] = c + temp[i] * normal[i];
        result[i] = m_data[0] * rotation[i][0] + m_data[1] * rotation[i][1] + m_data[2] * rotation[i][2];
    }
    result[3] = m_data[3];
    return result;
}
} // namespace xme