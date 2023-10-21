#pragma once
#include "forward.hpp"

namespace xme::math {
template<typename T>
constexpr bool is_vector_v = false;

template<typename T, std::size_t N>
constexpr bool is_vector_v<Vector<T, N>> = true;

template<typename T>
constexpr bool is_matrix_v = false;

template<typename T, std::size_t Cols, std::size_t Rows>
constexpr bool is_matrix_v<Matrix<T, Cols, Rows>> = true;
}