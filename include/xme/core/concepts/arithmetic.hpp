#pragma once
#include <type_traits>

namespace xme {
template<typename T>
concept floating_point_c = std::is_floating_point_v<T>;

template<typename T>
concept integral_c = std::is_integral_v<T>;

template<typename T>
concept signed_integral_c = integral_c<T> && std::is_signed_v<T>;

template<typename T>
concept unsigned_integral_c = integral_c<T> && std::is_unsigned_v<T>;

template<typename T>
concept arithmetic_c = floating_point_c<T> || integral_c<T>;
}  // namespace xme
