#pragma once
#include <xme/core/concepts/same_as.hpp>
#include <xme/core/concepts/boolean_testable.hpp>

namespace xme {
namespace detail {
template<typename T, typename U>
concept weakly_equality_comparable_with_c =
  requires(const std::remove_reference_t<T>& t, const std::remove_reference_t<U>& u) {
      { t == u } -> boolean_testable_c;
      { t != u } -> boolean_testable_c;
      { u == t } -> boolean_testable_c;
      { u != t } -> boolean_testable_c;
  };

template<typename T, typename U, typename C = std::common_reference_t<const T&, const U&>>
concept comparison_common_type_with_impl_c =
  same_as_c<std::common_reference_t<const T&, const U&>,
            std::common_reference_t<const U&, const T&>>
  && requires {
         requires convertible_to_c<const T&, const C&> || convertible_to_c<T, const C&>;
         requires convertible_to_c<const U&, const C&> || convertible_to_c<U, const C&>;
     };

template<typename T, typename U>
concept comparison_common_type_with_c =
  comparison_common_type_with_impl_c<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
}  // namespace detail

template<typename T>
concept equality_comparable_c = detail::weakly_equality_comparable_with_c<T, T>;

template<typename T, typename U>
concept equality_comparable_with_c =
  equality_comparable_c<T> && equality_comparable_c<U>
  && detail::comparison_common_type_with_c<T, U>
  && equality_comparable_c<
    std::common_reference_t<const std::remove_reference_t<T>&, const std::remove_reference_t<U>>>
  && detail::weakly_equality_comparable_with_c<T, U>;
}  // namespace xme
