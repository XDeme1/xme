#pragma once
#include <type_traits>
#include <xme/core/concepts/destructible.hpp>
#include <xme/core/concepts/convertible.hpp>

namespace xme {
template<typename T, typename... Args>
concept CConstructibleFrom = CDestructible<T> && std::is_constructible_v<T, Args...>;

template<typename T>
concept CDefaultInitializable = CConstructibleFrom<T> && requires {
    T{};
    ::new T;
};

template<typename T>
concept CMoveConstructible = std::is_constructible_v<T, T> && CConvertibleTo<T, T>;

template<typename T>
concept CCopyConstructible =
  CMoveConstructible<T> && CConstructibleFrom<T, T&> && CConvertibleTo<T&, T>
  && CConstructibleFrom<T, const T&> && CConvertibleTo<const T&, T>
  && CConstructibleFrom<T, const T> && CConvertibleTo<const T, T>;
}  // namespace xme
