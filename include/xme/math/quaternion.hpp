#pragma once
#include <array>

namespace xme {
template<typename T>
struct Quaternion {
public:
    static_assert(std::is_floating_point_v<T>, "T must be a floating point");

    constexpr Quaternion() = default;
    constexpr Quaternion(auto w, auto x, auto y, auto z)
        : m_Data({static_cast<T>(w), static_cast<T>(x), static_cast<T>(y),
                  static_cast<T>(z)}) {}

    constexpr auto& operator[](std::size_t i) noexcept { return m_Data[i]; }
    constexpr auto& operator[](std::size_t i) const noexcept { return m_Data[i]; }

private:
    std::array<T, 4> m_Data{1, 0, 0, 0}; // w, x, y, z
};

template<typename T, typename...Args, typename Temp = std::common_type_t<T, Args...>>
Quaternion(T, Args...) -> Quaternion<std::conditional_t<std::is_integral_v<Temp>, double, Temp>>;

template<typename T, typename U>
constexpr auto operator+(const Quaternion<T>& q1, const Quaternion<U>& q2) noexcept {
    return Quaternion{q1[0] + q2[0], q1[1] + q2[1], q1[2] + q2[2], q1[3] + q2[3]};
}
} // namespace xme