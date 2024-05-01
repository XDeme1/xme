#pragma once
#include <iterator>
#include <memory>
#include <range/v3/range.hpp>

namespace xme::ranges {
struct {
    template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent, typename Alloc>
    constexpr void operator()(Iter first, Sent last, Alloc& alloc) const noexcept {
        for(; first != last; ++first)
            std::allocator_traits<Alloc>::destroy(alloc, std::addressof(*first));
    }

    template<::ranges::forward_range R, typename Alloc>
    constexpr void operator()(R&& range, Alloc& alloc) const noexcept {
        (*this)(::ranges::begin(range), ::ranges::end(range), alloc);
    }
} inline constexpr destroy_a;

struct {
    template<std::destructible T, typename Alloc>
    constexpr void operator()(T* pos, Alloc& alloc) const noexcept {
        if constexpr(std::is_array_v<T>)
            ranges::destroy_a(::ranges::begin(*pos), ::ranges::end(*pos), alloc);
        else
            std::allocator_traits<Alloc>::destroy(alloc, pos);
    }
} inline constexpr destroy_at_a;

struct {
    template<std::forward_iterator Iter, typename Alloc>
    constexpr void operator()(Iter first, std::iter_difference_t<Iter> n,
                              Alloc& alloc) const noexcept {
        for(; n > 0; ++first, (void)--n) {
            ranges::destroy_at_a(std::addressof(*first), alloc);
        }
    }
} inline constexpr destroy_n_a;

}  // namespace xme::ranges
