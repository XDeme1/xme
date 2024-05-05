#pragma once
#include "range/v3/range/concepts.hpp"
#include <cstdint>
#include <immintrin.h>
#include <x86intrin.h>
#include <xme/setup.hpp>
#include <xme/hal/simd_detection.hpp>
#include <range/v3/range.hpp>
#include <range/v3/algorithm.hpp>

namespace xme {
namespace detail {
#define SEQ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
inline const __m128i shuffle = _mm_set_epi8(SEQ);

template<std::size_t size>
XME_INLINE void reverse_simd(void* lhs, void* rhs) {
#if XME_SIMD_USE_AVX2
    if constexpr(size == 1) {
        const __m256i shuf = _mm256_set_epi8(SEQ, SEQ);
        __m256i lower      = _mm256_loadu_si256((__m256i*)lhs);
        __m256i upper      = _mm256_loadu_si256((__m256i*)((std::int8_t*)rhs - 32));
        lower              = _mm256_shuffle_epi8(lower, shuf);
        upper              = _mm256_shuffle_epi8(upper, shuf);
        lower              = _mm256_permute2x128_si256(lower, lower, 1);
        upper              = _mm256_permute2x128_si256(upper, upper, 1);
        _mm256_storeu_si256((__m256i*)(std::int8_t*)lhs, upper);
        _mm256_storeu_si256((__m256i*)((std::int8_t*)rhs - 32), lower);
    }
    else
#elif XME_SIMD_USE_SSE3
    if constexpr(size == 1) {
        __m128i lower = _mm_loadu_si128((__m128i*)lhs);
        __m128i upper = _mm_loadu_si128((__m128i*)((std::int8_t*)rhs - 16));
        lower         = _mm_shuffle_epi8(lower, shuffle);
        upper         = _mm_shuffle_epi8(upper, shuffle);
        _mm_storeu_si128((__m128i_u*)(std::int8_t*)lhs, upper);
        _mm_storeu_si128((__m128i_u*)((std::int8_t*)rhs - 16), lower);
    }
    else if constexpr(size == 2) {}
    else
#endif
        static_assert(size < 0);
}
}  // namespace detail

template<::ranges::input_iterator I, ::ranges::sentinel_for<I> S>
XME_INLINE constexpr auto reverse(I i, S s) noexcept {
#if XME_SIMD_USE_AVX2 || XME_SIMD_USE_SSE3
    using T = ::ranges::iter_value_t<I>;

    if constexpr(::ranges::contiguous_iterator<I>) {
        static_assert(sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8);
        constexpr auto readable_bytes = (XME_SIMD_USE_AVX2 ? 32 : 16) / sizeof(T);
        auto count                    = ((s - i) / 2) / readable_bytes;
        const auto end                = s;
        while(count--) {
            detail::reverse_simd<sizeof(T)>(std::to_address(i), std::to_address(s));
            i += readable_bytes;
            s -= readable_bytes;
        }
        while(i < s)
            ::ranges::iter_swap(i++, --s);
        return end;
    }
    else
        return ::ranges::reverse(i, s);
#else
    return ::ranges::reverse(i, s);
#endif
}
template<::ranges::input_range R>
XME_INLINE constexpr auto reverse(R&& range) noexcept {
    return xme::reverse(::ranges::begin(range), ::ranges::end(range));
}
}  // namespace xme