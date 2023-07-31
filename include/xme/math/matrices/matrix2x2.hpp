#pragma once

#include "../../../../private/math/forward.hpp"
#include <array>

namespace xme {
    template<typename T>
    class Matrix<T, 2, 2> {
    public:
        static_assert(std::floating_point<T>, "T must be a floating point");

        using column_type = Vector<T, 2>;
        constexpr Matrix() noexcept
            : Matrix(1, 0, 
                     0, 1) {}

        constexpr Matrix(auto x1, auto y1,
                         auto x2, auto y2)
            : m_Data({{x1, y1},
                      {x2, y2}}) {}

        constexpr auto operator[](std::size_t i) noexcept -> column_type&
        { return m_Data[i]; }

        constexpr auto operator[](std::size_t i, std::size_t j) noexcept -> T&
        { return m_Data[i][j]; }
    private:
        std::array<column_type, 2> m_Data;
    };
}