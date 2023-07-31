#pragma once
#include <cstdint>

namespace xme {
    template<typename T, std::size_t Size>
    struct Vector;
    
    template<typename T, std::size_t Cols, std::size_t Rows>
    class Matrix;

    template<typename T>
    class Quaternion;
}