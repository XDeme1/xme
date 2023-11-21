#pragma once
#include <type_traits>
#include "vector.hpp"
#include "matrices/matrix_functions.hpp"

#define MAT_OP1(op)                                            \
    template<typename U>                                       \
    constexpr auto operator op(U s) const noexcept -> Matrix { \
        Matrix result{0};                                      \
        for(std::size_t i = 0; i < Cols; ++i)                  \
            result[i] = ((*this)[i] op s);                     \
        return result;                                         \
    }

#define MAT_OP2(op)                                                                       \
    MAT_OP1(op)                                                                           \
    template<typename U>                                                                  \
    constexpr auto operator op(const Matrix<U, Cols, Rows>& m) const noexcept -> Matrix { \
        Matrix result{0};                                                                 \
        for(std::size_t i = 0; i < Cols; ++i)                                             \
            result[i] = ((*this)[i] op m[i]);                                             \
        return result;                                                                    \
    }

#define MAT_SELF_OP1(op)                                  \
    template<typename U>                                  \
    constexpr auto operator op(U s) noexcept -> Matrix& { \
        for(std::size_t i = 0; i < Cols; ++i)             \
            (*this)[i] op s;                              \
        return *this;                                     \
    }

#define MAT_SELF_OP2(op)                                                             \
    MAT_SELF_OP1(op)                                                                 \
    template<typename U>                                                             \
    constexpr auto operator op(const Matrix<U, Cols, Rows>& m) noexcept -> Matrix& { \
        for(std::size_t i = 0; i < Cols; ++i)                                        \
            (*this)[i] op m[i];                                                      \
        return *this;                                                                \
    }

namespace xme::math {
template<XME_CONCEPT(std::floating_point, T), std::size_t Cols, std::size_t Rows = Cols>
class Matrix {
public:
    using row_type    = Vector<T, Cols>;
    using column_type = Vector<T, Rows>;

    static constexpr std::size_t rows    = Rows;
    static constexpr std::size_t columns = Cols;

    constexpr Matrix() noexcept : Matrix(1) {}

    template<XME_CONCEPT(CArithmetic, U)>
    explicit constexpr Matrix(U s) noexcept {
        constexpr std::size_t count = std::min(Cols, Rows);
        for(std::size_t i = 0; i < count; ++i)
            m_data[i][i] = static_cast<T>(s);
    }

    template<typename... Args, std::size_t Size>
    constexpr Matrix(const Vector<Args, Size>&... args) noexcept : m_data({args...}) {
        static_assert(sizeof...(Args) == Cols);
    }

    template<typename U>
    explicit constexpr Matrix(const Matrix<U, Cols, Rows>& m) noexcept {
        for(std::size_t i = 0; i < Cols; ++i)
            m_data[i] = m[i];
    }

    constexpr auto operator-() const noexcept -> Matrix {
        Matrix result{0};
        for(std::size_t i = 0; i < Cols; ++i)
            result[i] = -m_data[i];
        return result;
    }

    MAT_OP2(+)
    MAT_OP2(-)
    MAT_OP1(*)
    MAT_OP1(/)

    template<typename U>
    constexpr auto operator*(const Vector<U, Cols>& v) const noexcept -> column_type {
        column_type result;
        for(std::size_t i = 0; i < Rows; ++i)
            result[i] = this->row(i).dot(v);
        return result;
    }
    template<typename U, std::size_t Rows2>
    constexpr auto operator*(const Matrix<U, Rows2, Cols>& m) const noexcept
        -> Matrix<T, Rows2, Rows> {
        Matrix<T, Rows2, Rows> result{0};
        for(std::size_t rowIndex = 0; rowIndex < Rows; ++rowIndex) {
            const row_type row = this->row(rowIndex);
            for(std::size_t columnIndex = 0; columnIndex < Rows2; ++columnIndex)
                result[columnIndex][rowIndex] = row.dot(m[columnIndex]);
        }
        return result;
    }

    template<typename U>
    constexpr auto operator=(const Matrix<U, Cols, Rows>& m) noexcept -> Matrix& {
        for(std::size_t i = 0; i < Cols; ++i)
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
        for(std::size_t i = 0; i < Cols; ++i) {
            if((*this)[i] != m[i]) return false;
        }
        return true;
    }

    constexpr bool operator!=(const Matrix& m) const noexcept { return !operator==(m); }
#endif

    constexpr auto row(std::size_t row) const noexcept -> row_type {
        row_type result;
        for(std::size_t i = 0; i < row_type::size; ++i)
            result[i] = m_data[i][row];
        return result;
    }

    constexpr auto column(std::size_t column) const noexcept -> column_type {
        return m_data[column];
    };

    constexpr auto determinant() const noexcept -> T { return math::determinant(*this); }

    constexpr auto transpose() const noexcept -> Matrix<T, Rows, Cols> {
        return math::transpose(*this);
    }

private:
    std::array<column_type, Cols> m_data{};
};

template<typename T, typename... Args, std::size_t Rows>
Matrix(Vector<T, Rows>, Vector<Args, Rows>...)
    -> Matrix<typename std::common_type<T, Args...>::type, sizeof...(Args) + 1, Rows>;

template<XME_CONCEPT(std::floating_point, T)>
constexpr auto perspective_rh(T fov, T aspect_ratio, T far, T near) -> Matrix<T, 4> {
    const auto halfTan = std::tan(fov / 2);

    Matrix<T, 4> result{0};
    result[0][0] = 1 / (aspect_ratio * halfTan);
    result[1][1] = 1 / halfTan;
    result[2][2] = -(far + near) / (far - near);
    result[2][3] = -1;
    result[3][2] = -(2 * far * near) / (far - near);
    return result;
}

template<XME_CONCEPT(std::floating_point, T)>
constexpr auto perspective(T fov, T aspect_ratio, T far, T near) -> Matrix<T, 4> {
    return perspective_rh(fov, aspect_ratio, far, near);
}
}  // namespace xme::math

#undef MAT_OP1
#undef MAT_OP2
#undef MAT_SELF_OP1
#undef MAT_SELF_OP2

#include "../../../private/math/matrices/matrix4x4.hpp"
