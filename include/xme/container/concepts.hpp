#pragma once
#include <concepts>

namespace xme {
template<typename T>
concept CStatefulAllocator = !std::is_empty_v<T> && requires(T a) {
    { a.allocate(1) } -> std::same_as<typename T::value_type*>;
    a.deallocate((typename T::value_type*)(nullptr), 1);
};

template<typename T>
concept CStatelessAllocator = std::is_empty_v<T> && requires(T a) {
    { a.allocate(1) } -> std::same_as<typename T::value_type*>;
    a.deallocate((typename T::value_type*)(nullptr), 1);
};

template<typename T>
concept CAllocator = CStatefulAllocator<T> || CStatelessAllocator<T>;
}