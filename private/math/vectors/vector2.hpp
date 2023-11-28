#pragma once
#include <cassert>
#include <cmath>
#include <xme/math/geometric.hpp>

#define VEC_OP(op)                                                                          \
    XME_INLINE constexpr auto operator op(auto s) const noexcept -> Vector {                \
        return {                                                                            \
            x op static_cast<T>(s),                                                         \
            y op static_cast<T>(s),                                                         \
        };                                                                                  \
    }                                                                                       \
    template<typename U>                                                                    \
    XME_INLINE constexpr auto operator op(const Vector<U, 2>& v) const noexcept -> Vector { \
        return {                                                                            \
            x op static_cast<T>(v.x),                                                       \
            y op static_cast<T>(v.y),                                                       \
        };                                                                                  \
    }

#define VEC_SELF_OP(op)                                                                \
    XME_INLINE constexpr auto operator op(auto s) noexcept -> Vector& {                \
        x op static_cast<T>(s);                                                        \
        y op static_cast<T>(s);                                                        \
        return *this;                                                                  \
    }                                                                                  \
    template<typename U>                                                               \
    XME_INLINE constexpr auto operator op(const Vector<U, 2>& v) noexcept -> Vector& { \
        x op static_cast<T>(v.x);                                                      \
        y op static_cast<T>(v.y);                                                      \
        return *this;                                                                  \
    }

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector;

template<CArithmetic T>
struct Vector<T, 2> {
    static constexpr std::size_t size = 2;

    XME_INLINE constexpr Vector() noexcept = default;

    XME_INLINE explicit constexpr Vector(auto s) noexcept : Vector(s, s) {}

    XME_INLINE constexpr Vector(auto _x, auto _y) noexcept :
      x{static_cast<T>(_x)}, y{static_cast<T>(_y)} {}

    template<typename U>
    XME_INLINE explicit constexpr Vector(const Vector<U, 2>& v) noexcept : Vector(v.x, v.y) {}

    XME_INLINE constexpr auto operator-() const noexcept -> Vector { return {-x, -y}; }

    VEC_OP(+)
    VEC_OP(-)
    VEC_OP(*)
    VEC_OP(/)

    template<typename U>
    XME_INLINE constexpr auto operator=(const Vector<U, 2>& v) noexcept -> Vector& {
        x = v.x;
        y = v.y;
        return *this;
    }

    VEC_SELF_OP(+=)
    VEC_SELF_OP(-=)
    VEC_SELF_OP(*=)
    VEC_SELF_OP(/=)

    XME_INLINE constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < 2 && "Index out of bound");
        return (&x)[i];
    }

    XME_INLINE constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < 2 && "Index out of bound");
        return (&x)[i];
    }

    XME_INLINE constexpr bool operator==(const Vector&) const noexcept = default;

    XME_INLINE constexpr auto operator<=>(const Vector&) const noexcept = default;

    XME_INLINE constexpr auto length() const noexcept { return math::length(*this); }

    XME_INLINE constexpr auto normalize() const noexcept -> Vector {
        return math::normalize(*this);
    }

    T x{};
    T y{};
};
}  // namespace xme::math

#undef VEC_OP
#undef VEC_SELF_OP
