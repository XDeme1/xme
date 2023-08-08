#pragma once
#include <iostream>
#include <xme/math/forward.hpp>

namespace xme {
    template<typename T, std::size_t Size>
    std::ostream& operator<<(std::ostream& os, const Vector<T, Size>& v) {
        os << "Vector(";
        for (std::size_t i = 0; i < Size-1; ++i)
            os << v[i] << ", ";
        os << v[Size-1] << ')';
        return os;
    }
}