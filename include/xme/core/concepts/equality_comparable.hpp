#pragma once
#include <xme/core/concepts/same_as.hpp>
#include <xme/core/concepts/boolean_testable.hpp>

namespace xme {
namespace detail {
template<typename T, typename U>
concept CWeaklyEqualityComparableWith =
  requires(const std::remove_reference_t<T>& t, const std::remove_reference_t<U>& u) {
      { t == u } -> boolean_testable_c;
      { t != u } -> boolean_testable_c;
      { u == t } -> boolean_testable_c;
      { u != t } -> boolean_testable_c;
  };

template<typename T, typename U, typename C = std::common_reference_t<const T&, const U&>>
concept CComparisonCommonTypeWithImpl =
  CSameAs<std::common_reference_t<const T&, const U&>, std::common_reference_t<const U&, const T&>>
  && requires {
         requires CConvertibleTo<const T&, const C&> || CConvertibleTo<T, const C&>;
         requires CConvertibleTo<const U&, const C&> || CConvertibleTo<U, const C&>;
     };

template<typename T, typename U>
concept CComparisonCommonTypeWith =
  CComparisonCommonTypeWithImpl<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
}  // namespace detail

template<typename T>
concept CEqualityComparable = detail::CWeaklyEqualityComparableWith<T, T>;

template<typename T, typename U>
concept CEqualityComparableWith =
  CEqualityComparable<T> && CEqualityComparable<U> && detail::CComparisonCommonTypeWith<T, U>
  && CEqualityComparable<
    std::common_reference_t<const std::remove_reference_t<T>&, const std::remove_reference_t<U>>>
  && detail::CWeaklyEqualityComparableWith<T, U>;
}  // namespace xme
