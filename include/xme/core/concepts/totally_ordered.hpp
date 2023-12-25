#pragma once
#include <xme/core/concepts/equality_comparable.hpp>

namespace xme {
namespace detail {
template<typename T, typename U>
concept partially_ordered_with_c =
  requires(const std::remove_reference_t<T>& t, const std::remove_reference_t<U>& u) {
      { t < u } -> boolean_testable_c;
      { t > u } -> boolean_testable_c;
      { t <= u } -> boolean_testable_c;
      { t >= u } -> boolean_testable_c;
      { u < t } -> boolean_testable_c;
      { u > t } -> boolean_testable_c;
      { u <= t } -> boolean_testable_c;
      { u >= t } -> boolean_testable_c;
  };
}  // namespace detail

template<typename T>
concept totally_ordered_c = equality_comparable_c<T> && detail::partially_ordered_with_c<T, T>;

template<typename T, typename U>
concept totally_ordered_with_c =
  totally_ordered_c<T> && totally_ordered_c<U> && equality_comparable_with_c<T, U>
  && totally_ordered_c<
    std::common_reference_t<const std::remove_reference_t<T>&, const std::remove_reference_t<U>&>>
  && detail::partially_ordered_with_c<T, U>;
}  // namespace xme
