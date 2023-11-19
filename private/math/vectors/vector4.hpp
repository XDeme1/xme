#pragma once
#include <cassert>
#include <cmath>
#include <xme/math/concepts.hpp>

#define VEC_OP(op)                                                               \
    constexpr auto operator op(auto s) const noexcept -> Vector {                \
        return {x op s, y op s, z op s, w op s};                                 \
    }                                                                            \
    template<typename U>                                                         \
    constexpr auto operator op(const Vector<U, 4>& v) const noexcept -> Vector { \
        return {                                                                 \
            x op static_cast<T>(v.x),                                            \
            y op static_cast<T>(v.y),                                            \
            z op static_cast<T>(v.z),                                            \
            w op static_cast<T>(v.w),                                            \
        };                                                                       \
    }

#define VEC_SELF_OP(op)                                                     \
    constexpr auto operator op(auto s) noexcept -> Vector& {                \
        x op s;                                                             \
        y op s;                                                             \
        z op s;                                                             \
        w op s;                                                             \
        return *this;                                                       \
    }                                                                       \
    template<typename U>                                                    \
    constexpr auto operator op(const Vector<U, 4>& v) noexcept -> Vector& { \
        x op static_cast<T>(v.x);                                           \
        y op static_cast<T>(v.y);                                           \
        z op static_cast<T>(v.z);                                           \
        w op static_cast<T>(v.w);                                           \
        return *this;                                                       \
    }

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector;

template<CArithmetic T>
struct Vector<T, 4> {
    static constexpr std::size_t size = 4;

    constexpr Vector() noexcept = default;

    explicit constexpr Vector(auto s) noexcept : Vector(s, s, s, s) {}

    constexpr Vector(auto _x, auto _y, auto _z, auto _w) noexcept :
      x{static_cast<T>(_x)}, y{static_cast<T>(_y)}, z{static_cast<T>(_z)}, w{static_cast<T>(_w)} {}

    template<typename U>
    constexpr Vector(auto s1, auto s2, const Vector<U, 2>& v) noexcept :
      Vector(s1, s2, v[0], v[1]) {}

    template<typename U>
    constexpr Vector(auto s1, const Vector<U, 2>& v, auto s2) noexcept :
      Vector(s1, v[0], v[1], s2) {}

    template<typename U>
    constexpr Vector(const Vector<U, 2>& v, auto s1, auto s2) noexcept :
      Vector(v[0], v[1], s1, s2) {}

    template<typename U1, typename U2>
    constexpr Vector(const Vector<U1, 2>& v1, const Vector<U2, 2>& v2) noexcept :
      Vector(v1[0], v1[1], v2[0], v2[1]) {}

    template<typename U>
    constexpr Vector(auto s, const Vector<U, 3>& v) noexcept : Vector(s, v[0], v[1], v[2]) {}

    template<typename U>
    constexpr Vector(const Vector<U, 3>& v, auto s) noexcept : Vector(v[0], v[1], v[2], s) {}

    template<typename U>
    explicit constexpr Vector(const Vector<U, 4>& v) noexcept : Vector(v.x, v.y, v.z, v.w) {}

    constexpr auto operator-() const noexcept -> Vector { return {-x, -y, -z, -w}; }

    VEC_OP(+)
    VEC_OP(-)
    VEC_OP(*)
    VEC_OP(/)

    template<typename U>
    constexpr auto operator=(const Vector<U, 4>& v) noexcept -> Vector& {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }

    VEC_SELF_OP(+=)
    VEC_SELF_OP(-=)
    VEC_SELF_OP(*=)
    VEC_SELF_OP(/=)

    constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < 4 && "Index out of bound");
        return (&x)[i];
    }

    constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < 4 && "Index out of bound");
        return (&x)[i];
    }

    constexpr bool operator==(const Vector&) const noexcept = default;

    constexpr auto operator<=>(const Vector&) const noexcept = default;

    constexpr auto dot(const Vector& v) const noexcept -> T {
        return {x * v.x + y * v.y + z * v.z + w * v.w};
    }

    constexpr auto length() const noexcept { return std::sqrt(dot(*this)); }

    constexpr auto normalized() const noexcept -> Vector { return *this * (1 / length()); }

    constexpr auto reflect(const Vector& n) const noexcept -> Vector {
        return *this - n * dot(n) * 2;
    }

    constexpr auto distance(const Vector& v) const noexcept { return (v - *this).length(); }

    T x{};
    T y{};
    T z{};
    T w{};
};
}  // namespace xme::math

#undef VEC_OP
#undef VEC_SELF_OP
