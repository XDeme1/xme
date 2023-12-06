#pragma once
#include <cassert>
#include <array>
#include <type_traits>
#include "geometric.hpp"

#define VEC_OP(op)                                                                             \
    XME_INLINE constexpr auto operator op(auto s) const noexcept -> Vector {                   \
        Vector result{};                                                                       \
        for(std::size_t i = 0; i < Size; ++i)                                                  \
            result[i] = ((*this)[i] op static_cast<T>(s));                                     \
        return result;                                                                         \
    }                                                                                          \
    template<typename U>                                                                       \
    XME_INLINE constexpr auto operator op(const Vector<U, Size>& v) const noexcept -> Vector { \
        Vector result{};                                                                       \
        for(std::size_t i = 0; i < Size; ++i)                                                  \
            result[i] = ((*this)[i] op static_cast<T>(v[i]));                                  \
        return result;                                                                         \
    }

#define VEC_SELF_OP(op)                                                                   \
    XME_INLINE constexpr auto operator op(auto s) noexcept -> Vector& {                   \
        for(std::size_t i = 0; i < Size; ++i)                                             \
            (*this)[i] op static_cast<T>(s);                                              \
        return *this;                                                                     \
    }                                                                                     \
    template<typename U>                                                                  \
    XME_INLINE constexpr auto operator op(const Vector<U, Size>& v) noexcept -> Vector& { \
        for(std::size_t i = 0; i < Size; ++i)                                             \
            (*this)[i] op static_cast<T>(v[i]);                                           \
        return *this;                                                                     \
    }

namespace xme::math {
template<CArithmetic T, std::size_t Size>
struct Vector {
public:
    static constexpr std::size_t size = Size;

    XME_INLINE constexpr Vector() noexcept = default;

    XME_INLINE constexpr Vector(auto s) noexcept { m_data.fill(s); }

    template<CArithmetic... Args>
    XME_INLINE constexpr Vector(Args... args) noexcept : m_data({static_cast<T>(args)...}) {
        static_assert(sizeof...(Args) == Size);
    }

    template<typename U>
    XME_INLINE constexpr Vector(const Vector<U, Size>& v) noexcept {
        for(std::size_t i = 0; i < Size; ++i)
            m_data[i] = static_cast<T>(v[i]);
    }

    XME_INLINE constexpr auto operator-() const noexcept -> Vector {
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
    XME_INLINE constexpr auto operator=(const Vector<U, Size>& v) noexcept -> Vector& {
        for(std::size_t i = 0; i < Size; ++i)
            m_data[i] = static_cast<T>(v[i]);
        return *this;
    }

    VEC_SELF_OP(+=)
    VEC_SELF_OP(-=)
    VEC_SELF_OP(*=)
    VEC_SELF_OP(/=)

    XME_INLINE constexpr auto operator[](std::size_t i) noexcept -> T& {
        assert(i < Size && "Index out of bound");
        return m_data[i];
    }

    XME_INLINE constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        assert(i < Size && "Index out of bound");
        return m_data[i];
    }

    [[nodiscard]]
    XME_INLINE constexpr bool
    operator==(const Vector&) const noexcept = default;

    [[nodiscard]]
    XME_INLINE constexpr auto
    operator<=>(const Vector&) const noexcept = default;

    [[nodiscard]]
    XME_INLINE constexpr auto length() const noexcept -> T {
        return math::length(*this);
    }

    [[nodiscard]]
    XME_INLINE constexpr auto normalize() const noexcept -> Vector {
        return math::normalize(*this);
    }

private:
    std::array<T, Size> m_data{};
};

template<typename T, typename... Args>
Vector(T, Args...) -> Vector<std::common_type_t<T, Args...>, sizeof...(Args) + 1>;

template<std::size_t I, typename T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto get(Vector<T, Size>& v) noexcept -> decltype(auto) {
    return v[I];
}

template<std::size_t I, typename T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto get(const Vector<T, Size>& v) noexcept -> decltype(auto) {
    return v[I];
}

template<typename T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto begin(Vector<T, Size>& v) noexcept -> T* {
    return std::addressof(v[0]);
}

template<typename T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto begin(const Vector<T, Size>& v) noexcept -> const T* {
    return std::addressof(v[0]);
}

template<typename T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto end(Vector<T, Size>& v) noexcept -> T* {
    return std::addressof(v[Size - 1]) + 1;
}

template<typename T, std::size_t Size>
[[nodiscard]]
XME_INLINE constexpr auto end(const Vector<T, Size>& v) noexcept -> const T* {
    return std::addressof(v[Size - 1]) + 1;
}
}  // namespace xme::math

namespace std {
template<typename T, std::size_t Size>
struct tuple_size<xme::math::Vector<T, Size>> : integral_constant<std::size_t, Size> {};

template<std::size_t I, typename T, std::size_t Size>
struct tuple_element<I, xme::math::Vector<T, Size>> {
    using type = T;
};
}  // namespace std

#undef VEC_OP
#undef VEC_SELF_OP

#include "../../../private/math/vectors/vector2.hpp"
#include "../../../private/math/vectors/vector3.hpp"
#include "../../../private/math/vectors/vector4.hpp"
