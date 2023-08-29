#pragma once
#include <immintrin.h>
#include <xme/platform/simd_detect.hpp>

namespace xme {
using vec4_simd = __m128;
using ivec4_simd = __m128i;

using ivec2_simd = __m128i;
using dvec2_simd = __m128d;

#if XME_SIMD_AVX
using dvec4_simd = __m256d;
#endif

// SSE2 is the baseline for x86-64
inline auto vec4Add(vec4_simd v1, vec4_simd v2) -> vec4_simd {
    return _mm_add_ps(v1, v2);
}

inline auto vec4Sub(vec4_simd v1, vec4_simd v2) -> vec4_simd {
    return _mm_sub_ps(v1, v2);
}

inline auto vec4Mul(vec4_simd v1, vec4_simd v2) -> vec4_simd {
    return _mm_mul_ps(v1, v2);
}

inline auto vec4Div(vec4_simd v1, vec4_simd v2) -> vec4_simd {
    return _mm_div_ps(v1, v2);
}

#if XME_SIMD_AVX
inline auto vec4Add(dvec4_simd v1, dvec4_simd v2) -> dvec4_simd {
    return _mm256_add_pd(v1, v2);
}

inline auto vec4Sub(dvec4_simd v1, dvec4_simd v2) -> dvec4_simd {
    return _mm256_sub_pd(v1, v2);
}

inline auto vec4Mul(dvec4_simd v1, dvec4_simd v2) -> dvec4_simd {
    return _mm256_mul_pd(v1, v2);
}

inline auto vec4Div(dvec4_simd v1, dvec4_simd v2) -> dvec4_simd {
    return _mm256_div_pd(v1, v2);
}
#endif
} // namespace xme