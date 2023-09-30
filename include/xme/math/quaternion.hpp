#pragma once
#include "matrix.hpp"
#include "trigonometric.hpp"

namespace xme {
template<typename T>
class Quaternion {
public:
    static_assert(std::is_floating_point_v<T>, "T must be a floating point");

    constexpr Quaternion() noexcept = default;

    constexpr Quaternion(auto _w, auto _x, auto _y, auto _z) noexcept
        : w(static_cast<T>(_w)), x(static_cast<T>(_x)), y(static_cast<T>(_y)),
          z(static_cast<T>(_z)) {}

    constexpr Quaternion(const xme::Vector<T, 3>& euler) noexcept {
        const auto c = xme::cos(euler * T(0.5));
        const auto s = xme::sin(euler * T(0.5));

        w = c[0] * c[1] * c[2] + s[0] * s[1] * s[2];
        x = s[0] * c[1] * c[2] - c[0] * s[1] * s[2];
        y = c[0] * s[1] * c[2] + s[0] * c[1] * s[2];
        z = c[0] * c[1] * s[2] - s[0] * s[1] * c[2];
    }

    constexpr operator Matrix<T, 3>() const noexcept;
    constexpr operator Matrix<T, 4>() const noexcept;

    template<typename U>
    constexpr auto operator+(const Quaternion<U>& q) const noexcept;
    template<typename U>
    constexpr auto operator-(const Quaternion<U>& q) const noexcept;
    template<typename U>
    constexpr auto operator*(const Quaternion<U>& q) const noexcept;

    constexpr auto& operator[](std::size_t i) noexcept { return (&w)[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return (&w)[i]; }

    T w{1};
    T x{0};
    T y{0};
    T z{0};
};

template<typename T, typename... Args, typename Temp = std::common_type_t<T, Args...>>
Quaternion(T, Args...)
    -> Quaternion<std::conditional_t<std::is_integral_v<Temp>, float, Temp>>;

template<typename T>
constexpr Quaternion<T>::operator Matrix<T, 3>() const noexcept {
    Matrix<T, 3> result{1};
    result[0][0] = 1 - 2 * (y * y + z * z);
    result[0][1] = 2 * (x * y + w * z);
    result[0][2] = 2 * (x * z - w * y);

    result[1][0] = 2 * (x * y - w * z);
    result[1][1] = 1 - 2 * (x * x + z * z);
    result[1][2] = 2 * (y * z + w * x);

    result[2][0] = 2 * (x * z + w * y);
    result[2][1] = 2 * (y * z - w * x);
    result[2][2] = 1 - 2 * (x * x + y * y);
    return result;
}

template<typename T>
constexpr Quaternion<T>::operator Matrix<T, 4>() const noexcept {
    return Matrix<T, 4>{static_cast<Matrix<T, 3>>(*this)};
}

template<typename T>
template<typename U>
constexpr auto Quaternion<T>::operator+(const Quaternion<U>& q) const noexcept {
    return Quaternion{
        w + q.w,
        x + q.x,
        y + q.y,
        z + q.z,
    };
}

template<typename T>
template<typename U>
constexpr auto Quaternion<T>::operator-(const Quaternion<U>& q) const noexcept {
    return Quaternion{
        w - q.w,
        x - q.x,
        y - q.y,
        z - q.z,
    };
}
} // namespace xme