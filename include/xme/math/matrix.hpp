#pragma once
#include "concepts.hpp"
#include "vector.hpp"
#include <array>

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
            m_data[i][i] = static_cast<T>(s);
    }

    template<CArithmetic... Args, std::size_t Size>
        requires(sizeof...(Args) == Cols)
    constexpr Matrix(const Vector<Args, Size>&... args) noexcept : m_data({args...}) {}

    constexpr auto operator+() const noexcept;
    constexpr auto operator-() const noexcept;

    template<CArithmetic U>
    constexpr auto operator+(U s) const noexcept;
    template<typename U>
    constexpr auto operator+(const Matrix<U, Cols, Rows>& m) const noexcept;

    template<CArithmetic U>
    constexpr auto operator-(U s) const noexcept;
    template<typename U>
    constexpr auto operator-(const Matrix<U, Cols, Rows>& m) const noexcept;

    template<CArithmetic U>
    constexpr auto operator*(U s) const noexcept;
    template<typename U, std::size_t Rows2>
    constexpr auto operator*(const Matrix<U, Rows2, Cols>& m) const noexcept;
    template<typename U>
    constexpr auto operator*(const Vector<U, Cols>& m) const noexcept;

    template<CArithmetic U>
    constexpr auto operator/(U s) const noexcept;

    template<typename U>
    constexpr auto& operator=(const Matrix<U, Cols, Rows>& m) noexcept;

    template<CArithmetic U>
    constexpr auto& operator+=(U s) noexcept;
    template<typename U>
    constexpr auto& operator+=(const Matrix<U, Cols, Rows>& m) noexcept;

    template<CArithmetic U>
    constexpr auto& operator-=(U s) noexcept;
    template<typename U>
    constexpr auto& operator-=(const Matrix<U, Cols, Rows>& m) noexcept;

    template<CArithmetic U>
    constexpr auto& operator*=(U s) noexcept;

    template<CArithmetic U>
    constexpr auto& operator/=(U s) noexcept;

    constexpr auto& operator[](std::size_t i) noexcept { return m_data[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return m_data[i]; }

    constexpr auto& operator[](std::size_t i, std::size_t j) noexcept {
        return m_data[i][j];
    }
    constexpr auto& operator[](std::size_t i, std::size_t j) const noexcept {
        return m_data[i][j];
    }

    constexpr auto row(std::size_t row) const noexcept;

    constexpr auto column(std::size_t column) const noexcept;

    constexpr auto transpose() const noexcept;

    template<typename U>
    constexpr auto translate(const xme::Vector<U, 3>& v) const noexcept;

    template<typename U>
    constexpr auto scale(const xme::Vector<U, 3>& v) const noexcept;

    template<typename U>
    constexpr auto rotate(auto angle, const xme::Vector<U, 3>& normal) const noexcept;

private:
    std::array<column_type, Cols> m_data{};
};

template<typename T, typename... Args, std::size_t Rows>
Matrix(Vector<T, Rows>, Vector<Args, Rows>...)
    -> Matrix<std::common_type_t<T, Args...>, sizeof...(Args) + 1, Rows>;
} // namespace xme

#include "../../../private/math/matrices/io.hpp"
#include "../../../private/math/matrices/operators.hpp"
#include "../../../private/math/matrices/methods.hpp"