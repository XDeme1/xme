#pragma once
#include "vector.hpp"

namespace xme {
template<typename T, std::size_t Cols, std::size_t Rows>
class Matrix {
public:
    static_assert(std::is_floating_point_v<T>, "T must be a floating type");

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

    template<typename U>
    constexpr Matrix(const Matrix<U, Cols, Rows>& m) noexcept {
        for(std::size_t i = 0; i < Cols; ++i)
            m_data[i] = m[i];
    }
    
    constexpr auto operator-() const noexcept -> Matrix {
        Matrix result{0};
        for (std::size_t i = 0; i < Cols; ++i)
            result[i] = -m_data[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator+(U s) const noexcept -> Matrix {
        Matrix result{0};
        for (std::size_t i = 0; i < Cols; ++i)
            result[i] = m_data[i] + s;
        return result;
    }
    template<typename U>
    constexpr auto operator+(const Matrix<U, Cols, Rows>& m) const noexcept -> Matrix {
        Matrix result{0};
        for (std::size_t i = 0; i < Cols; ++i)
            result[i] = m_data[i] + m[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator-(U s) const noexcept -> Matrix {
        Matrix result{0};
        for (std::size_t i = 0; i < Cols; ++i)
            result[i] = m_data[i] - s;
        return result;
    }
    template<typename U>
    constexpr auto operator-(const Matrix<U, Cols, Rows>& m) const noexcept -> Matrix {
        Matrix result{0};
        for (std::size_t i = 0; i < Cols; ++i)
            result[i] = m_data[i] - m[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator*(U s) const noexcept -> Matrix {
        Matrix result{0};
        for (std::size_t i = 0; i < Cols; ++i)
            result[i] = m_data[i] * s;
        return result;
    }

    template<typename U>
    constexpr auto operator*(const Vector<U, Cols>& v) const noexcept -> column_type {
        column_type result;
        for (std::size_t i = 0; i < Rows; ++i)
            result[i] = this->row(i).dot(v);
        return result;
    }
    template<typename U, std::size_t Rows2>
    constexpr auto operator*(const Matrix<U, Rows2, Cols>& m) const noexcept
        -> Matrix<T, Rows2, Rows> {
        Matrix<T, Rows2, Rows> result{0};
        for (std::size_t rowIndex = 0; rowIndex < Rows; ++rowIndex) {
            const row_type row = this->row(rowIndex);
            for (std::size_t columnIndex = 0; columnIndex < Rows2; ++columnIndex)
                result[columnIndex][rowIndex] = row.dot(m[columnIndex]);
        }
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

    template<CArithmetic U>
    constexpr auto operator+=(U s) noexcept -> Matrix& {
        for (std::size_t i = 0; i < Cols; ++i)
            m_data[i] += s;
        return *this;
    }
    template<typename U>
    constexpr auto operator+=(const Matrix<U, Cols, Rows>& m) noexcept -> Matrix& {
        for (std::size_t i = 0; i < Cols; ++i)
            m_data[i] += m[i];
        return *this;
    }

    template<CArithmetic U>
    constexpr auto operator-=(U s) noexcept -> Matrix& {
        for (std::size_t i = 0; i < Cols; ++i)
            m_data[i] -= s;
        return *this;
    }
    template<typename U>
    constexpr auto operator-=(const Matrix<U, Cols, Rows>& m) noexcept -> Matrix& {
        for (std::size_t i = 0; i < Cols; ++i)
            m_data[i] -= m[i];
        return *this;
    }

    template<CArithmetic U>
    constexpr auto operator*=(U s) noexcept -> Matrix& {
        for(std::size_t i = 0; i < Cols; ++i)
            m_data[i] *= s;
        return *this;
    }

    template<CArithmetic U>
    constexpr auto operator/=(U s) noexcept -> Matrix& {
        for(std::size_t i = 0; i < Cols; ++i)
            m_data[i] /= s;
        return *this;
    }

    constexpr auto& operator[](std::size_t i) noexcept { return m_data[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return m_data[i]; }

    constexpr auto operator<=>(const Matrix&) const noexcept = default;
    
    constexpr bool operator==(const Matrix&) const noexcept = default;

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
        Matrix<T, Rows, Cols> result{0};
        for (std::size_t i = 0; i < Cols; ++i) {
            for (std::size_t j = 0; j < Rows; ++j) {
                result[j][i] = m_data[i][j];
            }
        }
        return result;
    }

    template<typename U>
    constexpr auto translate(const xme::Vector<U, 3>& v) const noexcept -> Matrix {
        return {
            m_data[0],
            m_data[1],
            m_data[2],
            m_data[0] * v[0] + m_data[1] * v[1] + m_data[2] * v[2] + m_data[3],
        };
    }

    template<typename U>
    constexpr auto scale(const xme::Vector<U, 3>& v) const noexcept -> Matrix {
        return {
            m_data[0] * v[0],
            m_data[1] * v[1],
            m_data[2] * v[2],
            m_data[3],
        };
    }

    template<CArithmetic U1, typename U2>
    constexpr auto rotate(U1 angle, const xme::Vector<U2, 3>& normal) const noexcept {
        const auto s{std::sin(angle)};
        const auto c{std::cos(angle)};

        const Vector<T, 3> temp{normal * (1 - c)};

        Matrix<T, 4> rotation;

        rotation[0][0] = c + temp[0] * normal[0];
        rotation[0][1] = temp[0] * normal[1] + s * normal[2];
        rotation[0][2] = temp[0] * normal[2] - s * normal[1];

        rotation[1][0] = temp[1] * normal[0] - s * normal[2];
        rotation[1][1] = c + temp[1] * normal[1];
        rotation[1][2] = temp[1] * normal[2] + s * normal[0];

        rotation[2][0] = temp[2] * normal[0] + s * normal[1];
        rotation[2][1] = temp[2] * normal[1] - s * normal[0];
        rotation[2][2] = c + temp[2] * normal[2];

        Matrix<T, 4> result;
        for (std::size_t i = 0; i < 3; ++i) {
            result[i] = m_data[0] * rotation[i][0] + m_data[1] * rotation[i][1] +
                        m_data[2] * rotation[i][2];
        }
        result[3] = m_data[3];
        return result;
    }

private:
    std::array<column_type, Cols> m_data{};
};

template<typename T, typename... Args, std::size_t Rows>
Matrix(Vector<T, Rows>, Vector<Args, Rows>...)
    -> Matrix<std::common_type_t<T, Args...>, sizeof...(Args) + 1, Rows>;
} // namespace xme

#include "../../../private/math/matrices/io.hpp"