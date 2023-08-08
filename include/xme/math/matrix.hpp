#pragma once
#include <array>

#include "vector.hpp"

namespace xme {
template<std::size_t Cols, std::size_t Rows>
concept CSquareMatrix = Cols == Rows;

template<typename T, std::size_t Cols, std::size_t Rows>
class Matrix {
public:
    using row_type = Vector<T, Cols>;
    using column_type = Vector<T, Rows>;

    static constexpr std::size_t rows = Rows;
    static constexpr std::size_t columns = Cols;

    constexpr Matrix() noexcept : Matrix(1) {}

    template<typename U>
    constexpr Matrix(U s) noexcept {
        constexpr std::size_t count = std::min(Cols, Rows);
        for (auto i = 0; i < count; ++i)
            m_Data[i][i] = static_cast<T>(s);
    }

    constexpr Matrix(auto x0, auto y0, auto x1, auto y1) noexcept
        requires CSquareMatrix<Cols, Rows> && (Cols == 2)
        : m_Data({{x0, y0}, {x1, y1}}) {}

    constexpr Matrix(auto x0, auto y0, auto z0, auto x1, auto y1, auto z1, auto x2,
                     auto y2, auto z2) noexcept
        requires CSquareMatrix<Cols, Rows> && (Cols == 3)
        : m_Data({{x0, y0, z0}, {x1, y1, z1}, {x2, y2, z2}}) {}

    constexpr Matrix(auto x0, auto y0, auto z0, auto w0, auto x1, auto y1, auto z1,
                     auto w1, auto x2, auto y2, auto z2, auto w2, auto x3, auto y3,
                     auto z3, auto w3) noexcept
        requires CSquareMatrix<Cols, Rows> && (Cols == 4)
        : m_Data(
              {{x0, y0, z0, w0}, {x1, y1, z1, w1}, {x2, y2, z2, w2}, {x3, y3, z3, w3}}) {}

    template<typename... Args, std::size_t Size>
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