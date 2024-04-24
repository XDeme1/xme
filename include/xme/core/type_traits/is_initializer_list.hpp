#pragma once
#include <initializer_list>

namespace xme {
template<typename T>
inline constexpr bool is_initializer_list = false;

template<typename T>
inline constexpr bool is_initializer_list<std::initializer_list<T>> = true;
}  // namespace xme
