#pragma once
#include <xme/ranges/swap.hpp>

namespace xme {
template<typename T>
concept swappable_c = requires(T& a, T& b) { ranges::swap(a, b); };

template<typename T, typename U>
concept swappable_with_c = requires(T& t, U& u) {
    ranges::swap(std::forward<T>(t), std::forward<U>(u));
    ranges::swap(std::forward<U>(u), std::forward<T>(t));
    ranges::swap(std::forward<T>(t), std::forward<T>(t));
    ranges::swap(std::forward<U>(u), std::forward<U>(u));
};
}  // namespace xme
