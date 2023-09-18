#pragma once
#include "../../../private/container/tuple_base.hpp"
#include "concepts.hpp"
#include <functional>

namespace xme {
template<typename... T>
struct Tuple : public detail::tuple_base<T...> {
private:
    using self = Tuple<T...>;

public:
    static constexpr std::size_t size = sizeof...(T);

    template<typename U>
        requires(CTupleLike<std::decay_t<U>>)
    constexpr auto operator=(U&& tup) -> self& {
        assignTupleIndex(std::forward<U>(tup), std::make_index_sequence<size>{});
        return *this;
    }

    constexpr auto operator<=>(const self&) const = default;
    constexpr bool operator==(const self&) const = default;

    constexpr void swap(Tuple& other) noexcept((std::is_nothrow_swappable_v<T> && ...)) {
        swap(other, std::make_index_sequence<size>{});
    }

private:
    template<typename Tup, std::size_t... I>
    constexpr void assignTupleIndex(Tup&& tup, std::index_sequence<I...>) {
        (void(detail::TupleElement<I, T>::value = get<I>(std::forward<Tup>(tup))), ...);
    }

    template<std::size_t... I>
    constexpr void
    swap(Tuple& tup,
         std::index_sequence<I...>) noexcept((std::is_nothrow_swappable_v<T> && ...)) {
        (std::ranges::swap(get<I>(*this), get<I>(tup)), ...);
    }
};

template<typename... T>
Tuple(T...) -> Tuple<std::unwrap_ref_decay_t<T>...>;

template<std::size_t I, typename... T>
constexpr auto get(Tuple<T...>& tup) noexcept -> decltype(auto) {
    return tup[std::integral_constant<std::size_t, I>{}];
}

template<std::size_t I, typename... T>
constexpr auto get(const Tuple<T...>& tup) noexcept -> decltype(auto) {
    return tup[std::integral_constant<std::size_t, I>{}];
}

template<std::size_t I, typename... T>
constexpr auto get(Tuple<T...>&& tup) noexcept -> decltype(auto) {
    return std::move(tup)[std::integral_constant<std::size_t, I>{}];
}

template<typename... T>
constexpr void swap(Tuple<T...>& lhs,
                    Tuple<T...>& rhs) noexcept((std::is_nothrow_swappable_v<T> && ...)) {
    lhs.swap(rhs);
}

namespace detail {
template<typename F, typename T, std::size_t... I>
    requires(CTupleLike<std::decay_t<T>>)
constexpr auto apply(F&& fun, T&& tup, std::index_sequence<I...>) noexcept(
    noexcept(std::forward<F>(fun)(get<I>(std::forward<T>(tup))...))) -> decltype(auto) {
    return std::forward<F>(fun)(get<I>(std::forward<T>(tup))...);
}
} // namespace detail

template<typename F, typename T>
    requires(CTupleLike<std::decay_t<T>>)
constexpr auto apply(F&& fun, T&& tup) noexcept(noexcept(detail::apply(
    std::forward<F>(fun), std::forward<T>(tup),
    std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{}))) -> decltype(auto) {
    return detail::apply(std::forward<F>(fun), std::forward<T>(tup),
                         std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{});
}

template<typename... T>
constexpr auto tie(T&... t) -> Tuple<T&...> {
    return {t...};
}

template<typename... T>
constexpr auto makeTuple(T&&... values) noexcept(
    std::is_nothrow_constructible_v<Tuple<std::unwrap_ref_decay_t<T>...>, T...>) {
    return Tuple<std::unwrap_ref_decay_t<T>...>{std::forward<T>(values)...};
}

template<typename... T>
constexpr auto forwardAsTuple(T&&... values) -> Tuple<T&&...> {
    static_assert((!std::is_rvalue_reference_v<T> && ...), "T is a dangling reference");
    return Tuple<T&&...>{std::forward<T>(values)...};
}

// Find a better way to do tupleCat
namespace detail {
template<typename T, typename OuterIdx, typename InnerIdx, std::size_t Next, typename...>
struct TupleCat;
template<typename T, std::size_t... OuterIdx, std::size_t... InnerIdx, std::size_t Next>
struct TupleCat<T, std::index_sequence<OuterIdx...>, std::index_sequence<InnerIdx...>,
                Next> {
    using return_t = Tuple<std::tuple_element_t<
        OuterIdx, std::remove_cvref_t<std::tuple_element_t<InnerIdx, T>>>...>;
    using outer_indices = std::index_sequence<OuterIdx...>;
    using inner_indices = std::index_sequence<InnerIdx...>;
};

template<typename T, std::size_t... OuterIdx, std::size_t... InnerIdx, std::size_t Next,
         std::size_t... OuterNext, typename... Rest>
struct TupleCat<T, std::index_sequence<OuterIdx...>, std::index_sequence<InnerIdx...>,
                Next, std::index_sequence<OuterNext...>, Rest...>
    : TupleCat<T, std::index_sequence<OuterIdx..., OuterNext...>,
               std::index_sequence<InnerIdx..., (Next + 0 * OuterNext)...>, Next + 1,
               Rest...> {};

template<typename... T>
using tuple_cat =
    TupleCat<Tuple<T&&...>, std::index_sequence<>, std::index_sequence<>, 0,
             std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>...>;

template<typename R, std::size_t... OuterIndex, std::size_t... InnerIndex, typename T>
constexpr auto tupleCat(std::index_sequence<OuterIndex...>,
                        std::index_sequence<InnerIndex...>, T tup) -> R {
    return R{get<OuterIndex>(get<InnerIndex>(std::move(tup)))...};
}
} // namespace detail

template<typename... T>
    requires(CTupleLike<std::decay_t<T>> && ...)
constexpr auto tupleCat(T&&... t) {
    using cat = detail::tuple_cat<T...>;
    using outer = typename cat::outer_indices;
    using inner = typename cat::inner_indices;
    return detail::tupleCat<typename cat::return_t>(
        outer{}, inner{}, forwardAsTuple(std::forward<T>(t)...));
}

} // namespace xme

namespace std {
template<typename... T>
struct tuple_size<xme::Tuple<T...>> : integral_constant<size_t, sizeof...(T)> {};

template<size_t I, typename... T>
struct tuple_element<I, xme::Tuple<T...>> {
    using type = decltype(xme::Tuple<T...>::declval(integral_constant<size_t, I>{}));
};
} // namespace std