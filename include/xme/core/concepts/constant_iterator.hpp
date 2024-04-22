#pragma once
#include <concepts>
#include <iterator>
#include "xme/core/iterators/iterator_traits.hpp"

namespace xme {
template<typename T>
concept CConstantIterator =
  std::input_iterator<T> && std::same_as<iter_const_reference_t<T>, std::iter_reference_t<T>>;
}  // namespace xme