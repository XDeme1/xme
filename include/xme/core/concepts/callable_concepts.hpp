#pragma once
#include <type_traits>
#include <xme/core/concepts/boolean_testable.hpp>

namespace xme {
template<typename F, typename... Args>
concept invocable_c = std::is_invocable_v<F, Args...>;

template<typename F, typename... Args>
concept regular_invocable_c = invocable_c<F, Args...>;

template<typename F, typename... Args>
concept predicate_c =
  regular_invocable_c<F, Args...> && boolean_testable_c<std::invoke_result_t<F, Args...>>;

template<typename R, typename T, typename U>
concept relation_c =
  predicate_c<R, T, T> && predicate_c<R, U, U> && predicate_c<R, T, U> && predicate_c<R, U, T>;

template<typename R, typename T, typename U>
concept equivalence_relation = relation_c<R, T, U>;

template<typename R, typename T, typename U>
concept strict_weak_order = relation_c<R, T, U>;
}  // namespace xme
