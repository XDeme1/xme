#pragma once
#include <type_traits>
#include <utility>

namespace xme {
template<typename LHS, typename RHS>
concept assignable_from = std::is_lvalue_reference_v<LHS> && requires(LHS lhs, RHS&& rhs) {
    { lhs = std::forward<RHS>(rhs) } -> std::same_as<LHS>;
};
}  // namespace xme
