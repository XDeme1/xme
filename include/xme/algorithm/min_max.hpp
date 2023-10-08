#pragma once
#include <xme/container/pair.hpp>

namespace xme {
template<typename T>
constexpr auto min(const T& lhs, const T& rhs) noexcept -> const T& {
    if (lhs < rhs)
        return lhs;
    return rhs;
}

template<typename T>
constexpr auto max(const T& lhs, const T& rhs) noexcept -> const T& {
    if (lhs > rhs)
        return lhs;
    return rhs;
}

template<typename T>
constexpr auto minmax(const T& lhs, const T& rhs) noexcept
    -> const Pair<const T&, const T&> {
    if (lhs < rhs)
        return {lhs, rhs};
    return {rhs, lhs};
}
} // namespace xme