#pragma once
#include <concepts>

namespace xme {
template<typename T, typename U>
concept CDifferentFrom = !std::same_as<T, U>;

template<typename T, typename Self>
concept CDifferentFromSelf = !std::same_as<Self, std::remove_cvref_t<T>>;
}  // namespace xme