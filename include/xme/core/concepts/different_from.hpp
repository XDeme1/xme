#pragma once
#include <concepts>

namespace xme {
template<typename T, typename U>
concept CDifferentFrom = !std::same_as<T, U>;
}  // namespace xme