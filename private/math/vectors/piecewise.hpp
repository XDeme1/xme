#pragma once
#include <xme/math/forward.hpp>

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

struct VectorPiecewise2 {
    template<typename T1, typename T2, typename U, typename R, std::size_t Size>
    constexpr auto operator()(const Vector<T1, Size>& v1, const Vector<T2, Size>& v2,  R(*fn)(U, U)) {
        xme::Vector<R, Size> result;
        for (std::size_t i = 0; i < Size; ++i) {
            result[i] = fn(v1[i], v2[i]);
        }
        return result;
    }
};
} // namespace xme::detail