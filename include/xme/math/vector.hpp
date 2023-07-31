#pragma once
#include <array>
#include <type_traits>

namespace xme {
template <typename T, std::size_t Size>
struct Vector {
  public:
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

    constexpr Vector() noexcept = default;
    constexpr Vector(const Vector&) noexcept = default;
    constexpr Vector(Vector&&) noexcept = default;

    constexpr auto operator=(const Vector&) noexcept -> Vector& = default;
    constexpr auto operator=(Vector&&) noexcept -> Vector& = default;

    template <typename U>
    constexpr Vector(U s) noexcept { m_Data.fill(s); }

    template <typename U>
        requires(Size == 2)
    constexpr Vector(U s) noexcept : Vector(s, s) {}

    template <typename U>
        requires(Size == 3)
    constexpr Vector(U s) noexcept : Vector(s, s, s) {}

    template <typename U>
        requires(Size == 4)
    constexpr Vector(U s) noexcept : Vector(s, s, s, s) {}

    template <typename... Args>
        requires(sizeof...(Args) == Size)
    constexpr Vector(Args... args) noexcept : m_Data({static_cast<T>(args)...}) {}

    // Vector3 Conversion constructors
    template <typename U>
        requires(Size == 3)
    constexpr Vector(auto s, const Vector<U, 2>& v) noexcept : Vector(s, v[0], v[1]) {}

    template <typename U>
        requires(Size == 3)
    constexpr Vector(const Vector<U, 2>& v, auto s) noexcept : Vector(v[0], v[1], s) {}

    // Vector4 Conversion constructors
    template <typename U>
        requires(Size == 4)
    constexpr Vector(auto s1, auto s2, const Vector<U, 2>& v) noexcept
        : Vector(s1, s2, v[0], v[1]) {}

    template <typename U>
        requires(Size == 4)
    constexpr Vector(auto s1, const Vector<U, 2>& v, auto s2) noexcept
        : Vector(s1, v[0], v[1], s2) {}

    template <typename U>
        requires(Size == 4)
    constexpr Vector(const Vector<U, 2>& v, auto s1, auto s2) noexcept
        : Vector(v[0], v[1], s1, s2) {}

    template <typename U1, typename U2>
        requires(Size == 4)
    constexpr Vector(const Vector<U1, 2>& v1, const Vector<U2, 2>& v2) noexcept
        : Vector(v1[0], v1[1], v2[0], v2[1]) {}

    template <typename U>
        requires(Size == 4)
    constexpr Vector(auto s, const Vector<U, 3>& v) noexcept
        : Vector(s, v[0], v[1], v[2]) {}

    template <typename U>
        requires(Size == 4)
    constexpr Vector(const Vector<U, 3>& v, auto s) noexcept
        : Vector(v[0], v[1], v[2], s) {}

    template <typename U>
    constexpr auto& operator=(const Vector<U, Size>& v) noexcept {
        for (std::size_t i = 0; i < Size; ++i)
            m_Data[i] = static_cast<T>(v[i]);
        return *this;
    }

    constexpr auto& operator[](std::size_t i) noexcept { return m_Data[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return m_Data[i]; }

  private:
    std::array<T, Size> m_Data = {};
};
} // namespace xme

#include "../../../private/math/vectors/vector_operators.hpp"
