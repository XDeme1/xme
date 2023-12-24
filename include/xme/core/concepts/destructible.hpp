#pragma once
#include <type_traits>

namespace xme {
template<typename T>
concept destructible = std::is_nothrow_destructible_v<T>;
}  // namespace xme
