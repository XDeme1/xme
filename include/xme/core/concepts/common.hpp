#pragma once
#include <type_traits>
#include <xme/core/concepts/same_as.hpp>
#include <xme/core/concepts/convertible.hpp>

namespace xme {
template<typename T, typename U>
concept common_reference_with =
  same_as<std::common_reference_t<T, U>, std::common_reference_t<U, T>>
  && convertible_to<T, std::common_reference_t<T, U>>
  && convertible_to<U, std::common_reference_t<T, U>>;

template<typename T, typename U>
concept common_with = same_as<std::common_type_t<T, U>, std::common_type_t<U, T>> && requires {
    static_cast<std::common_type_t<T, U>>(std::declval<T>());
    static_cast<std::common_type_t<T, U>>(std::declval<U>());
} && common_reference_with<std::add_lvalue_reference_t<const T>, std::add_lvalue_reference_t<const U>> && common_reference_with<std::add_lvalue_reference_t<std::common_type_t<T, U>>, std::common_reference_t<std::add_lvalue_reference_t<const T>, std::add_lvalue_reference_t<U>>>;
}  // namespace xme
