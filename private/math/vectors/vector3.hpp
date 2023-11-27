#pragma once
#include <cassert>
#include <cmath>
#include <xme/math/geometric.hpp>

#define VEC_OP(op)                                                                             \
    template<typename U>                                                                       \
    constexpr auto operator op(U s) const noexcept -> Vector {                                 \
        return {x op s, y op s, z op s};                                                       \
    }                                                                                          \
    template<typename U>                                                                       \
    constexpr auto operator op(const Vector<U, 3>& v) const noexcept -> Vector {               \
        return {x op static_cast<T>(v.x), y op static_cast<T>(v.y), z op static_cast<T>(v.z)}; \
    }

#define VEC_SELF_OP(op)                                                     \
    template<typename U>                                                    \
    constexpr auto operator op(U s) noexcept -> Vector& {                   \
        x op s;                                                             \
        y op s;                                                             \
        z op s;                                                             \
        return *this;                                                       \
    }                                                                       \
    template<typename U>                                                    \
    constexpr auto operator op(const Vector<U, 3>& v) noexcept -> Vector& { \
        x op static_cast<T>(v.x);                                           \
        y op static_cast<T>(v.y);                                           \
        z op static_cast<T>(v.z);                                           \
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

    template<typename U1, typename U2, typename U3>
    constexpr Vector(U1 _x, U2 _y, U3 _z) noexcept :
      x{static_cast<T>(_x)}, y{static_cast<T>(_y)}, z{static_cast<T>(_z)} {}

    template<typename U1, typename U2>
    constexpr Vector(U1 s, const Vector<U2, 2>& v) noexcept : Vector(s, v[0], v[1]) {}

    template<typename U1, typename U2>
    constexpr Vector(const Vector<U1, 2>& v, U2 s) noexcept : Vector(v[0], v[1], s) {}

    template<typename U>
    explicit constexpr Vector(const Vector<U, 3>& v) noexcept : Vector(v.x, v.y, v.z) {}

    constexpr auto operator-() const noexcept -> Vector { return {-x, -y, -z}; }

    VEC_OP(+)
    VEC_OP(-)
    VEC_OP(*)
    VEC_OP(/)

    template<typename U>
    constexpr auto operator=(const Vector<U, 3>& v) noexcept -> Vector& {
        x = v.x;
        y = v.y;
        z = v.z;
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
