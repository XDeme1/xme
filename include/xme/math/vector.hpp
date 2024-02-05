#pragma once
#include <cassert>
#include <array>
#include <cmath>
#include <xme/setup.hpp>
#include <xme/core/concepts/arithmetic.hpp>

#define VEC_OP(op)                                                                  \
    [[nodiscard]]                                                                   \
    constexpr auto operator op(auto s) const noexcept -> Vector {                   \
        Vector result{};                                                            \
        for(std::size_t i = 0; i < Size; ++i)                                       \
            result[i] = (*this)[i] op static_cast<T>(s);                            \
        return result;                                                              \
    }                                                                               \
    template<typename U>                                                            \
    [[nodiscard]]                                                                   \
    constexpr auto operator op(const Vector<U, Size>& v) const noexcept -> Vector { \
        Vector result{};                                                            \
        for(std::size_t i = 0; i < Size; ++i)                                       \
            result[i] = (*this)[i] op static_cast<T>(v[i]);                         \
        return result;                                                              \
    }

#define VEC_SELF_OP(op)                                                        \
    constexpr auto operator op(auto s) noexcept -> Vector& {                   \
        for(std::size_t i = 0; i < Size; ++i)                                  \
            (*this)[i] op static_cast<T>(s);                                   \
        return *this;                                                          \
    }                                                                          \
    template<typename U>                                                       \
    constexpr auto operator op(const Vector<U, Size>& v) noexcept -> Vector& { \
        for(std::size_t i = 0; i < Size; ++i)                                  \
            (*this)[i] op static_cast<T>(v[i]);                                \
        return *this;                                                          \
    }

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector {
public:
    static constexpr std::size_t size = Size;

    constexpr Vector() noexcept = default;

    template<CArithmetic U>
    constexpr Vector(U s) noexcept {
        m_data.fill(s);
    }

    template<typename... Args>
    constexpr Vector(auto s1, auto s2, Args... args) noexcept :
      m_data({static_cast<T>(s1), static_cast<T>(s2), static_cast<T>(args)...}) {}

    template<typename U>
    constexpr Vector(const Vector<U, Size>& v) noexcept {
        for(std::size_t i = 0; i < Size; ++i)
            m_data[i] = static_cast<T>(v[i]);
    }

    [[nodiscard]]
    constexpr auto operator-() const noexcept -> Vector {
        Vector result;
        for(std::size_t i = 0; i < Size; ++i)
            result[i] = -m_data[i];
        return result;
    }

    VEC_OP(+)
    VEC_OP(-)
    VEC_OP(*)
    VEC_OP(/)

    template<typename U>
    constexpr auto operator=(const Vector<U, Size>& v) noexcept -> Vector& {
        for(std::size_t i = 0; i < Size; ++i)
            m_data[i] = static_cast<T>(v[i]);
        return *this;
    }

    VEC_SELF_OP(+=)
    VEC_SELF_OP(-=)
    VEC_SELF_OP(*=)
    VEC_SELF_OP(/=)

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < Size && "Index out of bound");
        return m_data[i];
    }

    [[nodiscard]]
    constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < Size && "Index out of bound");
        return m_data[i];
    }

    [[nodiscard]]
    constexpr bool operator==(const Vector&) const noexcept = default;

    [[nodiscard]]
    constexpr auto operator<=>(const Vector&) const noexcept = default;

    [[nodiscard]]
    constexpr auto length() const noexcept -> T {
        T result{0};
        for(std::size_t i = 0; i < Size; ++i)
            result += (*this)[i] * (*this)[i];
        return std::sqrt(result);
    }

    [[nodiscard]]
    constexpr auto normalize() const noexcept -> Vector
        requires(CFloatingPoint<T>)
    {
        return (*this) * (1 / length());
    }

    std::array<T, Size> m_data;
};

template<typename T, typename... Args>
Vector(T, Args...) -> Vector<std::common_type_t<T, Args...>, sizeof...(Args) + 1>;
}  // namespace xme::math

#undef VEC_OP
#undef VEC_SELF_OP

#include "../../../private/math/vectors/vector2.hpp"
#include "../../../private/math/vectors/vector3.hpp"
#include "../../../private/math/vectors/vector4.hpp"
#include "vectors/functions.hpp"
#include "vectors/geometry.hpp"