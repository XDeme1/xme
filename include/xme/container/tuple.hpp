#pragma once
#include "../../../private/container/tuple_base.hpp"
#include "concepts.hpp"
#include <functional>
#include <xme/setup.hpp>
#include <xme/ranges/swap.hpp>

namespace xme {
template<typename... T>
struct Tuple : public detail::tuple_base<T...> {
private:
    using self = Tuple<T...>;

public:
    static constexpr std::size_t size = sizeof...(T);

    template<tuple_like_c U>
        requires(!std::same_as<Tuple, std::remove_reference_t<U>>)
    constexpr auto operator=(U&& tup) -> self& {
        assign_tuple_index(std::forward<U>(tup), std::make_index_sequence<size>{});
        return *this;
    }

    template<typename U>
        requires(tuple_like_c<U> || std::is_aggregate_v<std::remove_reference_t<U>>)
                && (!std::same_as<Tuple, U>) && requires(T... args) { U{args...}; }
    constexpr operator U() const {
        auto convert = []<typename Tup, std::size_t... I>(Tup&& tup, std::index_sequence<I...>) {
            return U{get<I>(std::forward<Tup>(tup))...};
        };
        return convert(*this, std::make_index_sequence<size>{});
    }

    XME_CONSTEXPR20 bool operator==(const self&) const noexcept = default;

    XME_CONSTEXPR20 auto operator<=>(const self&) const noexcept = default;

    constexpr void swap(Tuple& other) noexcept((std::is_nothrow_swappable_v<T> && ...)) {
        swap(other, std::make_index_sequence<size>{});
    }

private:
    template<typename Tup, std::size_t... I>
    constexpr void assign_tuple_index(Tup&& tup, std::index_sequence<I...>) {
        (void(detail::TupleElement<I, T>::value = get<I>(std::forward<Tup>(tup))), ...);
    }

    template<std::size_t... I>
    constexpr void swap(Tuple& tup, std::index_sequence<I...>)
      noexcept((std::is_nothrow_swappable_v<T> && ...)) {
        (ranges::swap(get<I>(*this), get<I>(tup)), ...);
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
constexpr void swap(Tuple<T...>& lhs, Tuple<T...>& rhs)
  noexcept((std::is_nothrow_swappable_v<T> && ...)) {
    lhs.swap(rhs);
}

namespace detail {
template<typename F, tuple_like_c T, std::size_t... I>
constexpr auto apply(F&& fun, T&& tup, std::index_sequence<I...>)
  noexcept(noexcept(std::forward<F>(fun)(get<I>(std::forward<T>(tup))...))) -> decltype(auto) {
    return std::forward<F>(fun)(get<I>(std::forward<T>(tup))...);
}
}  // namespace detail

template<typename F, tuple_like_c T>
constexpr auto apply(F&& fun, T&& tup)
  noexcept(noexcept(detail::apply(std::forward<F>(fun), std::forward<T>(tup),
                                  std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{})))
    -> decltype(auto) {
    return detail::apply(std::forward<F>(fun),
                         std::forward<T>(tup),
                         std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{});
}

template<typename... T>
constexpr auto tie(T&... t) -> Tuple<T&...> {
    return {t...};
}

template<typename... T>
constexpr auto make_tuple(T&&... values)
  noexcept(std::is_nothrow_constructible_v<Tuple<std::unwrap_ref_decay_t<T>...>, T...>) {
    return Tuple<std::unwrap_ref_decay_t<T>...>{std::forward<T>(values)...};
}

template<typename... T>
constexpr auto forward_as_tuple(T&&... values) noexcept -> Tuple<T&&...> {
    static_assert((!std::is_rvalue_reference_v<T> && ...), "T is a dangling reference");
    return Tuple<T&&...>{std::forward<T>(values)...};
}

// Find a better way to do tupleCat
namespace detail {
template<typename T, typename OuterIdx, typename InnerIdx, std::size_t Next, typename...>
struct TupleCat;
template<typename T, std::size_t... OuterIdx, std::size_t... InnerIdx, std::size_t Next>
struct TupleCat<T, std::index_sequence<OuterIdx...>, std::index_sequence<InnerIdx...>, Next> {
    using return_t = Tuple<
      std::tuple_element_t<OuterIdx, std::remove_cvref_t<std::tuple_element_t<InnerIdx, T>>>...>;
    using outer_indices = std::index_sequence<OuterIdx...>;
    using inner_indices = std::index_sequence<InnerIdx...>;
};

template<typename T, std::size_t... OuterIdx, std::size_t... InnerIdx, std::size_t Next,
         std::size_t... OuterNext, typename... Rest>
struct TupleCat<T, std::index_sequence<OuterIdx...>, std::index_sequence<InnerIdx...>, Next,
                std::index_sequence<OuterNext...>, Rest...>
  : TupleCat<T, std::index_sequence<OuterIdx..., OuterNext...>,
             std::index_sequence<InnerIdx..., (Next + 0 * OuterNext)...>, Next + 1, Rest...> {};

template<typename... T>
using tuple_cat = TupleCat<Tuple<T&&...>, std::index_sequence<>, std::index_sequence<>, 0,
                           std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>...>;

template<typename R, std::size_t... OuterIndex, std::size_t... InnerIndex, typename T>
constexpr auto tuple_cat_impl(std::index_sequence<OuterIndex...>,
                              std::index_sequence<InnerIndex...>, T tup) -> R {
    return R{get<OuterIndex>(get<InnerIndex>(std::move(tup)))...};
}
}  // namespace detail

template<tuple_like_c... T>
constexpr auto tuple_cat(T&&... t) {
    using cat   = detail::tuple_cat<T...>;
    using outer = typename cat::outer_indices;
    using inner = typename cat::inner_indices;
    return detail::tuple_cat_impl<typename cat::return_t>(
      outer{}, inner{}, forward_as_tuple(std::forward<T>(t)...));
}

}  // namespace xme

namespace std {
template<typename... T>
struct tuple_size<xme::Tuple<T...>> : integral_constant<size_t, sizeof...(T)> {};

template<size_t I, typename... T>
struct tuple_element<I, xme::Tuple<T...>> {
    using type = decltype(xme::Tuple<T...>::declval(integral_constant<size_t, I>{}));
};

template<typename... T, typename... U, template<class> class TQual, template<class> class UQual>
struct basic_common_reference<xme::Tuple<T...>, xme::Tuple<U...>, TQual, UQual> {
    using type = xme::Tuple<std::common_reference_t<TQual<T>, UQual<U>>...>;
};

template<typename... T, typename... U>
    requires(sizeof...(T) == sizeof...(U))
struct common_type<xme::Tuple<T...>, xme::Tuple<U...>> {
    using type = xme::Tuple<std::common_type_t<T, U>...>;
};
}  // namespace std
