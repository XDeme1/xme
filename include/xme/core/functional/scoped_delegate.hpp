#pragma once
#include <utility>
#include <xme/setup.hpp>

#if defined(__cpp_concepts)
#include <concepts>
#endif

namespace xme {
//! @brief Calls a function at the end of this object scope
//!
//! The function called must not throw an exception and cannot have parameters
template<XME_CONCEPT(std::invocable, F)>
class ScopedDelegate {
public:
    constexpr ScopedDelegate(F& func) noexcept : m_callable(func) {}

    constexpr ScopedDelegate(F&& func) noexcept : m_callable(std::move(func)) {}

    constexpr ~ScopedDelegate() noexcept { m_callable(); }

    constexpr auto operator=(const ScopedDelegate&) = delete;

    constexpr auto operator=(ScopedDelegate&&) = delete;

private:
    [[no_unique_address]] F m_callable;
};
}  // namespace xme
