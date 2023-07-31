#pragma once
#include <cstdint>
#include "../forward.hpp"

namespace xme::detail {
struct VectorPiecewise1 {
    template<typename T, typename U, typename R, std::size_t Size>
    constexpr auto operator()(const Vector<T, Size>& v, R(*fn)(U)) {
        xme::Vector<R, Size> result;
        for (std::size_t i = 0; i < Size; ++i) {
            result[i] = fn(v[i]);
        }
        return result;
    }
};
} // namespace xme::detail