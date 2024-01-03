#pragma once
#include <limits>
#include <xme/setup.hpp>
#include <xme/core/concepts/arithmetic.hpp>

namespace xme::math {
//! Returns the sign of the number.
//! returns -1 if negative, 0 if 0, 1 if positive
template<typename T>
    requires CSignedIntegral<T> || std::numeric_limits<T>::is_iec559
[[nodiscard]]
XME_INLINE constexpr auto sign(T n) noexcept -> T {
    return (T(0) < n) - (n < T(0));
}
}  // namespace xme::math