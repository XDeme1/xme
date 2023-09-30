#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

constexpr bool isError(bool b) { return b == false; }

template<std::floating_point T>
constexpr bool floatEqual(T lhs, T rhs) { return std::abs(lhs - rhs) <= std::numeric_limits<T>::epsilon(); }