#pragma once
#include "concepts.hpp"

namespace xme {
struct StaticAllocation {};

template<CAllocator T>
struct DynamicAllocation {
    using allocator_type = T;
};
}; // namespace xme