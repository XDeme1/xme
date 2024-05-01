#pragma once
#include "destroy.hpp"
#include <xme/container/concepts.hpp>
#include <xme/container/pair.hpp>

namespace xme::ranges {
struct {
    template<std::forward_iterator InIter, std::sentinel_for<InIter> InSent,
             std::forward_iterator OutIter, std::sentinel_for<OutIter> OutSent, typename Alloc>
    constexpr auto operator()(InIter in_first, InSent in_last, OutIter out_first, OutSent out_last,
                              Alloc& alloc) const -> xme::Pair<InIter, OutIter> {
        OutIter out_curr = out_first;
        try {
            for(; in_first != in_last && out_curr != out_last; ++out_curr, (void)++in_first) {
                std::allocator_traits<Alloc>::construct(
                  alloc, std::addressof(*out_curr), *in_first);
            }
        }
        catch(...) {
            ranges::destroy_a(in_first, out_curr, alloc);
            throw;
        }
        return {in_first, out_curr};
    }

    template<::ranges::forward_range InR, ::ranges::forward_range OutR, typename Alloc>
    constexpr auto operator()(InR&& in, OutR&& out, Alloc& alloc) const
      -> xme::Pair<std::ranges::borrowed_iterator_t<InR>, std::ranges::borrowed_iterator_t<OutR>> {
        return (*this)(
          ::ranges::begin(in), ::ranges::end(in), ::ranges::begin(out), ::ranges::end(out), alloc);
    }
} inline constexpr uninitialized_copy_a;

struct {
    template<std::forward_iterator Iter, typename T, typename Alloc>
    constexpr auto operator()(Iter first, std::size_t n, const T& value,
                              Alloc& alloc) const -> Iter {
        Iter curr = first;
        try {
            for(; n > 0; --n, (void)++curr) {
                std::allocator_traits<Alloc>::construct(alloc, std::addressof(*curr), value);
            }
        }
        catch(...) {
            ranges::destroy_a(first, curr, alloc);
            throw;
        }
        return curr;
    }
} inline constexpr uninitialized_fill_n_a;
}  // namespace xme::ranges
