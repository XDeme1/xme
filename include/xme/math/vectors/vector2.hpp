#pragma once
#include <cassert>
#include <cmath>
#include <xme/setup.hpp>
#include <xme/core/concepts/arithmetic.hpp>

#define VEC_OP(op)                                                               \
    [[nodiscard]]                                                                \
    constexpr auto operator op(auto s) const noexcept -> Vector {                \
        return {                                                                 \
            x op static_cast<T>(s),                                              \
            y op static_cast<T>(s),                                              \
        };                                                                       \
    }                                                                            \
    template<typename U>                                                         \
    [[nodiscard]]                                                                \
    constexpr auto operator op(const Vector<U, 2>& v) const noexcept -> Vector { \
        return {                                                                 \
            x op static_cast<T>(v.x),                                            \
            y op static_cast<T>(v.y),                                            \
        };                                                                       \
    }

#define VEC_SELF_OP(op)                                                     \
    constexpr auto operator op(auto s) noexcept -> Vector& {                \
        x op static_cast<T>(s);                                             \
        y op static_cast<T>(s);                                             \
        return *this;                                                       \
    }                                                                       \
    template<typename U>                                                    \
    constexpr auto operator op(const Vector<U, 2>& v) noexcept -> Vector& { \
        x op static_cast<T>(v.x);                                           \
        y op static_cast<T>(v.y);                                           \
        return *this;                                                       \
    }

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector;

template<CArithmetic T>
struct Vector<T, 2> {
    static constexpr std::size_t size = 2;

    constexpr Vector() noexcept = default;

    explicit constexpr Vector(auto s) noexcept : Vector(s, s) {}

    constexpr Vector(auto _x, auto _y) noexcept : x{static_cast<T>(_x)}, y{static_cast<T>(_y)} {}

    template<typename U>
    explicit constexpr Vector(const Vector<U, 2>& v) noexcept : Vector(v.x, v.y) {}

    [[nodiscard]]
    constexpr auto operator-() const noexcept -> Vector {
        return {-x, -y};
    }

    VEC_OP(+)
    VEC_OP(-)
    VEC_OP(*)
    VEC_OP(/)

    template<typename U>
    constexpr auto operator=(const Vector<U, 2>& v) noexcept -> Vector& {
        x = v.x;
        y = v.y;
        return *this;
    }

    VEC_SELF_OP(+=)
    VEC_SELF_OP(-=)
    VEC_SELF_OP(*=)
    VEC_SELF_OP(/=)

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < 2 && "Index out of bound");
        return (&x)[i];
    }

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < 2 && "Index out of bound");
        return (&x)[i];
    }

    [[nodiscard]]
    constexpr bool operator==(const Vector&) const noexcept = default;

    [[nodiscard]]
    constexpr auto operator<=>(const Vector&) const noexcept = default;

    [[nodiscard]]
    constexpr auto length() const noexcept -> T {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]]
    constexpr auto normalize() const noexcept -> Vector
        requires(CFloatingPoint<T>)
    {
        return (*this) * (1 / length());
    }

    T x;
    T y;
};
}  // namespace xme::math

#undef VEC_OP
#undef VEC_SELF_OP
