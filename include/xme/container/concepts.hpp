#pragma once
#include <concepts>
#include <type_traits>
#include <tuple>

namespace xme {
template<typename Alloc>
concept allocator_c = requires(Alloc a, typename Alloc::value_type* ptr) {
    typename Alloc::value_type;
    typename Alloc::size_type;
    typename Alloc::difference_type;
    { a.allocate(std::size_t()) } -> std::same_as<typename Alloc::value_type*>;
    a.deallocate(ptr, std::size_t());
};

namespace detail {
template<typename T, std::size_t I>
concept tuple_element_c = requires(T t) {
    typename std::tuple_element_t<I, std::remove_const_t<T>>;
    { get<I>(t) } -> std::convertible_to<const std::tuple_element_t<I, T>&>;
};

template<typename T, std::size_t... I>
constexpr auto tuple_element(std::index_sequence<I...>) noexcept {
    return (detail::tuple_element_c<T, I> && ...);
}

template<typename T>
concept tuple_like_impl_c = requires(T t) {
    typename std::tuple_size<T>::type;
    requires std::derived_from<std::tuple_size<T>,
                               std::integral_constant<std::size_t, std::tuple_size_v<T>>>;
} && detail::tuple_element<T>(std::make_index_sequence<std::tuple_size_v<T>>{});
}  // namespace detail

template<typename T>
concept tuple_like_c = detail::tuple_like_impl_c<std::remove_cvref_t<T>>;

template<typename T>
concept pair_like_c = tuple_like_c<T> && (std::tuple_size_v<std::remove_cvref_t<T>> == 2);
}  // namespace xme
