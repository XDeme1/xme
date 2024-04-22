// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include <type_traits>
#include <xme/ranges/base.hpp>

namespace xme::ranges {
namespace detail {
template<typename T>
concept member_begin = requires(T& t) {
    { decay_copy(t.begin()) } -> std::input_or_output_iterator;
};

template<typename T>
concept adl_begin = requires(T& t) {
    { decay_copy(begin(t)) } -> std::input_or_output_iterator;
};
}  // namespace detail

struct {
    template<detail::basic_borrowed_range T>
        requires std::is_array_v<std::remove_reference_t<T>> || detail::member_begin<T>
                 || detail::adl_begin<T>
    constexpr auto operator()(T&& t) const noexcept {
        if constexpr(std::is_array_v<std::remove_reference_t<T>>)
            return t + 0;
        else if constexpr(detail::member_begin<T>)
            return t.begin();
        else
            return begin(t);
    }
} inline constexpr begin;
}  // namespace xme::ranges