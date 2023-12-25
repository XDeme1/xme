#pragma once
#include <xme/setup.hpp>
#include <xme/core/concepts/concepts.hpp>
#include "matrix.hpp"

namespace xme::math {
template<floating_point_c T>
class Quaternion {
public:
    XME_INLINE constexpr Quaternion() noexcept = default;

    XME_INLINE constexpr Quaternion(auto _w, auto _x, auto _y, auto _z) noexcept :
      w(static_cast<T>(_w)), x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z)) {}

    XME_INLINE constexpr Quaternion(const Vector<T, 3>& euler) noexcept {
        const auto c = cos(euler * T(0.5));
        const auto s = sin(euler * T(0.5));

        w = c[0] * c[1] * c[2] + s[0] * s[1] * s[2];
        x = s[0] * c[1] * c[2] - c[0] * s[1] * s[2];
        y = c[0] * s[1] * c[2] + s[0] * c[1] * s[2];
        z = c[0] * c[1] * s[2] - s[0] * s[1] * c[2];
    }

    XME_INLINE constexpr operator Matrix<T, 3>() const noexcept;
    XME_INLINE constexpr operator Matrix<T, 4>() const noexcept;

    template<typename U>
    XME_INLINE constexpr auto operator+(const Quaternion<U>& q) const noexcept;
    template<typename U>
    XME_INLINE constexpr auto operator-(const Quaternion<U>& q) const noexcept;
    template<typename U>
    XME_INLINE constexpr auto operator*(const Quaternion<U>& q) const noexcept;

    XME_INLINE constexpr auto operator[](std::size_t i) noexcept -> T& { return (&w)[i]; }
    XME_INLINE constexpr auto operator[](std::size_t i) const noexcept -> const T& {
        return (&w)[i];
    }

    T w{1};
    T x{0};
    T y{0};
    T z{0};
};

template<typename T, typename... Args, typename Temp = std::common_type_t<T, Args...>>
Quaternion(T, Args...) -> Quaternion<std::conditional_t<std::is_integral_v<Temp>, float, Temp>>;

template<floating_point_c T>
XME_INLINE constexpr Quaternion<T>::operator Matrix<T, 3>() const noexcept {
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
}  // namespace xme::math
