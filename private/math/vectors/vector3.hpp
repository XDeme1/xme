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
        };                                                                       \
    }                                                                            \
    template<typename U>                                                         \
    [[nodiscard]]                                                                \
    constexpr auto operator op(const Vector<U, 3>& v) const noexcept -> Vector { \
        return {                                                                 \
            x op static_cast<T>(v.x),                                            \
            y op static_cast<T>(v.y),                                            \
            z op static_cast<T>(v.z),                                            \
        };                                                                       \
    }

#define VEC_SELF_OP(op)                                                     \
    constexpr auto operator op(auto s) noexcept -> Vector& {                \
        x op static_cast<T>(s);                                             \
        y op static_cast<T>(s);                                             \
        z op static_cast<T>(s);                                             \
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

    constexpr Vector(auto _x, auto _y, auto _z) noexcept :
      x{static_cast<T>(_x)}, y{static_cast<T>(_y)}, z{static_cast<T>(_z)} {}

    template<typename U>
    constexpr Vector(auto s, const Vector<U, 2>& v) noexcept : Vector(s, v.x, v.y) {}

    template<typename U>
    constexpr Vector(const Vector<U, 2>& v, auto s) noexcept : Vector(v.x, v.y, s) {}

    template<typename U>
    explicit constexpr Vector(const Vector<U, 3>& v) noexcept : Vector(v.x, v.y, v.z) {}

    [[nodiscard]]
    constexpr auto operator-() const noexcept -> Vector {
        return {-x, -y, -z};
    }

    VEC_OP(+)
    VEC_OP(-)
    VEC_OP(*)
    VEC_OP(/)

    template<typename U>
    constexpr auto operator=(const Vector<U, 3>& v) noexcept -> Vector& {
        x = static_cast<T>(v.x);
        y = static_cast<T>(v.y);
        z = static_cast<T>(v.z);
        return *this;
    }

    VEC_SELF_OP(+=)
    VEC_SELF_OP(-=)
    VEC_SELF_OP(*=)
    VEC_SELF_OP(/=)

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < 3 && "Index out of bound");
        return (&x)[i];
    }

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < 3 && "Index out of bound");
        return (&x)[i];
    }

    [[nodiscard]]
    constexpr bool operator==(const Vector&) const noexcept = default;

    [[nodiscard]]
    constexpr auto operator<=>(const Vector&) const noexcept = default;

    [[nodiscard]]
    constexpr auto length() const noexcept -> T {
        return math::length(*this);
    }

    [[nodiscard]]
    constexpr auto normalize() const noexcept -> Vector {
        return math::normalize(*this);
    }

    T x;
    T y;
    T z;
};
}  // namespace xme::math

#undef VEC_OP
#undef VEC_SELF_OP
