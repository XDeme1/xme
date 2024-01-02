#pragma once
#include <xme/math/vector.hpp>
#include <xme/math/matrices/matrix_functions.hpp>
#include <xme/math/matrices/matrix_transformation.hpp>

#define MAT_OP1(op)                                               \
    [[nodiscard]]                                                 \
    constexpr auto operator op(auto s) const noexcept -> Matrix { \
        return {m_data[0] op static_cast<T>(s),                   \
                m_data[1] op static_cast<T>(s),                   \
                m_data[2] op static_cast<T>(s),                   \
                m_data[3] op static_cast<T>(s)};                  \
    }

#define MAT_OP2(op)                                                                          \
    MAT_OP1(op)                                                                              \
    template<typename U>                                                                     \
    [[nodiscard]]                                                                            \
    constexpr auto operator op(const Matrix<U, 4, 4>& m) const noexcept -> Matrix {          \
        return {m_data[0] op m[0], m_data[1] op m[1], m_data[2] op m[2], m_data[3] op m[3]}; \
    }

#define MAT_SELF_OP1(op)                                     \
    constexpr auto operator op(auto s) noexcept -> Matrix& { \
        for(std::size_t i = 0; i < 4; ++i)                   \
            (*this)[i] op static_cast<T>(s);                 \
        return *this;                                        \
    }

#define MAT_SELF_OP2(op)                                                       \
    MAT_SELF_OP1(op)                                                           \
    template<typename U>                                                       \
    constexpr auto operator op(const Matrix<U, 4, 4>& m) noexcept -> Matrix& { \
        for(std::size_t i = 0; i < 4; ++i)                                     \
            (*this)[i] op m[i];                                                \
        return *this;                                                          \
    }

namespace xme::math {
template<CFloatingPoint T, std::size_t Cols, std::size_t Rows>
class Matrix;

template<CFloatingPoint T>
class Matrix<T, 4, 4> {
public:
    using row_type    = Vector<T, 4>;
    using column_type = Vector<T, 4>;

    static constexpr std::size_t rows    = 4;
    static constexpr std::size_t columns = 4;

    constexpr Matrix() noexcept : Matrix(1) {}

    template<typename U>
    explicit constexpr Matrix(U s) noexcept :
      m_data{
          column_type{s, 0, 0, 0},
          column_type{0, s, 0, 0},
          column_type{0, 0, s, 0},
          column_type{0, 0, 0, s}
    } {}

    template<typename... Args>
    constexpr Matrix(const Vector<Args, 4>&... args) noexcept :
      m_data({static_cast<column_type>(args)...}) {}

    template<typename U>
    explicit constexpr Matrix(const Matrix<U, 4, 4>& m) noexcept :
      m_data({m[0], m[1], m[2], m[3]}) {}

    template<typename U>
    explicit constexpr Matrix(const Matrix<U, 3, 3>& m) noexcept :
      m_data({
          column_type{m[0], 0},
          column_type{m[1], 0},
          column_type{m[2], 0},
          column_type{0, 0, 0, 1}
    }) {}

    [[nodiscard]]
    constexpr auto operator-() const noexcept -> Matrix {
        return {-(*this)[0], -(*this)[1], -(*this)[2], -(*this)[3]};
    }

    MAT_OP2(+)
    MAT_OP2(-)
    MAT_OP1(*)
    MAT_OP1(/)

    template<typename U>
    [[nodiscard]]
    constexpr auto operator*(const Vector<U, 4>& v) const noexcept -> column_type {
        return {
            math::dot(row(0), v),
            math::dot(row(1), v),
            math::dot(row(2), v),
            math::dot(row(3), v),
        };
    }

    template<typename U, std::size_t Rows2>
    [[nodiscard]]
    constexpr auto operator*(const Matrix<U, Rows2, 4>& m) const noexcept -> Matrix<T, Rows2, 4> {
        Matrix<T, Rows2, 4> result{0};
        for(std::size_t rowIndex = 0; rowIndex < 4; ++rowIndex) {
            const row_type row = this->row(rowIndex);
            for(std::size_t columnIndex = 0; columnIndex < Rows2; ++columnIndex)
                result[columnIndex][rowIndex] = dot(row, m[columnIndex]);
        }
        return result;
    }

    template<typename U>
    constexpr auto operator=(const Matrix<U, 4, 4>& m) noexcept -> Matrix& {
        m_data[0] = m[0];
        m_data[1] = m[1];
        m_data[2] = m[2];
        m_data[3] = m[3];
        return *this;
    }

    MAT_SELF_OP2(+=)
    MAT_SELF_OP2(-=)
    MAT_SELF_OP1(*=)
    MAT_SELF_OP1(/=)

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) noexcept -> column_type& {
        return m_data[i];
    }

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) const noexcept -> const column_type& {
        return m_data[i];
    }

    [[nodiscard]]
    constexpr bool operator==(const Matrix&) const noexcept = default;

    [[nodiscard]]
    constexpr auto operator<=>(const Matrix&) const noexcept = default;

    [[nodiscard]]
    constexpr auto row(std::size_t row) const noexcept -> row_type {
        return {(*this)[0][row], (*this)[1][row], (*this)[2][row], (*this)[3][row]};
    }

    [[nodiscard]]
    constexpr auto column(std::size_t column) const noexcept -> column_type {
        return m_data[column];
    }

    [[nodiscard]]
    constexpr auto determinant() const noexcept -> T {
        return math::determinant(*this);
    }

    [[nodiscard]]
    constexpr auto transpose() const noexcept -> Matrix {
        return math::transpose(*this);
    }

private:
    std::array<column_type, 4> m_data{};
};
}  // namespace xme::math

#undef MAT_OP1
#undef MAT_OP2
#undef MAT_SELF_OP1
#undef MAT_SELF_OP2
