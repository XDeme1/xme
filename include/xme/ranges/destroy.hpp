#pragma once
#include <iterator>
#include <memory>

namespace xme::ranges {
namespace detail {
struct DestroyA {
    template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent, typename Alloc>
    constexpr void operator()(Iter first, Sent last, Alloc& alloc) const noexcept {
        using traits = std::allocator_traits<Alloc>;
        for(; first != last; ++first) {
            traits::destroy(alloc, std::addressof(*first));
        }
    }
};
}  // namespace detail

inline constexpr detail::DestroyA destroy_a;

namespace detail {
struct DestroyAtA {
    template<std::destructible T, typename Alloc>
    constexpr void operator()(T* pos, Alloc& alloc) const noexcept {
        using traits = std::allocator_traits<Alloc>;
        if constexpr(std::is_array_v<T>) {
            ranges::destroy_a(std::ranges::begin(*pos), std::ranges::end(*pos), alloc);
        }
        else {
            traits::destroy(alloc, pos);
        }
    }
};
}  // namespace detail

inline constexpr detail::DestroyAtA destroy_at_a;

namespace detail {
struct DestroyNA {
    template<std::forward_iterator Iter, typename Alloc>
    constexpr void operator()(Iter first, std::iter_difference_t<Iter> n,
                              Alloc& alloc) const noexcept {
        for(; n > 0; ++first, (void)--n) {
            ranges::destroy_at_a(std::addressof(*first), alloc);
        }
    }
};
}  // namespace detail

inline constexpr detail::DestroyNA destroy_n_a;

}  // namespace xme::ranges
