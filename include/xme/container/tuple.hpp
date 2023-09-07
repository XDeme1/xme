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
    using type_list = super::type_list;

public:
    using super::operator[];
    using super::declval;

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
        assign(type_list{}, std::forward<U>(values)...);
    }

    constexpr void swap(Tuple& other) noexcept(is_nothrow_swappable) {
        swap(other, type_list{});
    }

    template<typename F>
    constexpr auto
    apply(F&& fun) noexcept(noexcept(apply(std::forward<F>(fun), type_list{})))
        -> decltype(auto) {
        return apply(std::forward<F>(fun), type_list{});
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
    apply(F&& fun, detail::TypeList<U...>) noexcept(noexcept(fun(this->U::value...)))
        -> decltype(auto) {
        return fun(this->U::value...);
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

template<std::size_t I, typename T>
constexpr auto get(T&& tup) -> decltype(auto) {
    static_assert(xme::detail::is_tuple_v<std::decay_t<T>>, "T should be a xme::Tuple");
    return std::forward<T>(tup)[std::integral_constant<std::size_t, I>{}];
}

template<typename... T>
constexpr void swap(Tuple<T...>& lhs,
                    Tuple<T...>& rhs) noexcept(Tuple<T...>::is_nothrow_swappable) {
    lhs.swap(rhs);
}

template<typename F, typename T>
constexpr auto apply(F&& fun, T&& tup) noexcept(noexcept(tup.apply(std::forward<F>(fun))))
    -> decltype(auto) {
    static_assert(xme::detail::is_tuple_v<std::decay_t<T>>, "T should be a xme::Tuple");
    return tup.apply(std::forward<F>(fun));
}

template<typename... T>
constexpr auto tie(T&... t) -> Tuple<T&...> {
    return {t...};
}

template<typename... T>
constexpr auto makeTuple(T&&... values) {
    return Tuple<std::unwrap_ref_decay_t<T>...>{std::forward<T>(values)...};
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