#pragma once

namespace xme {
struct StaticAllocation {};

template<typename Alloc>
struct DynamicAllocation {
    using allocator = Alloc;
};
}; // namespace xme