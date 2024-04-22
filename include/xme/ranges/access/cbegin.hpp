// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include <xme/core/iterators/const_iterator.hpp>
#include "end.hpp"

namespace xme::ranges {
namespace detail {
template<typename T>
concept CConstantRange =
  std::ranges::input_range<T> && ::xme::CConstantIterator<detail::iterator_t<T>>;

template<typename T>
constexpr auto possibly_const_range(T& t) noexcept -> auto& {
    if constexpr(CConstantRange<const T> && !CConstantRange<T>)
        return const_cast<const T&>(t);
    else
        return t;
}
}  // namespace detail

struct {
    template<detail::basic_borrowed_range T>
    constexpr auto operator()(T&& t) const noexcept {
        return xme::make_const_iterator(ranges::begin(detail::possibly_const_range(t)));
    }
} inline constexpr cbegin;
}  // namespace xme::ranges