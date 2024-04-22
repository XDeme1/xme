// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include <iterator>
#include "end.hpp"
#include "xme/core/utility/to_unsigned.hpp"

namespace xme::ranges {
namespace detail {
template<typename T>
concept is_int128 =
#ifdef __sizeof_int128__
  std::same_as<T, signed __int128> || std::same_as<T, unsigned __int128>;
#else
  false;
#endif

template<typename T>
concept integer_like =
  (std::integral<T> && !std::same_as<const volatile T, const volatile bool>) || is_int128<T>;

template<typename T>
concept member_size = !disable_sized_range<std::remove_cvref_t<T>> && requires(T& t) {
    { decay_copy(t.size()) } -> integer_like;
};

template<typename T>
concept adl_size = !disable_sized_range<std::remove_cvref_t<T>> && requires(T& t) {
    { decay_copy(size(t)) } -> integer_like;
};

template<typename T>
concept sized_sentinel = requires(T& t) {
    requires !std::is_unbounded_array_v<std::remove_reference_t<T>>;
    { ranges::begin(t) } -> std::forward_iterator;
    { ranges::end(t) } -> std::sized_sentinel_for<iterator_t<T>>;
    to_unsigned(ranges::end(t) - ranges::begin(t));
};
}  // namespace detail

struct {
    template<typename T>
        requires std::is_bounded_array_v<std::remove_reference_t<T>> || detail::member_size<T>
                 || detail::adl_size<T> || detail::sized_sentinel<T>
    constexpr auto operator()(T&& t) const noexcept {
        if constexpr(std::is_bounded_array_v<std::remove_reference_t<T>>)
            return std::extent_v<std::remove_reference_t<T>>;
        else if constexpr(detail::member_size<T>)
            return t.size();
        else if constexpr(detail::adl_size<T>)
            return size(t);
        else if constexpr(detail::sized_sentinel<T>)
            return to_unsigned(ranges::end(t) - ranges::begin(t));
    }
} inline constexpr size;
}  // namespace xme::ranges