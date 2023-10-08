#pragma once
#include <xme/math/matrix.hpp>

namespace xme {
    template<std::floating_point T>
    constexpr auto perspectiveRH(T fov, T aspect_ratio, T far, T near) -> Matrix<T, 4> {
        const auto halfTan = std::tan(fov / 2);
        
        Matrix<T, 4> result{0};
        result[0][0] = 1 / (aspect_ratio * halfTan);
        result[1][1] = 1 / halfTan;
        result[2][2] = -(far + near) / (far - near);
        result[2][3] = -1;
        result[3][2] = -(2 * far * near) / (far - near);
        return result;
    }

    template<std::floating_point T>
    constexpr auto perspective(T fov, T aspect_ratio, T far, T near) -> Matrix<T, 4> {
        return perspectiveRH(fov, aspect_ratio, far, near);
    }
}