#pragma once
#include <xme/container/pair.hpp>

namespace xme {
template<typename T>
constexpr auto min(const T& lhs, const T& rhs) noexcept -> const T& {
    if (lhs < rhs)
        return lhs;
    return rhs;
}

template<typename T, typename Cmp>
constexpr auto min(const T& lhs, const T& rhs, Cmp cmp) noexcept -> const T& {
    if (cmp(lhs, rhs))
        return lhs;
    return rhs;
}

template<typename T>
constexpr auto max(const T& lhs, const T& rhs) noexcept -> const T& {
    if (lhs < rhs)
        return rhs;
    return lhs;
}

template<typename T, typename Cmp>
constexpr auto max(const T& lhs, const T& rhs, Cmp cmp) noexcept -> const T& {
    if (cmp(lhs, rhs))
        return rhs;
    return lhs;
}

template<typename T>
constexpr auto minmax(const T& lhs, const T& rhs) noexcept -> Pair<const T&, const T&> {
    if (lhs < rhs)
        return {lhs, rhs};
    return {rhs, lhs};
}

template<typename T, typename Cmp>
constexpr auto minmax(const T& lhs, const T& rhs, Cmp cmp) noexcept
    -> Pair<const T&, const T&> {
    if (cmp(lhs, rhs))
        return {lhs, rhs};
    return {rhs, lhs};
}
} // namespace xme