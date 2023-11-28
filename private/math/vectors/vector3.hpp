#pragma once
#include <cassert>
#include <cmath>
#include <xme/math/geometric.hpp>

#define VEC_OP(op)                                                               \
    template<typename U>                                                         \
    constexpr auto operator op(U s) const noexcept -> Vector {                   \
        return {                                                                 \
            x op static_cast<T>(s),                                              \
            y op static_cast<T>(s),                                              \
            z op static_cast<T>(s),                                              \
        };                                                                       \
    }                                                                            \
    template<typename U>                                                         \
    constexpr auto operator op(const Vector<U, 3>& v) const noexcept -> Vector { \
        return {                                                                 \
            x op static_cast<T>(v[0]),                                           \
            y op static_cast<T>(v[1]),                                           \
            z op static_cast<T>(v[2]),                                           \
        };                                                                       \
    }

#define VEC_SELF_OP(op)                                                     \
    template<typename U>                                                    \
    constexpr auto operator op(U s) noexcept -> Vector& {                   \
        x op static_cast<T>(s);                                             \
        y op static_cast<T>(s);                                             \
        z op static_cast<T>(s);                                             \
        return *this;                                                       \
    }                                                                       \
    template<typename U>                                                    \
    constexpr auto operator op(const Vector<U, 3>& v) noexcept -> Vector& { \
        x op static_cast<T>(v[0]);                                          \
        y op static_cast<T>(v[1]);                                          \
        z op static_cast<T>(v[2]);                                          \
        return *this;                                                       \
    }

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector;

template<CArithmetic T>
struct Vector<T, 3> {
    static constexpr std::size_t size = 3;

    constexpr Vector() noexcept = default;

    template<typename U>
    explicit constexpr Vector(U s) noexcept : Vector(s, s, s) {}

    constexpr Vector(auto _x, auto _y, auto _z) noexcept :
      x{static_cast<T>(_x)}, y{static_cast<T>(_y)}, z{static_cast<T>(_z)} {}

    template<typename U>
    constexpr Vector(auto s, const Vector<U, 2>& v) noexcept : Vector(s, v[0], v[1]) {}

    template<typename U>
    constexpr Vector(const Vector<U, 2>& v, auto s) noexcept : Vector(v[0], v[1], s) {}

    template<typename U>
    explicit constexpr Vector(const Vector<U, 3>& v) noexcept : Vector(v[0], v[1], v[2]) {}

    constexpr auto operator-() const noexcept -> Vector { return {-x, -y, -z}; }

    VEC_OP(+)
    VEC_OP(-)
    VEC_OP(*)
    VEC_OP(/)

    template<typename U>
    constexpr auto operator=(const Vector<U, 3>& v) noexcept -> Vector& {
        x = static_cast<T>(v[0]);
        y = static_cast<T>(v[1]);
        z = static_cast<T>(v[2]);
        return *this;
    }

    VEC_SELF_OP(+=)
    VEC_SELF_OP(-=)
    VEC_SELF_OP(*=)
    VEC_SELF_OP(/=)

    constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < 3 && "Index out of bound");
        return (&x)[i];
    }

    constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < 3 && "Index out of bound");
        return (&x)[i];
    }

    constexpr bool operator==(const Vector&) const noexcept = default;

    constexpr auto operator<=>(const Vector&) const noexcept = default;

    constexpr auto length() const noexcept -> T { return math::length(*this); }

    constexpr auto normalize() const noexcept -> Vector { return math::normalize(*this); }

    T x{};
    T y{};
    T z{};
};
}  // namespace xme::math

#undef VEC_OP
#undef VEC_SELF_OP
