#pragma once
#include "forward.hpp"

namespace xme {
    template<typename T>
    constexpr bool is_vector = false;

    template<typename T, std::size_t Size>
    constexpr bool is_vector<Vector<T, Size>> = true;

    template<typename T>
    constexpr bool is_matrix = false;
    
    template<typename T, std::size_t Cols, std::size_t Rows>
    constexpr bool is_matrix<Matrix<T, Cols, Rows>> = true;

    template<typename T>
    constexpr bool is_quaternion = false;

    template<typename T>
    constexpr bool is_quaternion<Quaternion<T>> = true;
}