#pragma once
#include <xme/core/concepts/constructible.hpp>
#include <xme/core/concepts/assignable.hpp>
#include <xme/core/concepts/swappable.hpp>

namespace xme {
template<typename T>
concept movable_c =
  std::is_object_v<T> && move_constructible_c<T> && assignable_from_c<T&, T> && swappable_c<T>;
}
