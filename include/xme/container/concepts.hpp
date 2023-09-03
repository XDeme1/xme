#pragma once
#include <concepts>

namespace xme {

template<typename T>
concept CAllocator = requires(T a, typename T::value_type* ptr) {
    typename T::value_type;
    typename T::size_type;
    typename T::difference_type;
    { a.allocate(std::size_t(1)) } -> std::same_as<typename T::value_type*>;
    a.deallocate(ptr, std::size_t(1));
};

template<typename T>
concept CStatefulAllocator = CAllocator<T> && !std::is_empty_v<T>;

template<typename T>
concept CStatelessAllocator = CAllocator<T> && std::is_empty_v<T>;
}