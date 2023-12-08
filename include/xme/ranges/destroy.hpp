#pragma once
#include <iterator>

namespace xme::ranges {
namespace detail {
template<typename Alloc, typename T>
concept CAllocatorDestroy = requires(Alloc a, T ptr) {
    { a.destroy(std::addressof(*ptr)) };
};
}  // namespace detail
template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent, typename Alloc>
constexpr void destroy_a(Iter first, Sent last, Alloc& alloc) noexcept {
    using traits = std::allocator_traits<Alloc>;
    if constexpr(!detail::CAllocatorDestroy<Alloc, typename traits::pointer>) {}
    for(; first != last; ++first) {
        traits::destroy(alloc, std::addressof(*first));
    }
}
}  // namespace xme::ranges
