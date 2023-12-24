#pragma once
#include <type_traits>
#include <xme/core/concepts/destructible.hpp>
#include <xme/core/concepts/convertible.hpp>

namespace xme {
template<typename T, typename... Args>
concept constructible_from = destructible<T> && std::is_constructible_v<T, Args...>;

template<typename T>
concept default_initializable = constructible_from<T> && requires {
    T{};
    ::new T;
};

template<typename T>
concept move_constructible = std::is_constructible_v<T, T> && convertible_to<T, T>;

template<typename T>
concept copy_constructible =
  move_constructible<T> && constructible_from<T, T&> && convertible_to<T&, T>
  && constructible_from<T, const T&> && convertible_to<const T&, T>
  && constructible_from<T, const T> && convertible_to<const T, T>;
}  // namespace xme
