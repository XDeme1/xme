#pragma once
#include <type_traits>

namespace xme {
template<typename T>
concept CFloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept CIntegral = std::is_integral_v<T>;

template<typename T>
concept CSignedIntegral = CIntegral<T> && std::is_signed_v<T>;

template<typename T>
concept CUnsignedIntegral = CIntegral<T> && std::is_unsigned_v<T>;

template<typename T>
concept CArithmetic = CFloatingPoint<T> || CIntegral<T>;
}  // namespace xme
