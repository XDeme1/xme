#pragma once
#include <utility>
#include <xme/core/concepts/same_as.hpp>
namespace xme {
template<typename LHS, typename RHS>
concept CAssignableFrom = std::is_lvalue_reference_v<LHS> && requires(LHS lhs, RHS&& rhs) {
    { lhs = std::forward<RHS>(rhs) } -> CSameAs<LHS>;
};
}  // namespace xme
