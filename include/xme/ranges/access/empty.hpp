// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include "size.hpp"
#include <iterator>

namespace xme::ranges {
namespace detail {
template<typename T>
concept member_empty = requires(T& t) { bool(t.empty()); };

template<typename T>
concept size0_empty = requires(T& t) { (ranges::size(t) == 0); };

template<typename T>
concept ranges_empty = requires(T& t) {
    { ranges::begin(t) } -> std::forward_iterator;
    bool(ranges::begin(t) == ranges::end);
};
}  // namespace detail

struct {
    template<typename T>
        requires detail::member_empty<T> || detail::size0_empty<T> || detail::ranges_empty<T>
    constexpr bool operator()(T&& t) const noexcept {
        if constexpr(detail::member_empty<T>)
            return bool(t.empty());
        else if constexpr(detail::size0_empty<T>)
            return ranges::size(t) == 0;
        else
            return bool(ranges::begin(t) == ranges::end(t));
    }
} inline constexpr empty;
}  // namespace xme::ranges