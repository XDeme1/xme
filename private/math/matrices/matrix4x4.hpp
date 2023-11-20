#pragma once
#include <xme/math/vector.hpp>
#include <xme/math/matrices/matrix_functions.hpp>

#define MAT_OP1(op)                                                                  \
    template<typename U>                                                             \
    constexpr auto operator op(U s) const noexcept -> Matrix {                       \
        return {(*this)[0] op s, (*this)[1] op s, (*this)[2] op s, (*this)[3] op s}; \
    }

#define MAT_OP2(op)                                                                              \
    MAT_OP1(op)                                                                                  \
    template<typename U>                                                                         \
    constexpr auto operator op(const Matrix<U, 4, 4>& m) const noexcept -> Matrix {              \
        return {(*this)[0] op m[0], (*this)[1] op m[1], (*this)[2] op m[2], (*this)[3] op m[3]}; \
    }

#define MAT_SELF_OP1(op)                                  \
    template<typename U>                                  \
    constexpr auto operator op(U s) noexcept -> Matrix& { \
        for(std::size_t i = 0; i < 4; ++i)                \
            (*this)[i] op s;                              \
        return *this;                                     \
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
template<XME_CONCEPT(std::floating_point, T), std::size_t Cols, std::size_t Rows>
class Matrix;

template<XME_CONCEPT(std::floating_point, T)>
class Matrix<T, 4, 4> {
public:
    using row_type    = Vector<T, 4>;
    using column_type = Vector<T, 4>;

    static constexpr std::size_t rows    = 4;
    static constexpr std::size_t columns = 4;

    constexpr Matrix() noexcept : Matrix(1) {}

    template<typename U>
    explicit constexpr Matrix(U s) noexcept {
        for(std::size_t i = 0; i < 4; ++i)
            m_data[i][i] = static_cast<T>(s);
    }

    template<typename... Args>
    constexpr Matrix(const Vector<Args, 4>&... args) noexcept : m_data({args...}) {}

    template<typename U>
    explicit constexpr Matrix(const Matrix<U, 4, 4>& m) noexcept {
        for(std::size_t i = 0; i < 4; ++i)
            m_data[i] = m[i];
    }

    template<typename U>
    explicit constexpr Matrix(const Matrix<U, 3, 3>& m) noexcept :
      m_data({
          column_type{m[0], 0},
          column_type{m[1], 0},
          column_type{m[2], 0},
          column_type{0, 0, 0, 1}
    }) {}

    constexpr auto operator-() const noexcept -> Matrix {
        return {-(*this)[0], -(*this)[1], -(*this)[2], -(*this)[3]};
    }

    MAT_OP2(+)
    MAT_OP2(-)
    MAT_OP1(*)
    MAT_OP1(/)

    template<typename U>
    constexpr auto operator*(const Vector<U, 4>& v) const noexcept -> column_type {
        return {this->row(0).dot(v), this->row(1).dot(v), this->row(2).dot(v), this->row(3).dot(v)};
    }

    template<typename U, std::size_t Rows2>
    constexpr auto operator*(const Matrix<U, Rows2, 4>& m) const noexcept -> Matrix<T, Rows2, 4> {
        Matrix<T, Rows2, 4> result{0};
        for(std::size_t rowIndex = 0; rowIndex < 4; ++rowIndex) {
            const row_type row = this->row(rowIndex);
            for(std::size_t columnIndex = 0; columnIndex < Rows2; ++columnIndex)
                result[columnIndex][rowIndex] = row.dot(m[columnIndex]);
        }
        return result;
    }

    template<typename U>
    constexpr auto operator=(const Matrix<U, 4, 4>& m) noexcept -> Matrix& {
        for(std::size_t i = 0; i < 4; ++i)
            m_data[i] = m[i];
        return *this;
    }

    MAT_SELF_OP2(+=)
    MAT_SELF_OP2(-=)
    MAT_SELF_OP1(*=)
    MAT_SELF_OP1(/=)

    constexpr auto operator[](std::size_t i) noexcept -> column_type& { return m_data[i]; }

    constexpr auto operator[](std::size_t i) const noexcept -> const column_type& {
        return m_data[i];
    }

#if defined(__cpp_impl_three_way_comparison)
    constexpr bool operator==(const Matrix&) const noexcept = default;

    constexpr auto operator<=>(const Matrix&) const noexcept = default;
#else
    constexpr bool operator==(const Matrix& m) const noexcept {
        return (*this)[0] == m[0] && (*this)[1] == m[1] && (*this)[2] == m[2] && (*this)[3] == m[3];
    }

    constexpr bool operator!=(const Matrix& m) const noexcept { return !operator==(m); }
#endif

    constexpr auto row(std::size_t row) const noexcept -> row_type {
        return {(*this)[0][row], (*this)[1][row], (*this)[2][row], (*this)[3][row]};
    }

    constexpr auto column(std::size_t column) const noexcept -> column_type {
        return m_data[column];
    };

    constexpr auto determinant() const noexcept -> T { return math::determinant(*this); }

    constexpr auto transpose() const noexcept -> Matrix<T, 4, 4> { return math::transpose(*this); }

    template<typename U>
    constexpr auto translate(const Vector<U, 3>& v) const noexcept -> Matrix {
        return {
            m_data[0],
            m_data[1],
            m_data[2],
            m_data[0] * v[0] + m_data[1] * v[1] + m_data[2] * v[2] + m_data[3],
        };
    }

    template<typename U>
    constexpr auto scale(const Vector<U, 3>& v) const noexcept -> Matrix {
        return {
            m_data[0] * v[0],
            m_data[1] * v[1],
            m_data[2] * v[2],
            m_data[3],
        };
    }

    template<typename U1, typename U2>
    constexpr auto rotate(U1 angle, const Vector<U2, 3>& n) const noexcept {
        const auto s{std::sin(angle)};
        const auto c{std::cos(angle)};

        const Vector<T, 3> temp{n * (1 - c)};

        Matrix rotation;

        rotation[0][0] = c + temp[0] * n[0];
        rotation[0][1] = temp[0] * n[1] + s * n[2];
        rotation[0][2] = temp[0] * n[2] - s * n[1];

        rotation[1][0] = temp[1] * n[0] - s * n[2];
        rotation[1][1] = c + temp[1] * n[1];
        rotation[1][2] = temp[1] * n[2] + s * n[0];

        rotation[2][0] = temp[2] * n[0] + s * n[1];
        rotation[2][1] = temp[2] * n[1] - s * n[0];
        rotation[2][2] = c + temp[2] * n[2];

        Matrix result;
        for(std::size_t i = 0; i < 3; ++i) {
            result[i] = m_data[0] * rotation[i][0] + m_data[1] * rotation[i][1]
                        + m_data[2] * rotation[i][2];
        }
        result[3] = m_data[3];
        return result;
    }

private:
    std::array<column_type, 4> m_data{};
};
}  // namespace xme::math

#undef MAT_OP1
#undef MAT_OP2
#undef MAT_SELF_OP1
#undef MAT_SELF_OP2