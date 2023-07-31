#pragma once
#include <cstdint>
#include "../forward.hpp"

#define VECTOR_OP(op) \
    template<typename T, typename U, std::size_t Size> \
    constexpr auto operator op (const Vector<T, Size>& v1, const Vector<U, Size>& v2) noexcept { \
        Vector<decltype(v1[0] op v2[0]), Size> result; \
        for (std::size_t i = 0; i < Size; ++i) { \
            result[i] = v1[i] op v2[i]; \
        } \
        return result; \
    } \
    \
    template<typename T, std::size_t Size> \
    constexpr auto operator op (const Vector<T, Size>& v, auto s) noexcept {\
        return xme::operator op (v, xme::Vector<decltype(s), Size>(s)); \
    } \
    \
    template<typename T, std::size_t Size> \
    constexpr auto operator op (auto s, const Vector<T, Size>& v) noexcept { \
        return xme::operator op (Vector<decltype(s), Size>(s), v); \
    }

#define VECTOR_SELF_OP(op) \
    template<typename T, typename U, std::size_t Size> \
    constexpr auto operator op(Vector<T, Size>& v1, const Vector<U, Size>& v2) noexcept { \
        for (std::size_t i = 0; i < Size; ++i) { \
            v1[i] op v2[i]; \
        } \
        return v1; \
    } \
    \
    template<typename T, std::size_t Size> \
    constexpr auto operator op(Vector<T, Size>& v, auto s) noexcept { \
        for(std::size_t i = 0; i < Size; ++i) { \
            v[i] op s; \
        } \
        return v; \
    }

namespace xme {
    VECTOR_OP(+)
    VECTOR_OP(-)
    VECTOR_OP(*)
    VECTOR_OP(/)

    VECTOR_SELF_OP(+=)
    VECTOR_SELF_OP(-=)
    VECTOR_SELF_OP(*=)
    VECTOR_SELF_OP(/=)
}

#undef VECTOR_OP
#undef VECTOR_SELF_OP