#pragma once
#include <concepts>

namespace xme::math {
template<std::floating_point T>
inline constexpr T e_v = 2.718281828459045235360287471352662498L;

template<std::floating_point T>
inline constexpr T pi_v = 3.141592653589793238462643383279502884L;

template<std::floating_point T>
inline constexpr T inv_pi_v = 0.318309886183790671537767526745028724L;

template<std::floating_point T>
inline constexpr T inv_sqrtpi_v = 0.564189583547756286948079451560772586L;

template<std::floating_point T>
inline constexpr T log2e_v = 1.442695040888963407359924681001892137L;

template<std::floating_point T>
inline constexpr T log10e_v = 0.434294481903251827651128918916605082L;

template<std::floating_point T>
inline constexpr T ln2_v = 0.693147180559945309417232121458176568L;

template<std::floating_point T>
inline constexpr T ln10_v = 2.302585092994045684017991454684364208L;

template<std::floating_point T>
inline constexpr T sqrt2_v = 1.414213562373095048801688724209698079L;

template<std::floating_point T>
inline constexpr T sqrt3_v = 1.732050807568877293527446341505872367L;

template<std::floating_point T>
inline constexpr T phi_v = 1.618033988749894848204586834365638118L;

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
