#pragma once
#include <type_traits>

namespace xme {
template<typename T>
concept CDestructible = std::is_nothrow_destructible_v<T>;
}  // namespace xme
