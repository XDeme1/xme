#pragma once
#include <concepts>

namespace xme {
template<typename T, typename U>
concept CDifferentFrom = !std::is_same_v<T, U>;
}