#pragma once
#include <xme/math/vector.hpp>

#define VECTOR_OP(op)                                                                    \
    template<typename T, std::size_t Size>                                               \
    template<typename U>                                                                 \
    constexpr auto Vector<T, Size>::operator op(const Vector<U, Size>& v)                \
        const noexcept {                                                                 \
        Vector<decltype(m_data[0] op v[0]), Size> result;                                \
        for (std::size_t i = 0; i < Size; ++i)                                           \
            result[i] = m_data[i] op v[i];                                               \
        return result;                                                                   \
    }                                                                                    \
    template<typename T, std::size_t Size>                                               \
    template<CArithmetic U>                                                              \
    constexpr auto Vector<T, Size>::operator op(U s) const noexcept {                    \
        Vector<decltype(m_data[0] op s), Size> result;                                   \
        for (std::size_t i = 0; i < Size; ++i)                                           \
            result[i] = m_data[i] op s;                                                  \
        return result;                                                                   \
    }

#define VECTOR_SELF_OP(op)                                                               \
    template<typename T, std::size_t Size>                                               \
    template<typename U>                                                                 \
    constexpr auto& Vector<T, Size>::operator op(const Vector<U, Size>& v) noexcept {    \
        for (std::size_t i = 0; i < Size; ++i)                                           \
            m_data[i] op v[i];                                                           \
        return *this;                                                                    \
    }                                                                                    \
    template<typename T, std::size_t Size>                                               \
    template<CArithmetic U>                                                              \
    constexpr auto& Vector<T, Size>::operator op(U s) noexcept {                         \
        for (std::size_t i = 0; i < Size; ++i)                                           \
            m_data[i] op s;                                                              \
        return *this;                                                                    \
    }

namespace xme {
template<typename T, std::size_t Size>
constexpr auto Vector<T, Size>::operator+() const noexcept {
    return *this;
}

template<typename T, std::size_t Size>
constexpr auto Vector<T, Size>::operator-() const noexcept {
    Vector result;
    for (std::size_t i = 0; i < Size; ++i)
        result[i] = -m_data[i];
    return result;
}

VECTOR_OP(+)
VECTOR_OP(-)
VECTOR_OP(*)
VECTOR_OP(/)

template<typename T, std::size_t Size>
template<typename U>
constexpr auto& Vector<T, Size>::operator=(const Vector<U, Size>& v) noexcept {
    for (std::size_t i = 0; i < Size; ++i)
        this[i] = static_cast<T>(v[i]);
    return *this;
}

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