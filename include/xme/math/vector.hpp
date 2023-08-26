#pragma once
#include "concepts.hpp"
#include <array>
#include <cmath>
#include <type_traits>

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
    constexpr Vector(U s) noexcept {
        m_data.fill(s);
    }

    template<CArithmetic... Args>
        requires(sizeof...(Args) == Size)
    constexpr Vector(Args... args) noexcept : m_data({static_cast<T>(args)...}) {}

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
            m_data[i] = static_cast<T>(v[i]);
    }

    constexpr auto operator+() const noexcept -> Vector { return *this; }
    constexpr auto operator-() const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = -m_data[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator+(U s) const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] + s;
        return result;
    }
    template<typename U>
    constexpr auto operator+(const Vector<U, Size>& v) const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] + v[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator-(U s) const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] - s;
        return result;
    }
    template<typename U>
    constexpr auto operator-(const Vector<U, Size>& v) const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] - v[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator*(U s) const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] * s;
        return result;
    }
    template<typename U>
    constexpr auto operator*(const Vector<U, Size>& v) const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] * v[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator/(U s) const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] / s;
        return result;
    }
    template<typename U>
    constexpr auto operator/(const Vector<U, Size>& v) const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] / v[i];
        return result;
    }

    template<typename U>
    constexpr auto operator=(const Vector<U, Size>& v) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
            m_data[i] = static_cast<T>(v[i]);
        return *this;
    }

    template<CArithmetic U>
    constexpr auto operator+=(U s) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
            m_data[i] += s;
        return *this;
    }

    template<typename U>
    constexpr auto operator+=(const Vector<U, Size>& v) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
            m_data[i] += v[i];
        return *this;
    }

    template<CArithmetic U>
    constexpr auto operator-=(U s) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
            m_data[i] -= s;
        return *this;
    }

    template<typename U>
    constexpr auto operator-=(const Vector<U, Size>& v) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
            m_data[i] -= v[i];
        return *this;
    }

    template<CArithmetic U>
    constexpr auto operator*=(U s) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
            m_data[i] *= s;
        return *this;
    }

    template<typename U>
    constexpr auto operator*=(const Vector<U, Size>& v) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
            m_data[i] *= v[i];
        return *this;
    }

    template<CArithmetic U>
    constexpr auto operator/=(U s) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
            m_data[i] /= s;
        return *this;
    }

    template<typename U>
    constexpr auto operator/=(const Vector<U, Size>& v) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
            m_data[i] /= v[i];
        return *this;
    }

    constexpr auto& operator[](std::size_t i) noexcept { return m_data[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return m_data[i]; }

    constexpr auto dot(const Vector& v) const noexcept -> T {
        T result = 0;
        for (std::size_t i = 0; i < Size; ++i)
            result += (m_data[i] * v[i]);
        return result;
    }

    constexpr auto cross(const Vector& v) const noexcept -> Vector {
        static_assert(Size == 3, "Vector size must be 3");
        return {
            m_data[1] * v[2] - m_data[2] * v[1],
            m_data[2] * v[0] - m_data[0] * v[2],
            m_data[0] * v[1] - m_data[1] * v[0],
        };
    }

    constexpr auto lenght() const noexcept { return std::sqrt(dot(*this)); }

    constexpr auto normalized() const noexcept -> Vector {
        return *this * (1 / lenght());
    }

    constexpr auto reflect(const Vector& n) const noexcept -> Vector {
        return *this - n * dot(n) * 2;
    }

    constexpr auto distance(const Vector& v) const noexcept {
        return (v - *this).lenght();
    }

    template<CArithmetic U>
        requires(std::floating_point<T>)
    constexpr auto rotateX(U angle) const noexcept -> Vector {
        static_assert(Size >= 3, "Vector size must be 3 or higher");

        const auto sin{std::sin(angle)};
        const auto cos(std::cos(angle));

        Vector result{*this};
        result[1] = m_data[1] * cos - m_data[2] * sin;
        result[2] = m_data[1] * sin + m_data[2] * cos;
        return result;
    }

    template<CArithmetic U>
        requires(std::floating_point<T>)
    constexpr auto rotateY(U angle) const noexcept -> Vector {
        static_assert(Size >= 3, "Vector size must be 3 or higher");

        const auto sin{std::sin(angle)};
        const auto cos(std::cos(angle));

        Vector result{*this};
        result[0] = m_data[0] * cos + m_data[2] * sin;
        result[2] = -m_data[0] * sin + m_data[2] * cos;
        return result;
    }

    template<CArithmetic U>
        requires(std::floating_point<T>)
    constexpr auto rotateZ(U angle) const noexcept -> Vector {
        static_assert(Size >= 3, "Vector size must be 3 or higher");

        const auto sin{std::sin(angle)};
        const auto cos(std::cos(angle));

        Vector result{*this};
        result[0] = m_data[0] * cos - m_data[1] * sin;
        result[1] = m_data[0] * sin + m_data[1] * cos;
        return result;
    }
private:
    std::array<T, Size> m_data{};
};

template<typename T, std::size_t Size>
constexpr bool operator==(const Vector<T, Size>& v1, const Vector<T, Size>& v2) noexcept {
    for (std::size_t i = 0; i < Size; ++i) {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

template<typename T, std::size_t Size>
constexpr bool operator!=(const Vector<T, Size>& v1, const Vector<T, Size>& v2) noexcept {
    return !xme::operator==(v1, v2);
}

template<typename T, typename... Args>
Vector(T, Args...) -> Vector<std::common_type_t<T, Args...>, sizeof...(Args) + 1>;
} // namespace xme

#include "../../../private/math/vectors/io.hpp"