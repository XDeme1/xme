#pragma once
#include "forward.hpp"
#include "concepts.hpp"
#include <array>
#include <cmath>
#include <type_traits>

namespace xme {
template<typename T, std::size_t Size>
struct Vector {
public:
    static_assert(CArithmetic<T>, "T must be an arithmetic type");

    static constexpr std::size_t size = Size;

    constexpr Vector() noexcept = default;

    template<CArithmetic U>
    constexpr Vector(U s) noexcept {
        m_data.fill(s);
    }

    template<typename... Args>
        requires((sizeof...(Args) == Size) && (CArithmetic<Args> && ...))
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

    constexpr auto operator-() const noexcept -> Vector {
        Vector result;
        for (std::size_t i = 0; i < Size; ++i)
            result[i] = -m_data[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator+(U s) const noexcept -> Vector {
        Vector result;
        for(std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] + s;
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator+(const Vector<U, Size>& v) const noexcept -> Vector {
        Vector result;
        for(std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] + v[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator-(U s) const noexcept -> Vector {
        Vector result;
        for(std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] - s;
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator-(const Vector<U, Size>& v) const noexcept -> Vector {
        Vector result;
        for(std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] - v[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator*(U s) const noexcept -> Vector {
        Vector result;
        for(std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] * s;
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator*(const Vector<U, Size>& v) const noexcept -> Vector {
        Vector result;
        for(std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] * v[i];
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator/(U s) const noexcept -> Vector {
        Vector result;
        for(std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] / s;
        return result;
    }

    template<CArithmetic U>
    constexpr auto operator/(const Vector<U, Size>& v) const noexcept -> Vector {
        Vector result;
        for(std::size_t i = 0; i < Size; ++i)
            result[i] = m_data[i] / v[i];
        return result;
    }

    template<CArithmetic U>
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

    template<CArithmetic U>
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

    template<CArithmetic U>
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

    template<CArithmetic U>
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

    template<CArithmetic U>
    constexpr auto operator/=(const Vector<U, Size>& v) noexcept -> Vector& {
        for (std::size_t i = 0; i < Size; ++i)
                m_data[i] /= v[i];
        return *this;
    }

    constexpr auto operator[](std::size_t i) noexcept -> T& { return m_data[i]; }

    constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        return m_data[i];
    }

    constexpr auto operator<=>(const Vector&) const noexcept = default;

    constexpr bool operator==(const Vector&) const noexcept = default;

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

template<typename T, typename... Args>
Vector(T, Args...) -> Vector<std::common_type_t<T, Args...>, sizeof...(Args) + 1>;

template<std::size_t I, typename T, std::size_t Size>
constexpr auto get(Vector<T, Size>& v) noexcept -> decltype(auto) {
    return v[I];
}

template<std::size_t I, typename T, std::size_t Size>
constexpr auto get(const Vector<T, Size>& v) noexcept -> decltype(auto) {
    return v[I];
}

template<typename T, std::size_t Size>
constexpr auto begin(Vector<T, Size>& v) noexcept -> T* {
    return std::addressof(get<0>(v));
}

template<typename T, std::size_t Size>
constexpr auto begin(const Vector<T, Size>& v) noexcept -> const T* {
    return std::addressof(get<0>(v));
}

template<typename T, std::size_t Size>
constexpr auto end(Vector<T, Size>& v) noexcept -> T* {
    return std::addressof(get<Size>(v));
}

template<typename T, std::size_t Size>
constexpr auto end(const Vector<T, Size>& v) noexcept -> const T* {
    return std::addressof(get<Size>(v));
}
} // namespace xme

namespace std {
template<typename T, std::size_t Size>
struct tuple_size<xme::Vector<T, Size>> : integral_constant<std::size_t, Size> {};

template<std::size_t I, typename T, std::size_t Size>
struct tuple_element<I, xme::Vector<T, Size>> {
    using type = T;
};
} // namespace std