#pragma once
#include <xme/math/vector.hpp>

namespace xme {
template<typename T, std::size_t Size>
template<typename U>
constexpr auto Vector<T, Size>::dot(const Vector<U, Size>& v) const noexcept {
    decltype(m_Data[0] + v[0]) result = 0;
    for (std::size_t i = 0; i < Size; ++i)
        result += (m_Data[i] * v[i]);
    return result;
}

template<typename T, std::size_t Size>
template<typename U>
    requires(Size == 3)
constexpr auto Vector<T, Size>::cross(const Vector<U, 3>& v) const noexcept {
    return xme::Vector<decltype(m_Data[0] + v[0]), 3>{
        m_Data[1] * v[2] - m_Data[2] * v[1],
        m_Data[2] * v[0] - m_Data[0] * v[2],
        m_Data[0] * v[1] - m_Data[1] * v[0],
    };
}

template<typename T, std::size_t Size>
constexpr auto Vector<T, Size>::lenght() const noexcept {
    return std::sqrt(dot(*this));
}

template<typename T, std::size_t Size>
constexpr auto Vector<T, Size>::normalized() const noexcept {
    return *this * (1 / lenght());
}

template<typename T, std::size_t Size>
template<typename U>
constexpr auto Vector<T, Size>::reflect(const Vector<U, Size>& n) const noexcept {
    return *this - n * dot(n) * 2;
}

template<typename T, std::size_t Size>
template<typename U>
constexpr auto Vector<T, Size>::distance(const Vector<U, Size>& v) const noexcept {
    return (v - *this).lenght();
}

template<typename T, std::size_t Size>
template<typename U>
    requires(Size >= 3)
constexpr auto Vector<T, Size>::rotateX(U angle) const noexcept {
    Vector<T, Size> result{*this};
    const auto sin{std::sin(angle)};
    const auto cos(std::cos(angle));
    result[1] = m_Data[1] * cos - m_Data[2] * sin;
    result[2] = m_Data[1] * sin + m_Data[2] * cos;
    return result;
}

template<typename T, std::size_t Size>
template<typename U>
    requires(Size >= 3)
constexpr auto Vector<T, Size>::rotateY(U angle) const noexcept {
    Vector<T, Size> result{*this};
    const auto sin{std::sin(angle)};
    const auto cos(std::cos(angle));
    result[0] = m_Data[0] * cos + m_Data[2] * sin;
    result[2] = -m_Data[0] * sin + m_Data[2] * cos;
    return result;
}

template<typename T, std::size_t Size>
template<typename U>
    requires(Size >= 3)
constexpr auto Vector<T, Size>::rotateZ(U angle) const noexcept {
    Vector<T, Size> result{*this};
    const auto sin{std::sin(angle)};
    const auto cos(std::cos(angle));
    result[0] = m_Data[0] * cos - m_Data[1] * sin;
    result[1] = m_Data[0] * sin + m_Data[1] * cos;
    return result;
}
} // namespace xme