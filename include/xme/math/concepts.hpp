#pragma once
#include <concepts>
#include "type_traits.hpp"

namespace xme {
template<typename T>
concept CArithmetic = std::floating_point<T> || std::integral<T>;
}