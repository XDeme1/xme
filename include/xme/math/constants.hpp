#pragma once
#include <type_traits>

namespace xme::math {
namespace detail {
template<typename T>
using enable_float = typename std::enable_if<std::is_floating_point<T>::value, T>::type;
}

template<typename T>
inline constexpr T e_v = detail::enable_float<T>(2.718281828459045235360287471352662498L);

template<typename T>
inline constexpr T pi_v = detail::enable_float<T>(3.141592653589793238462643383279502884L);

template<typename T>
inline constexpr T inv_pi_v = detail::enable_float<T>(0.318309886183790671537767526745028724L);

template<typename T>
inline constexpr T inv_sqrtpi_v = detail::enable_float<T>(0.564189583547756286948079451560772586L);

template<typename T>
inline constexpr T log2e_v = detail::enable_float<T>(1.442695040888963407359924681001892137L);

template<typename T>
inline constexpr T log10e_v = detail::enable_float<T>(0.434294481903251827651128918916605082L);

template<typename T>
inline constexpr T ln2_v = detail::enable_float<T>(0.693147180559945309417232121458176568L);

template<typename T>
inline constexpr T ln10_v = detail::enable_float<T>(2.302585092994045684017991454684364208L);

template<typename T>
inline constexpr T sqrt2_v = detail::enable_float<T>(1.414213562373095048801688724209698079L);

template<typename T>
inline constexpr T sqrt3_v = detail::enable_float<T>(1.732050807568877293527446341505872367L);

template<typename T>
inline constexpr T phi_v = detail::enable_float<T>(1.618033988749894848204586834365638118L);

inline constexpr double e          = e_v<double>;
inline constexpr double pi         = pi_v<double>;
inline constexpr double inv_pi     = inv_pi_v<double>;
inline constexpr double inv_sqrtpi = inv_sqrtpi_v<double>;
inline constexpr double log2e      = log2e_v<double>;
inline constexpr double log10e     = log10e_v<double>;
inline constexpr double ln2        = ln2_v<double>;
inline constexpr double ln10       = ln10_v<double>;
inline constexpr double sqrt2      = sqrt2_v<double>;
inline constexpr double sqrt3      = sqrt3_v<double>;
inline constexpr double phi        = phi_v<double>;
}  // namespace xme::math
