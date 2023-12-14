#pragma once
#include <cstddef>

//! Made in its own file for future use.
namespace xme {
//! Specifies the size of the container.
template<std::size_t N>
struct Capacity {
    static constexpr std::size_t capacity = N;
};
};  // namespace xme