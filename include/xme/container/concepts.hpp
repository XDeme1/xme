#pragma once
#include <concepts>
#include <utility>

namespace xme {
template<typename T>
concept CStateless = std::is_empty_v<T>;

template<typename T>
concept CAllocator = requires(T a, typename T::value_type* ptr) {
    typename T::value_type;
    typename T::size_type;
    typename T::difference_type;
    { a.allocate(std::size_t(1)) } -> std::same_as<typename T::value_type*>;
    a.deallocate(ptr, std::size_t(1));
};

template<typename T>
concept CStatefulAllocator = CAllocator<T> && !CStateless<T>;

template<typename T>
concept CStatelessAllocator = CAllocator<T> && CStateless<T>;

template<typename T>
concept CTupleLike = (std::tuple_size_v<std::remove_cvref_t<T>> == 0) || requires(T t) {
    typename std::tuple_element_t<0, std::remove_cvref_t<T>>;
    std::tuple_size_v<std::remove_cvref_t<T>>;
    get<0>(t);
};

template<typename T>
concept CPairLike = CTupleLike<T> && (std::tuple_size_v<std::remove_cvref_t<T>> == 2);
} // namespace xme