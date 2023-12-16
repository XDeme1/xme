#pragma once
#include "destroy.hpp"
#include <iterator>
#include <xme/container/concepts.hpp>
#include <xme/container/pair.hpp>

namespace xme::ranges {
namespace detail {
struct UninitializedCopyA {
    template<std::forward_iterator InIter, std::sentinel_for<InIter> InSent,
             std::forward_iterator OutIter, std::sentinel_for<OutIter> OutSent, typename Alloc>
    constexpr auto operator()(InIter in_first, InSent in_last, OutIter out_first, OutSent out_last,
                              Alloc& alloc) const -> xme::Pair<InIter, OutIter> {
        OutIter out_curr = out_first;
        using traits     = std::allocator_traits<Alloc>;
        try {
            for(; in_first != in_last && out_curr != out_last; ++out_curr, (void)++in_first) {
                traits::construct(alloc, std::addressof(*out_curr), *in_first);
            }
        }
        catch(...) {
            ranges::destroy_a(in_first, out_curr, alloc);
            throw;
        }
        return {in_first, out_curr};
    }
};
struct UninitializedFillNA {
    template<std::forward_iterator Iter, typename T, typename Alloc>
    constexpr auto operator()(Iter first, std::size_t n, const T& value,
                              Alloc& allocator) const -> Iter {
        Iter curr    = first;
        using traits = std::allocator_traits<Alloc>;
        try {
            for(; n > 0; --n, (void)++curr) {
                traits::construct(allocator, std::addressof(*curr), value);
            }
        }
        catch(...) {
            ranges::destroy_a(first, curr, allocator);
            throw;
        }
        return curr;
    }
};
}  // namespace detail

inline constexpr detail::UninitializedCopyA uninitialized_copy_a;
inline constexpr detail::UninitializedFillNA uninitialized_fill_n_a;
}  // namespace xme::ranges
