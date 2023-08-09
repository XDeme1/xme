#pragma once
#include "forward.hpp"
#include <concepts>

namespace xme {
template<typename T>
concept CArithmetic = std::floating_point<T> || std::integral<T>;
}