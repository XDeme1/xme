#pragma once
#include <bit>
#include <x86intrin.h>
#include <xme/setup.hpp>
#include <xme/hal/simd_detection.hpp>
#include <range/v3/range.hpp>
#include <range/v3/algorithm.hpp>

namespace xme {
namespace detail {
template<std::size_t size>
XME_INLINE auto find_simd(const void* data, const void* const value) {
#if XME_SIMD_USE_AVX2
    if constexpr(size == 1) {
        const __m256i needle     = _mm256_set1_epi8(*(std::int8_t*)value);
        const __m256i comp       = _mm256_cmpeq_epi8(*(__m256i*)data, needle);
        const std::uint32_t mask = _mm256_movemask_epi8(comp);
        return std::countr_zero(mask);
    }
    else if constexpr(size == 2) {
        const __m256i needle     = _mm256_set1_epi16(*(std::int16_t*)value);
        const __m256i comp       = _mm256_cmpeq_epi16(*(__m256i*)data, needle);
        const std::uint32_t mask = _mm256_movemask_epi8(comp);
        return std::countr_zero(mask) >> 1;
    }
    else if constexpr(size == 4) {
        const __m256i needle    = _mm256_set1_epi32(*(std::int32_t*)value);
        const __m256i comp      = _mm256_cmpeq_epi32(*(__m256i*)data, needle);
        const std::uint8_t mask = _mm256_movemask_ps(*(__m256*)&comp);
        return std::countr_zero(mask);
    }
    else if constexpr(size == 8) {
        const __m256i needle    = _mm256_set1_epi64x(*(std::int64_t*)value);
        const __m256i comp      = _mm256_cmpeq_epi64(*(__m256i*)data, needle);
        const std::uint8_t mask = _mm256_movemask_pd(*(__m256d*)&comp);
        return mask == 0 ? 4 : std::countr_zero(mask);
    }
    else
#elif XME_SIMD_USE_SSE2
    if constexpr(size == 1) {
        const __m128i needle     = _mm_set1_epi8(*(std::int8_t*)value);
        const __m128i comp       = _mm_cmpeq_epi8(*(__m128i*)data, needle);
        const std::uint16_t mask = _mm_movemask_epi8(comp);
        return std::countr_zero(mask);
    }
    else if constexpr(size == 2) {
        const __m128i needle     = _mm_set1_epi16(*(std::int16_t*)value);
        const __m128i comp       = _mm_cmpeq_epi16(*(__m128i*)data, needle);
        const std::uint16_t mask = _mm_movemask_epi8(comp);
        return std::countr_zero(mask) >> 1;
    }
    else if constexpr(size == 4) {
        const __m128i needle    = _mm_set1_epi32(*(std::int32_t*)value);
        const __m128i comp      = _mm_cmpeq_epi32(*(__m128i*)data, needle);
        const std::uint8_t mask = _mm_movemask_ps(*(__m128*)&comp);
        return mask == 0 ? 4 : std::countr_zero(mask);
    }
    else if constexpr(size == 8) {
        const __m128i needle    = _mm_set1_epi64x(*(std::int64_t*)value);
        const __m128i comp      = _mm_cmpeq_epi64(*(__m128i*)data, needle);
        const std::uint8_t mask = _mm_movemask_pd(*(__m128d*)&comp);
        return mask == 0 ? 2 : std::countr_zero(mask);
    }
    else
#endif
        static_assert(size < 0);
}
}  // namespace detail

template<::ranges::input_iterator I, ::ranges::sentinel_for<I> S>
XME_INLINE constexpr auto find(I i, S s, const ::ranges::iter_value_t<I>& value) {
#if XME_SIMD_USE_AVX2 || XME_SIMD_USE_SSE2
    using T = ::ranges::iter_value_t<I>;

    constexpr auto readable_bytes = (XME_SIMD_USE_AVX2 ? 32 : 16) / sizeof(T);
    if constexpr(::ranges::contiguous_iterator<I>) {
        static_assert(sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8);
        auto compare = i;
        while(compare + readable_bytes <= s) {
            const auto index = detail::find_simd<sizeof(T)>(std::to_address(compare), &value);
            if(index != readable_bytes)
                return i + ((compare + index) - i);
            compare += readable_bytes;
        }

        while(compare != s && *compare != value)
            ++compare;

        return compare;
    }
    else
        return ::ranges::find(i, s, value);
#else
    return ::ranges::find(i, s, value);
#endif
}
template<::ranges::input_range R>
XME_INLINE constexpr auto find(R&& range, const ::ranges::range_value_t<R>& value) noexcept {
    return xme::find(::ranges::begin(range), ::ranges::end(range), value);
}
}  // namespace xme