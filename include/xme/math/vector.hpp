#pragma once
#include <array>
#include <cmath>
#include <type_traits>
#include "concepts.hpp"

namespace xme {

template<typename T, std::size_t Size>
struct Vector {
public:
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

    static constexpr std::size_t size = Size;

    constexpr Vector() noexcept = default;
    constexpr Vector(const Vector&) noexcept = default;
    constexpr Vector(Vector&&) noexcept = default;

    constexpr auto operator=(const Vector&) noexcept -> Vector& = default;
    constexpr auto operator=(Vector&&) noexcept -> Vector& = default;

    template<CArithmetic U>
    constexpr Vector(U s) noexcept { m_Data.fill(s); }

    template<CArithmetic... Args>
        requires(sizeof...(Args) == Size)
    constexpr Vector(Args... args) noexcept : m_Data({static_cast<T>(args)...}) {}

    // Vector3 Conversion constructors
    template<typename U>
        requires(Size == 3)
    constexpr Vector(auto s, const Vector<U, 2>& v) noexcept : Vector(s, v[0], v[1]) {}

    template<typename U>
        requires(Size == 3)
    constexpr Vector(const Vector<U, 2>& v, auto s) noexcept : Vector(v[0], v[1], s) {}

    // Vector4 Conversion constructors
    template<typename U>
        requires(Size == 4)
    constexpr Vector(auto s1, auto s2, const Vector<U, 2>& v) noexcept
        : Vector(s1, s2, v[0], v[1]) {}

    template<typename U>
        requires(Size == 4)
    constexpr Vector(auto s1, const Vector<U, 2>& v, auto s2) noexcept
        : Vector(s1, v[0], v[1], s2) {}

    template<typename U>
        requires(Size == 4)
    constexpr Vector(const Vector<U, 2>& v, auto s1, auto s2) noexcept
        : Vector(v[0], v[1], s1, s2) {}

    template<typename U1, typename U2>
        requires(Size == 4)
    constexpr Vector(const Vector<U1, 2>& v1, const Vector<U2, 2>& v2) noexcept
        : Vector(v1[0], v1[1], v2[0], v2[1]) {}

    template<typename U>
        requires(Size == 4)
    constexpr Vector(auto s, const Vector<U, 3>& v) noexcept
        : Vector(s, v[0], v[1], v[2]) {}

    template<typename U>
        requires(Size == 4)
    constexpr Vector(const Vector<U, 3>& v, auto s) noexcept
        : Vector(v[0], v[1], v[2], s) {}

    template<typename U>
    constexpr Vector(const Vector<U, Size>& v) noexcept {
        for (std::size_t i = 0; i < Size; ++i)
            m_Data[i] = static_cast<T>(v[i]);
    }

    template<typename U>
    constexpr auto& operator=(const Vector<U, Size>& v) noexcept {
        for (std::size_t i = 0; i < Size; ++i)
            m_Data[i] = static_cast<T>(v[i]);
        return *this;
    }

    constexpr auto& operator[](std::size_t i) noexcept { return m_Data[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return m_Data[i]; }

    //Useful for ranges algorithms
    constexpr auto* begin() noexcept { return &m_Data[0]; }
    constexpr auto* end() noexcept { return &m_Data[Size]; }
    
    constexpr auto* begin() const noexcept { return &m_Data[0]; }
    constexpr auto* end() const noexcept { return &m_Data[Size]; }

    template<typename U>
    constexpr auto dot(const Vector<U, Size>& v) const noexcept {
        decltype(m_Data[0] + v[0]) result = 0;
        for (std::size_t i = 0; i < Size; ++i)
            result += (m_Data[i] * v[i]);
        return result;
    }

    template<typename U>
        requires(Size == 3)
    constexpr auto cross(const Vector<U, 3>& v) const noexcept {
        return xme::Vector<decltype(m_Data[0] + v[0]), 3>{
            m_Data[1] * v[2] - m_Data[2] * v[1],
            m_Data[2] * v[0] - m_Data[0] * v[2],
            m_Data[0] * v[1] - m_Data[1] * v[0],
        };
    }

    constexpr auto lenght() const noexcept { return std::sqrt(dot(*this)); }

    constexpr auto normalized() const noexcept { return *this * (1 / lenght()); }

    template<typename U>
    constexpr auto reflect(const Vector<U, Size>& n) const noexcept {
        return *this - 2 * dot(n) * n;
    }

    template<typename U>
    constexpr auto distance(const Vector<U, Size>& v) const noexcept {
        return (v - *this).lenght();
    }

    template<typename U>
        requires(Size >= 3)
    constexpr auto rotateX(U angle) const noexcept {
        Vector<T, Size> result{*this};
        const auto sin{std::sin(angle)};
        const auto cos(std::cos(angle));
        result[1] = m_Data[1] * cos - m_Data[2] * sin;
        result[2] = m_Data[1] * sin + m_Data[2] * cos;
        return result;
    }

    template<typename U>
        requires(Size >= 3)
    constexpr auto rotateY(U angle) const noexcept {
        Vector<T, Size> result{*this};
        const auto sin{std::sin(angle)};
        const auto cos(std::cos(angle));
        result[0] = m_Data[0] * cos + m_Data[2] * sin;
        result[2] = -m_Data[0] * sin + m_Data[2] * cos;
        return result;
    }

    template<typename U>
        requires(Size >= 3)
    constexpr auto rotateZ(U angle) const noexcept {
        Vector<T, Size> result{*this};
        const auto sin{std::sin(angle)};
        const auto cos(std::cos(angle));
        result[0] = m_Data[0] * cos - m_Data[1] * sin;
        result[1] = m_Data[0] * sin + m_Data[1] * cos;
        return result;
    }
private:
    std::array<T, Size> m_Data{};
};

template<typename T, typename...Args>
Vector(T, Args...) -> Vector<std::common_type_t<T, Args...>, sizeof...(Args)+1>;
} // namespace xme

#include "../../../private/math/vectors/io.hpp"
#include "../../../private/math/vectors/operators.hpp"
#include "../../../private/math/vectors/piecewise.hpp"