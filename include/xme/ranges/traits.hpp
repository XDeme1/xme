#pragma once
#include "xme/ranges/access.hpp"
#include <iterator>
#include <utility>

namespace xme::ranges {
template<typename R>
using iterator_t = decltype(ranges::begin(std::declval<R&>()));

template<typename R>
using const_iterator_t = decltype(ranges::cbegin(std::declval<R&>()));

template<typename R>
using sentinel_t = decltype(ranges::end(std::declval<R&>()));

template<typename R>
using const_sentinel_t = decltype(ranges::cend(std::declval<R&>()));

template<typename R>
using range_size_t = decltype(ranges::size(std::declval<R&>()));

template<typename R>
using range_difference_t = std::iter_difference_t<ranges::iterator_t<R>>;

template<typename R>
using range_value_t = std::iter_value_t<ranges::iterator_t<R>>;

template<typename R>
using range_reference_t = std::iter_reference_t<ranges::iterator_t<R>>;

// template<typename R>
// using range_const_reference_t = std::iter_const_reference_t<ranges::iterator_t<R>>; // Implement
// later

template<typename R>
using range_rvalue_reference_t = std::iter_rvalue_reference_t<ranges::iterator_t<R>>;

template<typename R>
using range_common_reference_t = std::iter_common_reference_t<ranges::iterator_t<R>>;
}  // namespace xme::ranges