#pragma once
#include <concepts>
#include "type_traits.hpp"

namespace xme::math {
template<typename T>
concept CArithmetic = std::floating_point<T> || std::integral<T>;

template<auto A, auto B>
concept CEqual = A == B;

template<auto A, auto B>
concept CLess = A < B;

template<auto A, auto B>
concept CGreater = A > B;

template<typename T>
concept CVector = is_vector_v<T>;

template<typename T>
concept CMatrix = is_matrix_v<T>;
}