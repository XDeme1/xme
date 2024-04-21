#pragma once
#include <iterator>
#include <ranges>
#include <utility>

namespace xme::ranges {
template<typename R>
using range_size_t = decltype(std::ranges::size(std::declval<R&>()));

template<typename R>
using range_difference_t = std::iter_difference_t<std::ranges::iterator_t<R>>;
}  // namespace xme::ranges