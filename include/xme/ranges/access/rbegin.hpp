// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include "xme/core/iterators/reverse_iterator.hpp"
#include <xme/ranges/access/end.hpp>

namespace xme::ranges {
namespace detail {
template<typename T>
concept member_rbegin = requires(T& t) {
    { decay_copy(t.rbegin()) } -> std::input_or_output_iterator;
};

template<typename T>
concept adl_rbegin = requires(T& t) {
    { decay_copy(rbegin(t)) } -> std::input_or_output_iterator;
};

template<typename T>
concept reversable = requires(T& t) {
    { ranges::begin(t) } -> std::bidirectional_iterator;
    { ranges::end(t) } -> std::same_as<decltype(ranges::begin(t))>;
};
}  // namespace detail

struct {
    template<detail::basic_borrowed_range T>
        requires detail::member_rbegin<T> || detail::adl_rbegin<T> || detail::reversable<T>
    constexpr auto operator()(T&& t) const noexcept {
        if constexpr(detail::member_rbegin<T>)
            return t.rbegin();
        else if constexpr(detail::adl_rbegin<T>)
            return rbegin(t);
        else
            return ReverseIterator(ranges::end(t));
    }
} inline constexpr rbegin;
}  // namespace xme::ranges