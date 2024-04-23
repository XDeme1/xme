#pragma once
#include <concepts>
#include <ranges>
#include <utility>

namespace xme::ranges {
#ifndef __cpp_lib_concepts
class view_base {};

template<typename T>
class IView;
template<typename T>
using view_interface = IView<T>;

template<typename T, typename U>
    requires std::is_convertible_v<T*, view_interface<U>*>
void is_derived_from_view_interface(const T*, const view_interface<U>*);

template<typename T>
inline constexpr bool disable_sized_range = false;
template<typename T>
inline constexpr bool enable_borrowed_range = false;
template<typename T>
inline constexpr bool enable_view = std::derived_from<T, ranges::view_base> || requires {
    is_derived_from_view_interface((T*)nullptr, (T*)nullptr);
};
#else
using std::ranges::disable_sized_range;
using std::ranges::enable_borrowed_range;
using std::ranges::enable_view;
using std::ranges::view_base;
using std::ranges::view_interface;
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