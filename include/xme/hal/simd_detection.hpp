#pragma once

#ifdef __MMX__
#define XME_SIMD_MMX true
#else
#define XME_SIMD_MMX false
#endif

#ifdef __SSE__
#define XME_SIMD_SSE true
#else
#define XME_SIMD_SSE false
#endif

#ifdef __SSE2__
#define XME_SIMD_SSE2 true
#else
#define XME_SIMD_SSE2 false
#endif

#ifdef __SSE3__
#define XME_SIMD_SSE3 true
#else
#define XME_SIMD_SSE3 false
#endif

#ifdef __SSSE3__
#define XME_SIMD_SSSE3 true
#else
#define XME_SIMD_SSSE3 false
#endif

#if defined(__SSE4_1__) || defined(__SSE4_2__)
#define XME_SIMD_SSE4 true
#else
#define XME_SIMD_SSE4 false
#endif

#ifdef __AVX__
#define XME_SIMD_AVX true
#else
#define XME_SIMD_AVX false
#endif

#ifdef __AVX2__
#define XME_SIMD_AVX2 true
#else
#define XME_SIMD_AVX2 false
#endif
