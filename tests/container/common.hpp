#pragma once

#include <xme/container/linked_list.hpp>
#include <xme/container/spsc_queue.hpp>
#include <xme/container/array.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

constexpr bool isError(bool b) { return b == false; }

template<std::floating_point T>
constexpr bool floatEqual(T lhs, T rhs) { return std::abs(lhs - rhs) <= std::numeric_limits<T>::epsilon(); }