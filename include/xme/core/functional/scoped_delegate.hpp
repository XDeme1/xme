#pragma once
#include <utility>
#include <concepts>
#include <xme/setup.hpp>

namespace xme {
//! @brief Calls a function at the end of this object scope
//!
//! The function called must not throw an exception and cannot have parameters
template<std::invocable F>
class ScopedDelegate {
public:
    XME_INLINE constexpr ScopedDelegate(F& func) noexcept : m_callable(func) {}

    XME_INLINE constexpr ScopedDelegate(F&& func) noexcept : m_callable(std::move(func)) {}

    XME_INLINE constexpr ~ScopedDelegate() noexcept { m_callable(); }

    constexpr auto operator=(const ScopedDelegate&) = delete;

    constexpr auto operator=(ScopedDelegate&&) = delete;

private:
    [[no_unique_address]]
    F m_callable;
};
}  // namespace xme
