#pragma once
#include "concepts.hpp"
#include "vector.hpp"
#include <array>

#define MATRIX_OP(op)                                                                    \
    using t = std::remove_cvref_t<decltype(n)>;                                          \
    Matrix result{0};                                                                    \
    for (std::size_t i = 0; i < Cols; ++i) {                                             \
        if constexpr (std::is_arithmetic_v<t>)                                           \
            result[i] = m_data[i] op n;                                                  \
        else if constexpr (is_matrix<t> && (Cols == t::columns && Rows == t::rows))      \
            result[i] = m_data[i] op n[i];                                               \
        else                                                                             \
            static_assert(                                                               \
                false,                                                                   \
                "Argument must be either arithmetic or Matrix with the same size");      \
    }                                                                                    \
    return result;

#define MATRIX_SELF(op)                                                                  \
    using t = std::remove_cvref_t<decltype(n)>;                                          \
    for (std::size_t i = 0; i < Cols; ++i) {                                             \
        if constexpr (std::is_arithmetic_v<t>)                                           \
            m_data[i] op n;                                                              \
        else if constexpr (is_matrix<t> && (Cols == t::columns && Rows == t::rows))      \
            m_data[i] op n[i];                                                           \
        else                                                                             \
            static_assert(                                                               \
                false,                                                                   \
                "Argument must be either arithmetic or Matrix with the same size");      \
    }                                                                                    \
    return *this;

namespace xme {
template<typename T, std::size_t Cols, std::size_t Rows>
class Matrix {
public:
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

    using row_type = Vector<T, Cols>;
    using column_type = Vector<T, Rows>;

    static constexpr std::size_t rows = Rows;
    static constexpr std::size_t columns = Cols;

    constexpr Matrix(const Matrix&) noexcept = default;
    constexpr Matrix(Matrix&&) noexcept = default;

    constexpr auto operator=(const Matrix&) noexcept -> Matrix& = default;
    constexpr auto operator=(Matrix&&) noexcept -> Matrix& = default;

    constexpr Matrix() noexcept : Matrix(1) {}

    template<CArithmetic U>
    constexpr Matrix(U s) noexcept {
        constexpr std::size_t count = std::min(Cols, Rows);
        for (std::size_t i = 0; i < count; ++i)
            m_data[i][i] = static_cast<T>(s);
    }

    template<CArithmetic... Args, std::size_t Size>
        requires(sizeof...(Args) == Cols)
    constexpr Matrix(const Vector<Args, Size>&... args) noexcept : m_data({args...}) {}

    constexpr auto operator+() const noexcept -> Matrix { return *this; }
    constexpr auto operator-() const noexcept -> Matrix {
        Matrix result{0};
        for (std::size_t i = 0; i < Cols; ++i)
            result[i] = -m_data[i];
        return result;
    }

    constexpr auto operator+(auto&& n) const noexcept -> Matrix { MATRIX_OP(+) }

    constexpr auto operator-(auto&& n) const noexcept -> Matrix { MATRIX_OP(-) }

    template<CArithmetic U>
    constexpr auto operator*(U s) const noexcept -> Matrix {
        Matrix result{0};
        for (std::size_t i = 0; i < Cols; ++i)
            result[i] = m_data[i] * s;
        return result;
    }

    template<std::size_t Rows2>
    constexpr auto operator*(const Matrix<T, Rows2, Cols>& m) const noexcept
        -> Matrix<T, Rows2, Rows> {
        Matrix<T, Rows2, Rows> result{0};
        for (std::size_t rowIndex = 0; rowIndex < Rows; ++rowIndex) {
            const row_type row = this->row(rowIndex);
            for (std::size_t columnIndex = 0; columnIndex < Rows2; ++columnIndex)
                result[columnIndex][rowIndex] = row.dot(m[columnIndex]);
        }
        return result;
    }

    constexpr auto operator*(const Vector<T, Cols>& v) const noexcept -> Vector<T, Rows> {
        Vector<T, Rows> result;
        for (std::size_t i = 0; i < Rows; ++i)
            result[i] = this->row(i).dot(v);
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator/(U s) const noexcept -> Matrix {
        Matrix result{0};
        for (std::size_t i = 0; i < Cols; ++i)
            result[i] = m_data[i] / s;
        return result;
    }

    template<typename U>
    constexpr auto operator=(const Matrix<U, Cols, Rows>& m) noexcept -> Matrix& {
        for (std::size_t i = 0; i < Cols; ++i)
            m_data[i] = m[i];
        return *this;
    }

    constexpr auto operator+=(auto&& n) noexcept -> Matrix& { MATRIX_SELF(+=) }

    constexpr auto operator-=(auto&& n) noexcept -> Matrix& { MATRIX_SELF(-=) }

    template<CArithmetic U>
    constexpr auto operator*=(U s) noexcept -> Matrix& {
        return *this = (*this * s);
    }

    template<CArithmetic U>
    constexpr auto operator/=(U s) noexcept -> Matrix& {
        return *this = (*this / s);
    }

    constexpr auto& operator[](std::size_t i) noexcept { return m_data[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return m_data[i]; }

    constexpr auto& operator[](std::size_t i, std::size_t j) noexcept {
        return m_data[i][j];
    }
    constexpr auto& operator[](std::size_t i, std::size_t j) const noexcept {
        return m_data[i][j];
    }

    constexpr auto row(std::size_t row) const noexcept -> row_type {
        row_type result;
        for (auto i = 0u; i < row_type::size; ++i)
            result[i] = m_data[i][row];
        return result;
    }

    constexpr auto column(std::size_t column) const noexcept -> column_type {
        return m_data[column];
    };

    constexpr auto transpose() const noexcept -> Matrix<T, Rows, Cols> {
        Matrix<T, Rows, Cols> result;
        for (std::size_t i = 0; i < Cols; ++i) {
            for (std::size_t j = 0; j < Rows; ++j) {
                result[j][i] = m_data[i][j];
            }
        }
        return result;
    }

    constexpr auto translate(const xme::Vector<T, 3>& v) const noexcept -> Matrix {
        return {
            m_data[0],
            m_data[1],
            m_data[2],
            m_data[0] * v[0] + m_data[1] * v[1] + m_data[2] * v[2] + m_data[3],
        };
    }

    constexpr auto scale(const xme::Vector<T, 3>& v) const noexcept -> Matrix {
        return {
            m_data[0] * v[0],
            m_data[1] * v[1],
            m_data[2] * v[2],
            m_data[3],
        };
    }

    constexpr auto rotate(T angle, const xme::Vector<T, 3>& normal) const noexcept {
        const auto s{std::sin(angle)};
        const auto c{std::cos(angle)};

        const Vector<T, 3> temp{normal * (1 - c)};

        Matrix<T, 4> rotation;

        rotation[0][1] = temp[0] * normal[1] + s * normal[2];
        rotation[0][2] = temp[0] * normal[2] - s * normal[1];

        rotation[1][0] = temp[1] * normal[0] - s * normal[2];
        rotation[1][2] = temp[1] * normal[2] + s * normal[0];

        rotation[2][0] = temp[2] * normal[0] + s * normal[1];
        rotation[2][1] = temp[2] * normal[1] - s * normal[0];

        Matrix<T, 4> result;
        for (std::size_t i = 0; i < 3; ++i) {
            rotation[i][i] = c + temp[i] * normal[i];
            result[i] = m_data[0] * rotation[i][0] + m_data[1] * rotation[i][1] +
                        m_data[2] * rotation[i][2];
        }
        result[3] = m_data[3];
        return result;
    }

private:
    std::array<column_type, Cols> m_data{};
};

template<typename T, std::size_t Cols, std::size_t Rows>
constexpr bool operator==(const Matrix<T, Cols, Rows>& m1,
                          const Matrix<T, Cols, Rows>& m2) noexcept {
    for (std::size_t i = 0; i < Cols; ++i) {
        if (m1[i] != m2[i])
            return false;
    }
    return true;
}

template<typename T, std::size_t Cols, std::size_t Rows>
constexpr bool operator!=(const Matrix<T, Cols, Rows>& m1,
                          const Matrix<T, Cols, Rows>& m2) noexcept {
    return !operator==(m1, m2);
}

template<typename T, typename... Args, std::size_t Rows>
Matrix(Vector<T, Rows>, Vector<Args, Rows>...)
    -> Matrix<std::common_type_t<T, Args...>, sizeof...(Args) + 1, Rows>;
} // namespace xme

#undef MATRIX_OP

#include "../../../private/math/matrices/io.hpp"