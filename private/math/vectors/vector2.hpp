#pragma once
#include <cassert>
#include <cmath>
#include <type_traits>
#include <xme/setup.hpp>

#if __cpp_concepts
#include <xme/math/concepts.hpp>
#endif

#define VEC_OP(op)                                                               \
    template<typename U>                                                         \
    constexpr auto operator op(U s) const noexcept -> Vector {                   \
        return {x op s, y op s};                                                 \
    }                                                                            \
    template<typename U>                                                         \
    constexpr auto operator op(const Vector<U, 2>& v) const noexcept -> Vector { \
        return {x op static_cast<T>(v.x), y op static_cast<T>(v.y)};             \
    }

#define VEC_SELF_OP(op)                                                     \
    template<typename U>                                                    \
    constexpr auto operator op(U s) noexcept -> Vector& {                   \
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
template<XME_CONCEPT(CArithmetic, T), std::size_t Size>
struct Vector;

template<XME_CONCEPT(CArithmetic, T)>
struct Vector<T, 2> {
    static constexpr std::size_t size = 2;

    constexpr Vector() noexcept = default;

    template<typename U>
    explicit constexpr Vector(U s) noexcept : Vector(s, s) {}

    template<typename U1, typename U2>
    constexpr Vector(U1 _x, U2 _y) noexcept : x{static_cast<T>(_x)}, y{static_cast<T>(_y)} {}

    template<typename U>
    explicit constexpr Vector(const Vector<U, 2>& v) noexcept : Vector(v.x, v.y) {}

    constexpr auto operator-() const noexcept -> Vector { return {-x, -y}; }

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

    constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < 2 && "Index out of bound");
        return (&x)[i];
    }

    constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < 2 && "Index out of bound");
        return (&x)[i];
    }

#if defined(__cpp_impl_three_way_comparison)
    constexpr bool operator==(const Vector&) const noexcept = default;

    constexpr auto operator<=>(const Vector&) const noexcept = default;
#else
    constexpr bool operator==(const Vector& v) const noexcept {
        return (*this)[0] == v[0] && (*this)[1] == v[1];
    }

    constexpr bool operator!=(const Vector& v) const noexcept { return !operator==(v); }
#endif

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
