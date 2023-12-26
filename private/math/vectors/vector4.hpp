#pragma once
#include <cassert>
#include <cmath>
#include <xme/math/geometric.hpp>

#define VEC_OP(op)                                                               \
    [[nodiscard]]                                                                \
    constexpr auto operator op(auto s) const noexcept -> Vector {                \
        return {                                                                 \
            x op static_cast<T>(s),                                              \
            y op static_cast<T>(s),                                              \
            z op static_cast<T>(s),                                              \
            w op static_cast<T>(s),                                              \
        };                                                                       \
    }                                                                            \
    template<typename U>                                                         \
    [[nodiscard]]                                                                \
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
        x op static_cast<T>(s);                                             \
        y op static_cast<T>(s);                                             \
        z op static_cast<T>(s);                                             \
        w op static_cast<T>(s);                                             \
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
template<arithmetic_c T, std::size_t Size>
struct Vector;

template<arithmetic_c T>
struct Vector<T, 4> {
    static constexpr std::size_t size = 4;

    constexpr Vector() noexcept = default;

    explicit constexpr Vector(auto s) noexcept : Vector(s, s, s, s) {}

    constexpr Vector(auto _x, auto _y, auto _z, auto _w) noexcept :
      x{static_cast<T>(_x)}, y{static_cast<T>(_y)}, z{static_cast<T>(_z)}, w{static_cast<T>(_w)} {}

    template<typename U>
    constexpr Vector(auto s1, auto s2, const Vector<U, 2>& v) noexcept : Vector(s1, s2, v.x, v.y) {}

    template<typename U>
    constexpr Vector(auto s1, const Vector<U, 2>& v, auto s2) noexcept : Vector(s1, v.x, v.y, s2) {}

    template<typename U>
    constexpr Vector(const Vector<U, 2>& v, auto s1, auto s2) noexcept : Vector(v.x, v.y, s1, s2) {}

    template<typename U1, typename U2>
    constexpr Vector(const Vector<U1, 2>& v1, const Vector<U2, 2>& v2) noexcept :
      Vector(v1.x, v1.y, v2.x, v2.y) {}

    template<typename U>
    constexpr Vector(auto s, const Vector<U, 3>& v) noexcept : Vector(s, v.x, v.y, v.z) {}

    template<typename U>
    constexpr Vector(const Vector<U, 3>& v, auto s) noexcept : Vector(v.x, v.y, v.z, s) {}

    template<typename U>
    explicit constexpr Vector(const Vector<U, 4>& v) noexcept : Vector(v.x, v.y, v.z, v.w) {}

    [[nodiscard]]
    constexpr auto operator-() const noexcept -> Vector {
        return {-x, -y, -z, -w};
    }

    VEC_OP(+)
    VEC_OP(-)
    VEC_OP(*)
    VEC_OP(/)

    template<typename U>
    constexpr auto operator=(const Vector<U, 4>& v) noexcept -> Vector& {
        x = static_cast<T>(v.x);
        y = static_cast<T>(v.y);
        z = static_cast<T>(v.z);
        w = static_cast<T>(v.w);
        return *this;
    }

    VEC_SELF_OP(+=)
    VEC_SELF_OP(-=)
    VEC_SELF_OP(*=)
    VEC_SELF_OP(/=)

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < 4 && "Index out of bound");
        return (&x)[i];
    }

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < 4 && "Index out of bound");
        return (&x)[i];
    }

    [[nodiscard]]
    constexpr bool operator==(const Vector&) const noexcept = default;

    [[nodiscard]]
    constexpr auto operator<=>(const Vector&) const noexcept = default;

    [[nodiscard]]
    constexpr auto length() const noexcept {
        return math::length(*this);
    }

    [[nodiscard]]
    constexpr auto normalize() const noexcept -> Vector {
        return math::normalize(*this);
    }

    T x;
    T y;
    T z;
    T w;
};
}  // namespace xme::math

#undef VEC_OP
#undef VEC_SELF_OP
