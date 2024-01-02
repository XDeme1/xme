#pragma once
#include <type_traits>
#include <xme/core/concepts/boolean_testable.hpp>

namespace xme {
template<typename F, typename... Args>
concept CInvocable = std::is_invocable_v<F, Args...>;

template<typename F, typename... Args>
concept CRegularInvocable = CInvocable<F, Args...>;

template<typename F, typename... Args>
concept CPredicate =
  CRegularInvocable<F, Args...> && boolean_testable_c<std::invoke_result_t<F, Args...>>;

template<typename R, typename T, typename U>
concept CRelation =
  CPredicate<R, T, T> && CPredicate<R, U, U> && CPredicate<R, T, U> && CPredicate<R, U, T>;

template<typename R, typename T, typename U>
concept CEquivalenceRelation = CRelation<R, T, U>;

template<typename R, typename T, typename U>
concept CStrictWeakOrder = CRelation<R, T, U>;
}  // namespace xme
