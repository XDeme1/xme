#pragma once
#include "concepts.hpp"

namespace xme {
template<typename T, typename U>
struct Pair {
private:
    using self = Pair<T, U>;

public:
    static constexpr bool is_nothrow_swappable = false;
    template<CPairLike P>
    constexpr auto operator=(P&& p) noexcept(is_nothrow_swappable) -> self& {
        first = get<0>(std::forward<P>(p));
        second = get<1>(std::forward<P>(p));
        return *this;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, 0>) & noexcept -> T& {
        return first;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, 0>) const& noexcept
        -> const T& {
        return first;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, 0>) && noexcept -> T&& {
        return first;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, 1>) & noexcept -> U& {
        return second;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, 1>) const& noexcept
        -> const U& {
        return second;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, 1>) && noexcept -> U&& {
        return second;
    }

    constexpr auto operator<=>(const self&) const = default;
    constexpr bool operator==(const self&) const = default;

    static constexpr T declval(std::integral_constant<std::size_t, 0>) {
        static_assert(false, "This should only be used to get the type of the element");
    }

    static constexpr U declval(std::integral_constant<std::size_t, 1>) {
        static_assert(false, "This should only be used to get the type of the element");
    }

    constexpr void swap(const Pair& p) noexcept(std::is_nothrow_swappable_v<T> &&
                                          std::is_nothrow_swappable_v<U>) {
        std::ranges::swap(first, p.first);
        std::ranges::swap(second, p.second);
    }

    T first;
    U second;
};

template<typename T, typename U>
Pair(T, U) -> Pair<std::unwrap_ref_decay_t<T>, std::unwrap_ref_decay_t<U>>;

template<std::size_t I, typename T, typename U>
constexpr auto get(Pair<T, U>& p) noexcept -> decltype(auto) {
    return p[std::integral_constant<std::size_t, I>{}];
}

template<std::size_t I, typename T, typename U>
constexpr auto get(const Pair<T, U>& p) noexcept -> decltype(auto) {
    return p[std::integral_constant<std::size_t, I>{}];
}

template<std::size_t I, typename T, typename U>
constexpr auto get(Pair<T, U>&& p) noexcept -> decltype(auto) {
    return std::move(p)[std::integral_constant<std::size_t, I>{}];
}

template<typename T, typename U>
constexpr void swap(const Pair<T, U>& lhs, const Pair<T, U>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

template<typename T, typename U>
constexpr auto makePair(T&& t, U&& u) noexcept(
    std::is_nothrow_constructible_v<
        xme::Pair<std::unwrap_ref_decay_t<T>, std::unwrap_ref_decay_t<U>>, T, U>) {
    return Pair<std::unwrap_ref_decay_t<T>, std::unwrap_ref_decay_t<U>>{
        std::forward<T>(t), std::forward<U>(u)};
}

} // namespace xme

namespace std {
template<typename T, typename U>
struct tuple_size<xme::Pair<T, U>> : std::integral_constant<std::size_t, 2> {};

template<std::size_t I, typename T, typename U>
struct tuple_element<I, xme::Pair<T, U>> {
    using type =
        decltype(xme::Pair<T, U>::declval(std::integral_constant<std::size_t, I>{}));
};
} // namespace std