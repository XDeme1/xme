#pragma once
#include <concepts>
#include <tuple>
#include <type_traits>
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

namespace detail {
template<typename T, std::size_t I>
concept CTupleElement = requires(T t) {
    typename std::tuple_element_t<I, std::remove_const_t<T>>;
    { get<I>(t) } -> std::convertible_to<const std::tuple_element_t<I, T>&>;
};
} // namespace detail

template<typename T>
concept CTupleLike = requires(T t) {
    typename std::tuple_size<T>::type;
    requires std::derived_from<std::tuple_size<T>,
                               std::integral_constant<std::size_t, std::tuple_size_v<T>>>;
} && []<std::size_t... I>(std::index_sequence<I...>) {
    return (detail::CTupleElement<T, I> && ...);
}(std::make_index_sequence<std::tuple_size_v<T>>{});

template<typename T>
concept CPairLike = CTupleLike<T> && (std::tuple_size_v<T> == 2);
} // namespace xme