#pragma once
#include <concepts>

namespace xme::math {
//! e
template<std::floating_point T>
inline constexpr T e_v = static_cast<T>(
    2.718281828'4590452353'6028747135'2662497757'2470936999'5957496696'7627724076'6303535475L);

//! e^2
template<std::floating_point T>
inline constexpr T e_sqr_v = static_cast<T>(
    7.389056098'9306502272'3042746057'5007813180'3155705518'4732408712'7822522573'7960790577L);

//! e^π
template<std::floating_point T>
inline constexpr T e_pow_pi_v = static_cast<T>(
    23.14069263'2779269005'7290863679'4854738026'6106242600'2119934450'4640952434'2350690452L);

//! π
template<std::floating_point T>
inline constexpr T pi_v = static_cast<T>(
    3.141592653'5897932384'6264338327'9502884197'1693993751'0582097494'4592307816'4062862089L);

//! 2π
template<std::floating_point T>
inline constexpr T two_pi_v = static_cast<T>(
    6.283185307'1795864769'2528676655'9005768394'3387987502'1164194988'9184615632'8125724179L);

//! 2/π
template<std::floating_point T>
inline constexpr T two_over_pi_v = static_cast<T>(
    0.636619772'3675813430'7553505349'0057448137'8385829618'2579499066'9376235587'1905369061L);

//! π/2
template<std::floating_point T>
inline constexpr T pi_over_two_v = static_cast<T>(
    1.570796326'7948966192'3132169163'9751442098'5846996875'5291048747'2296153908'2031431044L);

//! π^2
template<std::floating_point T>
inline constexpr T pi_sqr_v = static_cast<T>(
    9.869604401'0893586188'3449099987'6151135313'6994072407'9062641334'9376220044'8224192052L);

//! 1/π
template<std::floating_point T>
inline constexpr T inv_pi_v = static_cast<T>(
    0.318309886'1837906715'3776752674'5028724068'9192914809'1289749533'4688117793'5952684530L);

//! τ
template<std::floating_point T>
inline constexpr T tau_v = math::two_pi_v<T>;

//! log2(e)
template<std::floating_point T>
inline constexpr T log2_e_v = static_cast<T>(
    1.442695040'8889634073'5992468100'1892137426'6459541529'8593413544'9406931109'2191811850L);

//! log10(e)
template<std::floating_point T>
inline constexpr T log10_e_v = static_cast<T>(
    0.434294481'9032518276'5112891891'6605082294'3970058036'6656611445'3783165864'6492088707L);

//! ln(2)
template<std::floating_point T>
inline constexpr T ln_two_v = static_cast<T>(
    0.693147180'5599453094'1723212145'8176568075'5001343602'5525412068'0009493393'6219696947L);

//! ln(10)
template<std::floating_point T>
inline constexpr T ln_ten_v = static_cast<T>(
    2.302585092'9940456840'1799145468'4364207601'1014886287'7297603332'7900967572'6096773524L);

//! sqrt(2)
template<std::floating_point T>
inline constexpr T sqrt_two_v = static_cast<T>(
    1.414213562'3730950488'0168872420'9698078569'6718753769'4807317667'9737990732'4784621070L);

//! sqrt(3)
template<std::floating_point T>
inline constexpr T sqrt_three_v = static_cast<T>(
    1.732050807'5688772935'2744634150'5872366942'8052538103'8062805580'6979451933'0169088000L);

//! sqrt(5)
template<std::floating_point T>
inline constexpr T sqrt_five_v = static_cast<T>(
    2.236067977'4997896964'0917366873'1276235440'6183596115'2572427089'7245410520'9256378048L);

//! sqrt(e)
template<std::floating_point T>
inline constexpr T sqrt_e_v = static_cast<T>(
    1.648721270'7001281468'4865078781'4163571653'7761007101'4801157507'9311640661'0211942156L);

//! sqrt(pi)
template<std::floating_point T>
inline constexpr T sqrt_pi_v = static_cast<T>(
    1.772453850'9055160272'9816748334'1145182797'5494561223'8712821380'7789852911'2845910321L);

//! sqrt(2π)
template<std::floating_point T>
inline constexpr T sqrt_two_pi_v = static_cast<T>(
    2.506628274'6310005024'1576528481'1045253006'9867406099'3831662992'3576342293'6546078419L);

//! sqrt(2πe)
template<std::floating_point T>
inline constexpr T sqrt_two_pi_e_v = static_cast<T>(
    4.132731354'1224929384'6939188429'9852649445'5219169913'0845155665'1253797957'9285134170L);

//! 1/sqrt(π)
template<std::floating_point T>
inline constexpr T inv_sqrt_pi_v = static_cast<T>(
    0.564189583'5477562869'4807945156'0772585844'0506293289'9885684408'5721710642'4684414934L);

//! cbrt(2)
template<std::floating_point T>
inline constexpr T cbrt_two_v = static_cast<T>(
    1.259921049'8948731647'6721060727'8228350570'2514647015'0798008197'5112155299'6765139594L);

//! Reciprocal fibonacci constant
template<std::floating_point T>
inline constexpr T inv_fibonacci_v = static_cast<T>(
    3.359885666'2431775531'7201130291'8927179688'9051337319'6848649555'3815325130'3189966833L);

//! ϕ (Golden ratio)
template<std::floating_point T>
inline constexpr T phi_v = static_cast<T>(
    1.618033988'7498948482'0458683436'5638117720'3091798057'6286213544'8622705260'4628189024L);

//! Catalan's constant
template<std::floating_point T>
inline constexpr T catalan_v = static_cast<T>(
    0.915965594'1772190150'5460351493'2384110774'1493742816'7213426649'8119621763'0197762547L);

//! γ (Euler-Mascheroni constant)
template<std::floating_point T>
inline constexpr T euler_v = static_cast<T>(
    0.577215664'9015328606'0651209008'2402431042'1593359399'2359880576'7234884867'7267776646L);

//! G (Gauss constant)
template<std::floating_point T>
inline constexpr T gauss_v = static_cast<T>(
    0.834626841'6740731862'8142973279'9046808993'9930134903'4700244982'7370103681'9927095264L);

//! ρ (Plastic number)
template<std::floating_point T>
inline constexpr T plastic_v = static_cast<T>(
    1.324717957'2447460259'6090885447'8097340734'4040569017'3336453401'5050302827'8512455475L);

//! ζ(2)
template<std::floating_point T>
inline constexpr T zeta_two_v = static_cast<T>(
    1.644934066'8482264364'7241516664'6025189218'9499012067'9843773555'8229370007'4704032008L);

//! ζ(3)
template<std::floating_point T>
inline constexpr T zeta_three_v = static_cast<T>(
    1.202056903'1595942853'9973816151'1449990764'9862923404'9888179227'1555341838'2057863130L);

//! ζ(4)
template<std::floating_point T>
inline constexpr T zeta_four_v = static_cast<T>(
    1.082323233'7111381915'1600369654'1167902774'7509519187'2690768297'6215444120'6161869688L);

inline constexpr double e        = e_v<double>;
inline constexpr double e_sqr    = e_sqr_v<double>;
inline constexpr double e_pow_pi = e_pow_pi_v<double>;

inline constexpr double pi          = pi_v<double>;
inline constexpr double two_pi      = two_pi_v<double>;
inline constexpr double two_over_pi = two_over_pi_v<double>;
inline constexpr double pi_over_two = pi_over_two_v<double>;
inline constexpr double pi_sqr      = pi_sqr_v<double>;
inline constexpr double inv_pi      = inv_pi_v<double>;

inline constexpr double tau = tau_v<double>;

inline constexpr double log2_e  = log2_e_v<double>;
inline constexpr double log10_e = log10_e_v<double>;
inline constexpr double ln_two  = ln_two_v<double>;
inline constexpr double ln_ten  = ln_ten_v<double>;

inline constexpr double sqrt_two      = sqrt_two_v<double>;
inline constexpr double sqrt_three    = sqrt_three_v<double>;
inline constexpr double sqrt_five     = sqrt_five_v<double>;
inline constexpr double sqrt_e        = sqrt_e_v<double>;
inline constexpr double sqrt_pi       = sqrt_pi_v<double>;
inline constexpr double sqrt_two_pi   = sqrt_two_pi_v<double>;
inline constexpr double sqrt_two_pi_e = sqrt_two_pi_e_v<double>;
inline constexpr double inv_sqrt_pi   = inv_sqrt_pi_v<double>;

inline constexpr double cbrt_two = cbrt_two_v<double>;

inline constexpr double inv_fibonacci = inv_fibonacci_v<double>;
inline constexpr double phi           = phi_v<double>;
inline constexpr double catalan       = catalan_v<double>;
inline constexpr double euler         = euler_v<double>;
inline constexpr double gauss         = gauss_v<double>;
inline constexpr double plastic       = plastic_v<double>;
inline constexpr double zeta_two      = zeta_two_v<double>;
inline constexpr double zeta_three    = zeta_three_v<double>;
inline constexpr double zeta_four     = zeta_four_v<double>;
}  // namespace xme::math
