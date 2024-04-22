#pragma once
#include "xme/ranges/access.hpp"
#include <iterator>
#include <utility>

namespace xme::ranges {
template<typename R>
using iterator_t = decltype(ranges::begin(std::declval<R&>()));

template<typename R>
using sentinel_t = decltype(ranges::end(std::declval<R&>()));

template<typename R>
using range_size_t = decltype(ranges::size(std::declval<R&>()));

template<typename R>
using range_difference_t = std::iter_difference_t<ranges::iterator_t<R>>;
}  // namespace xme::ranges