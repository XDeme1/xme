#pragma once
#include <xme/core/concepts/constructible.hpp>
#include <xme/core/concepts/assignable.hpp>
#include <xme/core/concepts/swappable.hpp>
#include <xme/core/concepts/equality_comparable.hpp>

namespace xme {
template<typename T>
concept movable_c =
  std::is_object_v<T> && move_constructible_c<T> && assignable_from_c<T&, T> && swappable_c<T>;

template<typename T>
concept copyable_c = copy_constructible_c<T> && movable_c<T> && assignable_from_c<T&, T&>
                     && assignable_from_c<T&, const T&> && assignable_from_c<T&, const T>;

template<typename T>
concept semiregular_c = copyable_c<T> && default_initializable_c<T>;

template<typename T>
concept regular_c = semiregular_c<T> && equality_comparable_c<T>;
}  // namespace xme
