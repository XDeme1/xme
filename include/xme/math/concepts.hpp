#pragma once
#include <concepts>
#include "type_traits.hpp"

namespace xme {
template<typename T>
concept CArithmetic = std::floating_point<T> || std::integral<T>;

template<typename T>
concept CVector = is_vector<T>;

template<typename T>
concept CMatrix = is_matrix<T>;

template<typename T>
concept CQuaternion = is_quaternion<T>;
}