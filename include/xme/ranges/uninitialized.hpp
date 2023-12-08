#pragma once
#include <iterator>
#include <xme/container/pair.hpp>

namespace xme::ranges {
namespace detail {
template<typename Alloc, typename T, typename... Args>
concept CTrivialAllocator = !requires(Alloc a, T ptr, Args&&... args) {
    { a.construct(ptr, std::forward<Args>(args)...) };
} || !requires(Alloc a, T ptr) {
    { a.destroy(ptr) };
};

struct UninitializedCopyA {
    template<
        std::forward_iterator InIter,
        std::sentinel_for<InIter> InSent,
        std::forward_iterator OutIter,
        std::sentinel_for<OutIter> OutSent,
        typename Alloc>
    constexpr auto operator()(
        InIter in_first,
        InSent in_last,
        OutIter out_first,
        OutSent out_last,
        Alloc& allocator
    ) const -> xme::Pair<InIter, OutIter> {
        InIter curr  = in_first;
        using traits = std::allocator_traits<Alloc>;
        using ptr_t  = decltype(std::addressof(*curr));
        if constexpr(CTrivialAllocator<Alloc, ptr_t, decltype(*out_first)>) {}
        try {
            for(; curr != in_last && out_first != out_last; ++curr, (void)++out_first) {
                traits::construct(allocator, std::addressof(*curr), *out_first);
            }
        }
        catch(...) {
            for(; in_first != curr; ++in_first) {
                traits::destroy(allocator, std::addressof(*in_first));
            }
            throw;
        }
        return {curr, out_first};
    }
};
struct UninitializedFillNA {
    template<std::forward_iterator Iter, typename T, typename Alloc>
    constexpr auto
    operator()(Iter first, std::size_t n, const T& value, Alloc& allocator) const -> Iter {
        Iter curr    = first;
        using traits = std::allocator_traits<Alloc>;
        try {
            for(; n > 0; --n, (void)++curr) {
                traits::construct(allocator, std::addressof(*curr), value);
            }
        }
        catch(...) {
            for(; first != curr; ++first) {
                traits::destroy(allocator, std::addressof(*first));
            }
            throw;
        }
        return curr;
    }
};
}  // namespace detail

inline constexpr detail::UninitializedCopyA uninitialized_copy_a;
inline constexpr detail::UninitializedFillNA uninitialized_fill_n_a;
}  // namespace xme::ranges
