#pragma once

#include <xme/math/math.hpp>
#include <algorithm>
#include <iostream>

constexpr bool isError(bool b) { return b == false; }

template<std::floating_point T>
constexpr bool floatEqual(T lhs, T rhs) { return std::abs(lhs - rhs) <= std::numeric_limits<T>::epsilon(); }