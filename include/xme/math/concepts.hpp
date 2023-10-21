#pragma once
#include <concepts>
#include "type_traits.hpp"

namespace xme::math {
template<typename T>
concept CArithmetic = std::floating_point<T> || std::integral<T>;

template<typename T>
concept CVector = is_vector_v<T>;

template<typename T>
concept CMatrix = is_matrix_v<T>;
}