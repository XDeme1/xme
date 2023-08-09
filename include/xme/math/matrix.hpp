#pragma once
#include <array>
#include "concepts.hpp"
#include "vector.hpp"

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
        for (auto i = 0; i < count; ++i)
            m_Data[i][i] = static_cast<T>(s);
    }

    template<CArithmetic... Args, std::size_t Size>
        requires(sizeof...(Args) == Cols)
    constexpr Matrix(const Vector<Args, Size>&... args) noexcept : m_Data({args...}) {}

    constexpr auto& operator[](std::size_t i) noexcept { return m_Data[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return m_Data[i]; }

    constexpr auto& operator[](std::size_t i, std::size_t j) noexcept {
        return m_Data[i][j];
    }
    constexpr auto& operator[](std::size_t i, std::size_t j) const noexcept {
        return m_Data[i][j];
    }

    constexpr auto row(std::size_t row) const noexcept {
        row_type result;
        for (auto i = 0u; i < row_type::size; ++i)
            result[i] = m_Data[i][row];
        return result;
    }

    constexpr auto column(std::size_t column) const noexcept { return m_Data[column]; }

    constexpr auto transpose() const noexcept {
        Matrix<T, Rows, Cols> result;
        for (auto i = 0; i < Cols; ++i) {
            for (auto j = 0; j < Rows; ++j) {
                result[j][i] = m_Data[i][j];
            }
        }
        return result;
    }

    template<typename U>
    constexpr auto translate(const xme::Vector<U, 3>& v) const noexcept {
        return Matrix{
            m_Data[0],
            m_Data[1],
            m_Data[2],
            m_Data[0] * v[0] + m_Data[1] * v[1] + m_Data[2] * v[2] + m_Data[3],
        };
    }
    
    template<typename U>
    constexpr auto scale(const xme::Vector<U, 3>& v) const noexcept {
        return Matrix{
            m_Data[0] * v[0],
            m_Data[1] * v[1],
            m_Data[2] * v[2],
            m_Data[3],
        };
    }

private:
    std::array<column_type, Cols> m_Data{};
};

template<typename T, typename... Args, std::size_t Rows,
         typename Tmp = std::common_type_t<T, Args...>>
Matrix(Vector<T, Rows>, Vector<Args, Rows>...)
    -> Matrix<std::conditional_t<std::is_integral_v<Tmp>, float, Tmp>,
              sizeof...(Args) + 1, Rows>;
} // namespace xme

#include "../../../private/math/matrices/io.hpp"
#include "../../../private/math/matrices/matrix_operators.hpp"