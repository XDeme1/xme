#pragma once
#include <type_traits>
#include <xme/core/concepts/destructible.hpp>
#include <xme/core/concepts/convertible.hpp>

namespace xme {
template<typename T, typename... Args>
concept constructible_from_c = destructible_c<T> && std::is_constructible_v<T, Args...>;

template<typename T>
concept default_initializable_c = constructible_from_c<T> && requires {
    T{};
    ::new T;
};

template<typename T>
concept move_constructible_c = std::is_constructible_v<T, T> && convertible_to_c<T, T>;

template<typename T>
concept copy_constructible_c =
  move_constructible_c<T> && constructible_from_c<T, T&> && convertible_to_c<T&, T>
  && constructible_from_c<T, const T&> && convertible_to_c<const T&, T>
  && constructible_from_c<T, const T> && convertible_to_c<const T, T>;
}  // namespace xme
