#pragma once
#include <xme/math/concepts.hpp>
#include <cassert>
#include <cmath>

#define VEC_OP(op)                                                               \
    constexpr auto operator op(auto s) const noexcept -> Vector {                \
        return {x op s, y op s};                                                 \
    }                                                                            \
    template<typename U>                                                         \
    constexpr auto operator op(const Vector<U, 2>& v) const noexcept -> Vector { \
        return {x op static_cast<T>(v.x), y op static_cast<T>(v.y)};             \
    }

#define VEC_SELF_OP(op)                                                     \
    constexpr auto operator op(auto s) noexcept -> Vector& {                \
        x op s;                                                             \
        y op s;                                                             \
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

    constexpr auto operator-() const noexcept -> Vector { return {-x, -y}; }

    VEC_OP(+);
    VEC_OP(-);
    VEC_OP(*);
    VEC_OP(/);

    template<typename U>
    constexpr auto operator=(const Vector<U, 2>& v) noexcept -> Vector& {
        x = v.x;
        y = v.y;
        return *this;
    }

    VEC_SELF_OP(+=);
    VEC_SELF_OP(-=);
    VEC_SELF_OP(*=);
    VEC_SELF_OP(/=);

    constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < 2 && "Index out of bound");
        return (&x)[i];
    }

    constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < 2 && "Index out of bound");
        return (&x)[i];
    }

    constexpr bool operator==(const Vector&) const noexcept = default;

    constexpr auto operator<=>(const Vector&) const noexcept = default;

    constexpr auto dot(const Vector& v) const noexcept -> T { return {x * v.x + y * v.y}; }

    constexpr auto length() const noexcept { return std::sqrt(dot(*this)); }

    constexpr auto normalized() const noexcept -> Vector { return *this * (1 / length()); }

    constexpr auto reflect(const Vector& n) const noexcept -> Vector {
        return *this - n * dot(n) * 2;
    }

    constexpr auto distance(const Vector& v) const noexcept { return (v - *this).length(); }

    T x{};
    T y{};
};
}  // namespace xme::math

#undef VEC_OP
#undef VEC_SELF_OP
