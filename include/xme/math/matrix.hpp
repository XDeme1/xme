#pragma once
#include "vector.hpp"

#define MAT_OP1(op)                                               \
    constexpr auto operator op(auto s) const noexcept -> Matrix { \
        Matrix result{0};                                         \
        for(std::size_t i = 0; i < Cols; ++i)                     \
            result[i] = ((*this)[i] op s);                        \
        return result;                                            \
    }

#define MAT_OP2(op)                                                                       \
    MAT_OP1(op);                                                                          \
    template<typename U>                                                                  \
    constexpr auto operator op(const Matrix<U, Cols, Rows>& m) const noexcept -> Matrix { \
        Matrix result{0};                                                                 \
        for(std::size_t i = 0; i < Cols; ++i)                                             \
            result[i] = ((*this)[i] op m[i]);                                             \
        return result;                                                                    \
    }

#define MAT_SELF_OP1(op)                                     \
    constexpr auto operator op(auto s) noexcept -> Matrix& { \
        for(std::size_t i = 0; i < Cols; ++i)                \
            (*this)[i] op s;                                 \
        return *this;                                        \
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
template<std::floating_point T, std::size_t Cols, std::size_t Rows = Cols>
class Matrix {
public:
    using row_type    = Vector<T, Cols>;
    using column_type = Vector<T, Rows>;

    static constexpr std::size_t rows    = Rows;
    static constexpr std::size_t columns = Cols;

    constexpr Matrix() noexcept : Matrix(1) {}

    template<CArithmetic U>
    constexpr Matrix(U s) noexcept {
        constexpr std::size_t count = std::min(Cols, Rows);
        for(std::size_t i = 0; i < count; ++i)
            m_data[i][i] = static_cast<T>(s);
    }

    template<typename... Args, std::size_t Size>
        requires(sizeof...(Args) == Cols)
    constexpr Matrix(const Vector<Args, Size>&... args) noexcept : m_data({args...}) {}

    template<typename U>
    constexpr Matrix(const Matrix<U, Cols, Rows>& m) noexcept {
        for(std::size_t i = 0; i < Cols; ++i)
            m_data[i] = m[i];
    }

    template<typename U>
        requires(Cols == Rows && Cols == 4)
    constexpr Matrix(const Matrix<U, 3, 3>& m) noexcept :
      m_data({
          column_type{m[0], 0},
          column_type{m[1], 0},
          column_type{m[2], 0},
          column_type{0, 0, 0, 1}
    }) {}

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

    constexpr bool operator==(const Matrix&) const noexcept = default;

    constexpr auto operator<=>(const Matrix&) const noexcept = default;

    constexpr auto row(std::size_t row) const noexcept -> row_type {
        row_type result;
        for(std::size_t i = 0; i < row_type::size; ++i)
            result[i] = m_data[i][row];
        return result;
    }

    constexpr auto column(std::size_t column) const noexcept -> column_type {
        return m_data[column];
    };

    constexpr auto determinant() const noexcept -> T
        requires(CEqual<Cols, Rows>) && (CEqual<Cols, 2>)
    {
        return m_data[0][0] * m_data[1][1] - m_data[1][0] * m_data[0][1];
    }

    constexpr auto determinant() const noexcept -> T
        requires(CEqual<Cols, Rows>) && (CEqual<Cols, 3>)
    {
        const auto cofactor01 = m_data[0][1] * m_data[1][2] - m_data[1][1] * m_data[0][2];
        const auto cofactor12 = m_data[1][1] * m_data[2][2] - m_data[2][1] * m_data[1][2];
        const auto cofactor02 = m_data[0][1] * m_data[2][2] - m_data[2][1] * m_data[0][2];
        return m_data[0][0] * cofactor12 - (m_data[1][0] * cofactor02)
               + (m_data[2][0] * cofactor01);
    }

    constexpr auto determinant() const noexcept -> T
        requires(CEqual<Cols, Rows>) && (CEqual<Cols, 4>)
    {
        const auto cf01 = m_data[0][2] * m_data[1][3] - m_data[1][2] * m_data[0][3];
        const auto cf12 = m_data[1][2] * m_data[2][3] - m_data[2][2] * m_data[1][3];
        const auto cf23 = m_data[2][2] * m_data[3][3] - m_data[3][2] * m_data[2][3];
        const auto cf02 = m_data[0][2] * m_data[2][3] - m_data[2][2] * m_data[0][3];
        const auto cf03 = m_data[0][2] * m_data[3][3] - m_data[3][2] * m_data[0][3];
        const auto cf13 = m_data[1][2] * m_data[3][3] - m_data[3][2] * m_data[1][3];

        const auto factor0 =
            m_data[0][0] * ((m_data[1][1] * cf23) - (m_data[2][1] * cf13) + (m_data[3][1] * cf12));
        const auto factor1 =
            m_data[1][0] * ((m_data[0][1] * cf23) - (m_data[2][1] * cf03) + (m_data[3][1] * cf02));
        const auto factor2 =
            m_data[2][0] * ((m_data[0][1] * cf13) - (m_data[1][1] * cf03) + (m_data[3][1] * cf01));
        const auto factor3 =
            m_data[3][0] * ((m_data[0][1] * cf12) - (m_data[1][1] * cf02) + (m_data[2][1] * cf01));
        return factor0 - factor1 + factor2 - factor3;
    }

    constexpr auto transpose() const noexcept -> Matrix<T, Rows, Cols> {
        Matrix<T, Rows, Cols> result{0};
        for(std::size_t i = 0; i < Cols; ++i) {
            for(std::size_t j = 0; j < Rows; ++j) {
                result[j][i] = m_data[i][j];
            }
        }
        return result;
    }

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

        Matrix<T, 4> rotation;

        rotation[0][0] = c + temp[0] * n[0];
        rotation[0][1] = temp[0] * n[1] + s * n[2];
        rotation[0][2] = temp[0] * n[2] - s * n[1];

        rotation[1][0] = temp[1] * n[0] - s * n[2];
        rotation[1][1] = c + temp[1] * n[1];
        rotation[1][2] = temp[1] * n[2] + s * n[0];

        rotation[2][0] = temp[2] * n[0] + s * n[1];
        rotation[2][1] = temp[2] * n[1] - s * n[0];
        rotation[2][2] = c + temp[2] * n[2];

        Matrix<T, 4> result;
        for(std::size_t i = 0; i < 3; ++i) {
            result[i] = m_data[0] * rotation[i][0] + m_data[1] * rotation[i][1]
                        + m_data[2] * rotation[i][2];
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

template<std::floating_point T>
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

template<std::floating_point T>
constexpr auto perspective(T fov, T aspect_ratio, T far, T near) -> Matrix<T, 4> {
    return perspective_rh(fov, aspect_ratio, far, near);
}
}  // namespace xme::math

#undef MAT_OP1
#undef MAT_OP2
#undef MAT_SELF_OP1
#undef MAT_SELF_OP2
