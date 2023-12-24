#pragma once
#include <type_traits>

namespace xme {
template<typename T>
concept floating_point = std::is_floating_point_v<T>;

template<typename T>
concept integral = std::is_integral_v<T>;

template<typename T>
concept signed_integral = integral<T> && std::is_signed_v<T>;

template<typename T>
concept unsigned_integral = integral<T> && std::is_unsigned_v<T>;

template<typename T>
concept arithmetic = floating_point<T> || integral<T>;
}  // namespace xme
