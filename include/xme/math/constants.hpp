#pragma once
#include <concepts>

namespace xme::math {
//! e
template<std::floating_point T>
inline constexpr T e_v = 2.718281828459045235360287471352662498L;

//! e^2
template<std::floating_point T>
inline constexpr T e_sqr_v = 7.389056098930650227230427460575007813L;

//! e^π
template<std::floating_point T>
inline constexpr T e_pow_pi_v = 23.14069263277926900572908636794854738L;

//! π
template<std::floating_point T>
inline constexpr T pi_v = 3.141592653589793238462643383279502884L;

//! 2π
template<std::floating_point T>
inline constexpr T two_pi_v = 6.283185307179586476925286766559005768L;

//! 2/π
template<std::floating_point T>
inline constexpr T two_over_pi_v = 0.636619772367581343075535053490057448L;

//! π/2
template<std::floating_point T>
inline constexpr T pi_over_two_v = 1.570796326794896619231321691639751442L;

//! π^2
template<std::floating_point T>
inline constexpr T pi_sqr_v = 9.869604401089358618834490999876151135L;

//! 1/π
template<std::floating_point T>
inline constexpr T inv_pi_v = 0.318309886183790671537767526745028724L;

//! 1/sqrt(π)
template<std::floating_point T>
inline constexpr T inv_sqrt_pi_v = 0.5641895835477562869480794515607725858L;

//! τ
template<std::floating_point T>
inline constexpr T tau_v = math::two_pi_v<T>;

//! log2(e)
template<std::floating_point T>
inline constexpr T log2_e_v = 1.442695040888963407359924681001892137L;

//! log10(e)
template<std::floating_point T>
inline constexpr T log10_e_v = 0.434294481903251827651128918916605082L;

//! ln(2)
template<std::floating_point T>
inline constexpr T ln_two_v = 0.693147180559945309417232121458176568L;

//! ln(10)
template<std::floating_point T>
inline constexpr T ln_ten_v = 2.302585092994045684017991454684364208L;

//! sqrt(2)
template<std::floating_point T>
inline constexpr T sqrt_two_v = 1.414213562373095048801688724209698079L;

//! sqrt(3)
template<std::floating_point T>
inline constexpr T sqrt_three_v = 1.732050807568877293527446341505872367L;

//! sqrt(5)
template<std::floating_point T>
inline constexpr T sqrt_five_v = 2.236067977499789696409173668731276235L;

//! sqrt(e)
template<std::floating_point T>
inline constexpr T sqrt_e_v = 1.648721270700128146848650787814163571L;

//! sqrt(2pi)
template<std::floating_point T>
inline constexpr T sqrt_two_pi_v = 2.506628274631000502415765284811045253L;

//! sqrt(2epi)
template<std::floating_point T>
inline constexpr T sqrt_two_e_pi_v = 4.132731354122492938469391884299852649L;

//! cbrt(2)
template<std::floating_point T>
inline constexpr T cbrt_two_v = 1.259921049894873164767210607278228350L;

//! Reciprocal fibonacci constant
template<std::floating_point T>
inline constexpr T inv_fibonacci_v = 3.359885666243177553172011302918927179L;

//! ϕ (Golden ratio)
template<std::floating_point T>
inline constexpr T phi_v = 1.618033988749894848204586834365638118L;

//! γ (Euler-Mascheroni constant)
template<std::floating_point T>
inline constexpr T euler_v = 0.577215664901532860606512090082402431L;

//! G (Gauss constant)
template<std::floating_point T>
inline constexpr T gauss_v = 0.834626841674073186281429732799046808L;

//! ρ (Plastic number)
template<std::floating_point T>
inline constexpr T plastic_v = 1.324717957244746025960908854478097340L;

inline constexpr double e        = e_v<double>;
inline constexpr double e_sqr    = e_sqr_v<double>;
inline constexpr double e_pow_pi = e_pow_pi_v<double>;

inline constexpr double pi          = pi_v<double>;
inline constexpr double two_pi      = two_pi_v<double>;
inline constexpr double two_over_pi = two_over_pi_v<double>;
inline constexpr double pi_over_two = pi_over_two_v<double>;
inline constexpr double pi_sqr      = pi_sqr_v<double>;
inline constexpr double inv_pi      = inv_pi_v<double>;
inline constexpr double inv_sqrt_pi = inv_sqrt_pi_v<double>;

inline constexpr double tau = tau_v<double>;

inline constexpr double log2_e  = log2_e_v<double>;
inline constexpr double log10_e = log10_e_v<double>;
inline constexpr double ln_two  = ln_two_v<double>;
inline constexpr double ln_ten  = ln_ten_v<double>;

inline constexpr double sqrt_two      = sqrt_two_v<double>;
inline constexpr double sqrt_three    = sqrt_three_v<double>;
inline constexpr double sqrt_five     = sqrt_five_v<double>;
inline constexpr double sqrt_e        = sqrt_e_v<double>;
inline constexpr double sqrt_two_pi   = sqrt_two_pi_v<double>;
inline constexpr double sqrt_two_e_pi = sqrt_two_e_pi_v<double>;

inline constexpr double cbrt_two = cbrt_two_v<double>;

inline constexpr double inv_fibonacci = inv_fibonacci_v<double>;
inline constexpr double phi           = phi_v<double>;
inline constexpr double euler         = euler_v<double>;
inline constexpr double gauss         = gauss_v<double>;
inline constexpr double plastic       = plastic_v<double>;
}  // namespace xme::math
