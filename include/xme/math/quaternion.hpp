#pragma once
#include "matrix.hpp"
#include <array>

namespace xme {
template<typename T>
class Quaternion {
public:
    static_assert(std::is_floating_point_v<T>, "T must be a floating point");

    constexpr Quaternion() noexcept = default;
    constexpr Quaternion(auto w, auto x, auto y, auto z) noexcept
        : m_data({static_cast<T>(w), static_cast<T>(x), static_cast<T>(y),
                  static_cast<T>(z)}) {}

    constexpr operator Matrix<T, 3>() const noexcept;
    constexpr operator Matrix<T, 4>() const noexcept;

    template<typename U>
    constexpr auto operator+(const Quaternion<U>& q) const noexcept;
    template<typename U>
    constexpr auto operator-(const Quaternion<U>& q) const noexcept;
    template<typename U>
    constexpr auto operator*(const Quaternion<U>& q) const noexcept;

    constexpr auto& operator[](std::size_t i) noexcept { return m_data[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return m_data[i]; }

private:
    std::array<T, 4> m_data{1, 0, 0, 0}; // w, x, y, z
};

template<typename T, typename... Args, typename Temp = std::common_type_t<T, Args...>>
Quaternion(T, Args...)
    -> Quaternion<std::conditional_t<std::is_integral_v<Temp>, float, Temp>>;

template<typename T>
constexpr Quaternion<T>::operator Matrix<T, 3>() const noexcept {
    return Matrix<T, 3>{};
}

template<typename T>
constexpr Quaternion<T>::operator Matrix<T, 4>() const noexcept {
    return Matrix<T, 4>{};
}

template<typename T>
template<typename U>
constexpr auto Quaternion<T>::operator+(const Quaternion<U>& q) const noexcept {
    return Quaternion{
        this[0] + q[0],
        this[1] + q[1],
        this[2] + q[2],
        this[3] + q[3],
    };
}

template<typename T>
template<typename U>
constexpr auto Quaternion<T>::operator-(const Quaternion<U>& q) const noexcept {
    return Quaternion{
        this[0] - q[0],
        this[1] - q[1],
        this[2] - q[2],
        this[3] - q[3],
    };
}
} // namespace xme