#pragma once
#include "../../../private/container/tuple_base.hpp"
#include "concepts.hpp"
#include <functional>

namespace xme {
template<typename... T>
struct Tuple : public detail::tuple_base<T...> {
private:
    using self = Tuple<T...>;
    using super = detail::tuple_base<T...>;

public:
    using super::operator[];
    using super::declval;
    using base_list = super::base_list;
    using element_list = detail::TypeList<T...>;

    static constexpr std::size_t size = sizeof...(T);
    static constexpr bool is_nothrow_swappable = (std::is_nothrow_swappable_v<T> && ...);

    template<CTupleLike U>
    constexpr auto operator=(U&& tup) -> self& {
        assignTupleIndex(std::forward<U>(tup), std::make_index_sequence<size>{});
        return *this;
    }

    constexpr auto operator<=>(const self&) const = default;
    constexpr bool operator==(const self&) const = default;

    template<typename... U>
    constexpr void assign(U&&... values) {
        static_assert(sizeof...(U) == size,
                      "The amount of arguments must be equal to the tuple's size");
        assign(base_list{}, std::forward<U>(values)...);
    }

    constexpr void swap(Tuple& other) noexcept(is_nothrow_swappable) {
        swap(other, base_list{});
    }

    template<typename F>
    constexpr auto
    apply(F&& fun) & noexcept(noexcept(apply(std::forward<F>(fun), base_list{})))
        -> decltype(auto) {
        return apply(std::forward<F>(fun), base_list{});
    }

    template<typename F>
    constexpr auto
    apply(F&& fun) const& noexcept(noexcept(apply(std::forward<F>(fun), base_list{})))
        -> decltype(auto) {
        return apply(std::forward<F>(fun), base_list{});
    }

    template<typename F>
    constexpr auto
    apply(F&& fun) && noexcept(noexcept(static_cast<Tuple&&>(*this).apply(std::forward<F>(fun), base_list{})))
        -> decltype(auto) {
        return static_cast<Tuple&&>(*this).apply(std::forward<F>(fun), base_list{});
    }

private:
    template<typename... U, typename... Args>
    constexpr void assign(detail::TypeList<U...>, Args&&... args) {
        (void(U::value = std::forward<Args>(args)), ...);
    }

    template<typename Tup, std::size_t... I>
    constexpr void assignTupleIndex(Tup&& tup, std::index_sequence<I...>) {
        (void(detail::TupleElement<I, T>::value = get<I>(std::forward<Tup>(tup))), ...);
    }

    template<typename Tup, typename... U>
    constexpr void swap(Tup&& tup,
                        detail::TypeList<U...>) noexcept(is_nothrow_swappable) {
        (void(std::ranges::swap(U::value, tup.U::value)), ...);
    }

    template<typename F, typename... U>
    constexpr auto
    apply(F&& fun, detail::TypeList<U...>) & noexcept(noexcept(fun(this->U::value...)))
        -> decltype(auto) {
        return fun(this->U::value...);
    }

    template<typename F, typename... U>
    constexpr auto apply(F&& fun, detail::TypeList<U...>) const& noexcept(
        noexcept(fun(this->U::value...))) -> decltype(auto) {
        return fun(this->U::value...);
    }

    template<typename F, typename... U>
    constexpr auto apply(F&& fun, detail::TypeList<U...>) && noexcept(
        noexcept(fun(static_cast<Tuple&&>(*this).U::value...))) -> decltype(auto) {
        return fun((static_cast<Tuple&&>(*this).U::value)...);
    }
};

template<>
struct Tuple<> : public detail::tuple_base<> {
private:
    using self = Tuple<>;

public:
    using element_list = detail::TypeList<>;

    static constexpr std::size_t size = 0;

    constexpr auto operator<=>(const Tuple&) const = default;
    constexpr bool operator==(const Tuple&) const = default;

    template<CTupleLike U>
    constexpr auto operator=(U&&) noexcept -> self& {
        return *this;
    }

    constexpr void assign() noexcept {}

    constexpr void swap() noexcept {}

    template<typename F>
    constexpr auto apply(F&& fun) noexcept(noexcept(fun())) -> decltype(auto) {
        return fun();
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
                    Tuple<T...>& rhs) noexcept(Tuple<T...>::is_nothrow_swappable) {
    lhs.swap(rhs);
}

template<typename F, typename... T>
constexpr auto apply(F&& fun,
                     Tuple<T...>& tup) noexcept(noexcept(tup.apply(std::forward<F>(fun))))
    -> decltype(auto) {
    return tup.apply(std::forward<F>(fun));
}

template<typename F, typename... T>
constexpr auto apply(F&& fun,
                     const Tuple<T...>& tup) noexcept(noexcept(tup.apply(std::forward<F>(fun))))
    -> decltype(auto) {
    return tup.apply(std::forward<F>(fun));
}

template<typename F, typename... T>
constexpr auto apply(F&& fun, Tuple<T...>&& tup) noexcept(
    noexcept(std::move(tup).apply(std::forward<F>(fun)))) -> decltype(auto) {
    return std::move(tup).apply(std::forward<F>(fun));
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
    return Tuple<T&&...>{std::forward<T>(values)...};
}

//Find a better way to do tupleCat
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

template<CTupleLike... T>
using tuple_cat =
    TupleCat<Tuple<T&&...>, std::index_sequence<>, std::index_sequence<>, 0,
             std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>...>;

template<typename R, std::size_t... OuterIndex, std::size_t... InnerIndex, typename T>
constexpr auto tupleCat(std::index_sequence<OuterIndex...>,
                        std::index_sequence<InnerIndex...>, T tup) -> R {
    return R{get<OuterIndex>(get<InnerIndex>(std::move(tup)))...};
}
} // namespace detail

template<CTupleLike... T>
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