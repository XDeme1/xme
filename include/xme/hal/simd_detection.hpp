#pragma once
#include <cstdint>
#include <type_traits>

//! -------------------------------
//!      Detection SIMD Begin
//! -------------------------------
#if defined(__MMX__)
#define XME_HAS_SIMD_MMX true
#else
#define XME_HAS_SIMD_MMX false
#endif

#if defined(__SSE__)
#define XME_HAS_SIMD_SSE true
#else
#define XME_HAS_SIMD_SSE false
#endif

#if defined(__SSE2__)
#define XME_HAS_SIMD_SSE2 true
#else
#define XME_HAS_SIMD_SSE2 false
#endif

#if defined(__SSE3__)
#define XME_HAS_SIMD_SSE3 true
#else
#define XME_HAS_SIMD_SSE3 false
#endif

#if defined(__SSSE3__)
#define XME_HAS_SIMD_SSSE3 true
#else
#define XME_HAS_SIMD_SSSE3 false
#endif

#if defined(__SSE4_1__)
#define XME_HAS_SIMD_SSE41 true
#else
#define XME_HAS_SIMD_SSE41 false
#endif

#if defined(__SSE4_2__)
#define XME_HAS_SIMD_SSE42 true
#else
#define XME_HAS_SIMD_SSE42 false
#endif

#if defined(__AVX__)
#define XME_HAS_SIMD_AVX true
#else
#define XME_HAS_SIMD_AVX false
#endif

#if defined(__AVX2__)
#define XME_HAS_SIMD_AVX2 true
#else
#define XME_HAS_SIMD_AVX2 false
#endif

#if defined(__AVX512F__)
#define XME_HAS_SIMD_AVX512F true
#else
#define XME_HAS_SIMD_AVX512F false
#endif
//! ------------------------------
//!      Detection SIMD End
//! ------------------------------

//! ------------------------------
//!      Enable SIMD Begin
//! ------------------------------
#if defined(XME_ENABLE_SIMD_AVX512F)
#define XME_ENABLE_SIMD_AVX2
#define XME_USE_SIMD_AVX512F true
#else
#define XME_USE_SIMD_AVX512F false
#endif

#if defined(XME_ENABLE_SIMD_AVX2)
#define XME_ENABLE_SIMD_AVX
#define XME_USE_SIMD_AVX2 true
#else
#define XME_USE_SIMD_AVX2 false
#endif

#if defined(XME_ENABLE_SIMD_AVX)
#define XME_ENABLE_SIMD_SSE42
#define XME_USE_SIMD_AVX true
#else
#define XME_USE_SIMD_AVX false
#endif

#if defined(XME_ENABLE_SIMD_SSE42)
#define XME_ENABLE_SIMD_SSE41
#define XME_USE_SIMD_SSE42 true
#else
#define XME_USE_SIMD_SSE42 false
#endif

#if defined(XME_ENABLE_SIMD_SSE41)
#define XME_ENABLE_SIMD_SSSE3
#define XME_USE_SIMD_SSE41 true
#else
#define XME_USE_SIMD_SSE41 false
#endif

#if defined(XME_ENABLE_SIMD_SSSE3)
#define XME_ENABLE_SIMD_SSE3
#define XME_USE_SIMD_SSSE3 true
#else
#define XME_USE_SIMD_SSSE3 false
#endif

#if defined(XME_ENABLE_SIMD_SSE3)
#define XME_ENABLE_SIMD_SSE2
#define XME_USE_SIMD_SSE3 true
#else
#define XME_USE_SIMD_SSE3 false
#endif

#if defined(XME_ENABLE_SIMD_SSE2)
#define XME_ENABLE_SIMD_SSE
#define XME_USE_SIMD_SSE2 true
#else
#define XME_USE_SIMD_SSE2 false
#endif

#if defined(XME_ENABLE_SIMD_SSE)
#define XME_ENABLE_SIMD_MMX
#define XME_USE_SIMD_SSE true
#else
#define XME_USE_SIMD_SSE false
#endif

#if defined(XME_ENABLE_SIMD_MMX)
#define XME_USE_SIMD_MMX true
#else
#define XME_USE_SIMD_MMX false
#endif
//! ------------------------------
//!       Enable SIMD End
//! ------------------------------

#define XME_SIMD_MMX     0x0000'0001
#define XME_SIMD_SSE     0x0000'0002
#define XME_SIMD_SSE2    0x0000'0004
#define XME_SIMD_SSE3    0x0000'0008
#define XME_SIMD_SSSE3   0x0000'0010
#define XME_SIMD_SSE41   0x0000'0020
#define XME_SIMD_SSE42   0x0000'0040
#define XME_SIMD_AVX     0x0000'0080
#define XME_SIMD_AVX2    0x0000'0100
#define XME_SIMD_AVX512F 0x0000'0200

#define XME_SUPPORTED_SIMD                                                          \
    (XME_HAS_SIMD_MMX * XME_SIMD_MMX | XME_HAS_SIMD_SSE * XME_SIMD_SSE              \
        | XME_HAS_SIMD_SSE2 * XME_SIMD_SSE2 | XME_HAS_SIMD_SSE3 * XME_SIMD_SSE3     \
        | XME_HAS_SIMD_SSSE3 * XME_SIMD_SSSE3 | XME_HAS_SIMD_SSE41 * XME_SIMD_SSE41 \
        | XME_HAS_SIMD_SSE42 * XME_SIMD_SSE42 | XME_HAS_SIMD_AVX * XME_SIMD_AVX     \
        | XME_HAS_SIMD_AVX2 * XME_SIMD_AVX2 | XME_HAS_SIMD_AVX512F * XME_SIMD_AVX512F)

#define XME_ENABLED_SIMD                                                            \
    (XME_USE_SIMD_MMX * XME_SIMD_MMX | XME_USE_SIMD_SSE * XME_SIMD_SSE              \
        | XME_USE_SIMD_SSE2 * XME_SIMD_SSE2 | XME_USE_SIMD_SSE3 * XME_SIMD_SSE3     \
        | XME_USE_SIMD_SSSE3 * XME_SIMD_SSSE3 | XME_USE_SIMD_SSE41 * XME_SIMD_SSE41 \
        | XME_USE_SIMD_SSE42 * XME_SIMD_SSE42 | XME_USE_SIMD_AVX * XME_SIMD_AVX     \
        | XME_USE_SIMD_AVX2 * XME_SIMD_AVX2 | XME_USE_SIMD_AVX512F * XME_SIMD_AVX512F)

namespace xme::hal {
enum class ESimd : std::uint32_t {
    mmx     = XME_SIMD_MMX,
    sse     = XME_SIMD_SSE,
    sse2    = XME_SIMD_SSE2,
    sse3    = XME_SIMD_SSE3,
    ssse3   = XME_SIMD_SSSE3,
    sse41   = XME_SIMD_SSE41,
    sse42   = XME_SIMD_SSE42,
    avx     = XME_SIMD_AVX,
    avx2    = XME_SIMD_AVX2,
    avx512f = XME_SIMD_AVX512F
};

inline constexpr ESimd supported_simd = static_cast<ESimd>(XME_SUPPORTED_SIMD);
inline constexpr ESimd enabled_simd   = static_cast<ESimd>(XME_ENABLED_SIMD);

constexpr auto operator|(ESimd e1, ESimd e2) noexcept -> ESimd {
    using u = std::underlying_type_t<ESimd>;
    return ESimd(static_cast<u>(e1) | static_cast<u>(e2));
}

constexpr auto operator&(ESimd e1, ESimd e2) noexcept -> ESimd {
    using u = std::underlying_type_t<ESimd>;
    return ESimd(static_cast<u>(e1) & static_cast<u>(e2));
}
}  // namespace xme::hal
