// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include <xme/ranges/access/rbegin.hpp>

namespace xme::ranges {
namespace detail {
template<typename T>
concept member_rend = requires(T& t) {
    { decay_copy(t.rend()) } -> std::input_or_output_iterator;
};

template<typename T>
concept adl_rend = requires(T& t) {
    { decay_copy(rend(t)) } -> std::input_or_output_iterator;
};
}  // namespace detail

struct {
    template<detail::basic_borrowed_range T>
        requires detail::member_rend<T> || detail::adl_rend<T> || detail::reversable<T>
    constexpr auto operator()(T&& t) const noexcept {
        if constexpr(detail::member_rend<T>)
            return t.rend();
        else if constexpr(detail::adl_rend<T>)
            return rend(t);
        else
            return ReverseIterator(ranges::begin(t));
    }
} inline constexpr rend;
}  // namespace xme::ranges