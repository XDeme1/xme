#pragma once
#include <xme/math/forward.hpp>

#define VECTOR_OP(op)                                                                    \
    template<typename T, typename U, std::size_t Size>                                   \
    constexpr auto operator op(const Vector<T, Size>& v1,                                \
                               const Vector<U, Size>& v2) noexcept {                     \
        Vector<decltype(v1[0] op v2[0]), Size> result;                                   \
        for (std::size_t i = 0; i < Size; ++i)                                           \
            result[i] = v1[i] op v2[i];                                                  \
        return result;                                                                   \
    }                                                                                    \
                                                                                         \
    template<typename T, std::size_t Size>                                               \
    constexpr auto operator op(const Vector<T, Size>& v, auto s) noexcept {              \
        Vector<decltype(v[0] op s), Size> result;                                        \
        for (std::size_t i = 0; i < Size; ++i)                                           \
            result[i] = v[i] op s;                                                       \
        return result;                                                                   \
    }                                                                                    \
                                                                                         \
    template<typename T, std::size_t Size>                                               \
    constexpr auto operator op(auto s, const Vector<T, Size>& v) noexcept {              \
        Vector<decltype(s op v[0]), Size> result;                                        \
        for (std::size_t i = 0; i < Size; ++i)                                           \
            result[i] = s op v[i];                                                       \
        return result;                                                                   \
    }

#define VECTOR_SELF_OP(op)                                                               \
    template<typename T, typename U, std::size_t Size>                                   \
    constexpr auto operator op(Vector<T, Size>& v1,                                      \
                               const Vector<U, Size>& v2) noexcept {                     \
        for (std::size_t i = 0; i < Size; ++i)                                           \
            v1[i] op v2[i];                                                              \
        return v1;                                                                       \
    }                                                                                    \
                                                                                         \
    template<typename T, std::size_t Size>                                               \
    constexpr auto operator op(Vector<T, Size>& v, auto s) noexcept {                    \
        for (std::size_t i = 0; i < Size; ++i)                                           \
            v[i] op s;                                                                   \
        return v;                                                                        \
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

template<typename T, typename U, std::size_t Size>
constexpr bool operator==(const Vector<T, Size>& v1, const Vector<U, Size>& v2) noexcept {
    for (auto i = 0; i < Size; ++i) {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

template<typename T, typename U, std::size_t Size>
constexpr bool operator!=(const Vector<T, Size>& v1, const Vector<U, Size>& v2) noexcept {
    return !xme::operator==(v1, v2);
}
} // namespace xme

#undef VECTOR_OP
#undef VECTOR_SELF_OP