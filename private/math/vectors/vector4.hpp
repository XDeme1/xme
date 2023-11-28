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
            w op static_cast<T>(s),                                              \
        };                                                                       \
    }                                                                            \
    template<typename U>                                                         \
    constexpr auto operator op(const Vector<U, 4>& v) const noexcept -> Vector { \
        return {                                                                 \
            x op static_cast<T>(v[0]),                                           \
            y op static_cast<T>(v[1]),                                           \
            z op static_cast<T>(v[2]),                                           \
            w op static_cast<T>(v[3]),                                           \
        };                                                                       \
    }

#define VEC_SELF_OP(op)                                                     \
    template<typename U>                                                    \
    constexpr auto operator op(U s) noexcept -> Vector& {                   \
        x op s;                                                             \
        y op s;                                                             \
        z op s;                                                             \
        w op s;                                                             \
        return *this;                                                       \
    }                                                                       \
    template<typename U>                                                    \
    constexpr auto operator op(const Vector<U, 4>& v) noexcept -> Vector& { \
        x op static_cast<T>(v[0]);                                          \
        y op static_cast<T>(v[1]);                                          \
        z op static_cast<T>(v[2]);                                          \
        w op static_cast<T>(v[3]);                                          \
        return *this;                                                       \
    }

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector;

template<CArithmetic T>
struct Vector<T, 4> {
    static constexpr std::size_t size = 4;

    constexpr Vector() noexcept = default;

    template<typename U>
    explicit constexpr Vector(U s) noexcept : Vector(s, s, s, s) {}

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
        x = static_cast<T>(v[0]);
        y = static_cast<T>(v[1]);
        z = static_cast<T>(v[2]);
        w = static_cast<T>(v[3]);
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

    constexpr auto length() const noexcept { return math::length(*this); }

    constexpr auto normalize() const noexcept -> Vector { return math::normalize(*this); }

    T x{};
    T y{};
    T z{};
    T w{};
};
}  // namespace xme::math

#undef VEC_OP
#undef VEC_SELF_OP
