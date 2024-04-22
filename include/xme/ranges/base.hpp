#pragma once
#include <ranges>
#include <utility>

namespace xme::ranges {
#ifndef __cpp_lib_concepts
template<typename T>
inline constexpr bool disable_sized_range = false;
template<typename T>
inline constexpr bool enable_borrowed_range = false;
#else
using std::ranges::disable_sized_range;
using std::ranges::enable_borrowed_range;
#endif

namespace detail {
template<typename T>
constexpr auto decay_copy(T&& t) noexcept -> std::decay_t<T> {
    return std::forward<T>(t);
}

template<typename T>
concept basic_borrowed_range =
  std::is_lvalue_reference_v<T> || enable_borrowed_range<std::remove_cvref_t<T>>;
}  // namespace detail
}  // namespace xme::ranges