// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include "begin.hpp"
#include <type_traits>

namespace xme::ranges {
namespace detail {
template<typename T>
using iterator_t = decltype(ranges::begin(std::declval<T&>()));

template<typename T>
concept member_end = requires(T& t) {
    { decay_copy(t.end()) } -> std::sentinel_for<iterator_t<T>>;
};

template<typename T>
concept adl_end = requires(T& t) {
    { decay_copy(end(t)) } -> std::sentinel_for<iterator_t<T>>;
};
}  // namespace detail

struct {
    template<detail::basic_borrowed_range T>
        requires std::is_bounded_array_v<std::remove_reference_t<T>> || detail::member_end<T>
                 || detail::adl_end<T>
    constexpr auto operator()(T&& t) const noexcept {
        if constexpr(std::is_bounded_array_v<std::remove_reference_t<T>>)
            return t + std::extent_v<std::remove_reference_t<T>>;
        else if constexpr(detail::member_end<T>)
            return t.end();
        else
            return end(t);
    }
} inline constexpr end;

}  // namespace xme::ranges