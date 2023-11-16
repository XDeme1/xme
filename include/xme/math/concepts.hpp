#pragma once
#include <concepts>

namespace xme::math {
template<typename T>
concept CArithmetic = std::floating_point<T> || std::integral<T>;

template<auto A, auto B>
concept CEqual = A == B;

template<auto A, auto B>
concept CLess = A < B;

template<auto A, auto B>
concept CGreater = A > B;
}  // namespace xme::math
