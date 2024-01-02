#pragma once
#include <xme/setup.hpp>
#include <xme/core/concepts/concepts.hpp>

namespace xme::math {
template<CFloatingPoint T>
class Quaternion {
public:
    constexpr Quaternion() noexcept = default;

    constexpr Quaternion(auto _w, auto _x, auto _y, auto _z) noexcept :
      w(static_cast<T>(_w)), x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z)) {}

    template<typename U>
    constexpr auto operator+(const Quaternion<U>& q) const noexcept -> Quaternion {
        return {w + q.w, x + q.x, y + q.y, z + q.z};
    }

    template<typename U>
    constexpr auto operator-(const Quaternion<U>& q) const noexcept -> Quaternion {
        return {w - q.w, x - q.x, y - q.y, z - q.z};
    }

    template<typename U>
    constexpr auto operator*(const Quaternion<U>& q) const noexcept;

    constexpr auto operator[](std::size_t i) noexcept -> T& { return (&w)[i]; }
    constexpr auto operator[](std::size_t i) const noexcept -> const T& { return (&w)[i]; }

    T w;
    T x;
    T y;
    T z;
};

template<typename T, typename... Args, typename Temp = std::common_type_t<T, Args...>>
Quaternion(T, Args...) -> Quaternion<std::conditional_t<std::is_integral_v<Temp>, float, Temp>>;
}  // namespace xme::math
