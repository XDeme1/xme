#pragma once
#include <functional>
#include <xme/container/tuple.hpp>

namespace xme {
namespace detail {
template<typename F, typename... Args>
struct BindFront {
private:
    using bound_indices = std::make_index_sequence<sizeof...(Args)>;
    using self = BindFront<F, Args...>;

public:
    constexpr BindFront(const BindFront&) noexcept = default;

    constexpr BindFront(BindFront&&) noexcept = default;

    template<typename Fn, typename... BoundArgs>
    constexpr BindFront(Fn&& func, BoundArgs&&... args) noexcept(
        std::is_nothrow_constructible_v<F, Fn> &&
        (std::is_nothrow_constructible_v<Args, BoundArgs> && ...))
        : callable(std::forward<Fn>(func)), bound_args{std::forward<BoundArgs>(args)...} {
    }

    constexpr auto operator=(const BindFront&) noexcept -> self& = default;

    constexpr auto operator=(BindFront&&) noexcept -> self& = default;

    // TODO: Simplify when deducing this is added
    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) & noexcept(
        std::is_nothrow_invocable_v<F&, Args&..., CallArgs...>) -> decltype(auto) {
        return self::call(*this, bound_indices{}, std::forward<CallArgs>(args)...);
    }

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) const& noexcept(
        std::is_nothrow_invocable_v<const F&, const Args&..., CallArgs...>)
        -> decltype(auto) {
        return self::call(*this, bound_indices{}, std::forward<CallArgs>(args)...);
    }

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) && noexcept(
        std::is_nothrow_invocable_v<F, Args..., CallArgs...>) -> decltype(auto) {
        return self::call(std::move(*this), bound_indices{},
                          std::forward<CallArgs>(args)...);
    }

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) const&& noexcept(
        std::is_nothrow_invocable_v<const F, const Args..., CallArgs...>)
        -> decltype(auto) {
        return self::call(std::move(*this), bound_indices{},
                          std::forward<CallArgs>(args)...);
    }

private:
    template<typename T, std::size_t... I, typename... InArgs>
    static constexpr auto
    call(T&& self, std::index_sequence<I...>, InArgs&&... args) noexcept(
        noexcept(std::invoke(std::forward<T>(self).callable,
                             get<I>(std::forward<T>(self).bound_args)...,
                             std::forward<InArgs>(args)...))) -> decltype(auto) {
        return std::invoke(std::forward<T>(self).callable,
                           get<I>(std::forward<T>(self).bound_args)...,
                           std::forward<InArgs>(args)...);
    }

    [[no_unique_address]] F callable;
    [[no_unique_address]] xme::Tuple<Args...> bound_args;
};

template<typename F, typename... Args>
struct BindBack {
private:
    using bound_indices = std::make_index_sequence<sizeof...(Args)>;
    using self = BindBack<F, Args...>;

public:
    constexpr BindBack(const BindBack&) noexcept = default;

    constexpr BindBack(BindBack&&) noexcept = default;

    template<typename Fn, typename... BoundArgs>
    constexpr BindBack(Fn&& func, BoundArgs&&... args) noexcept(
        std::is_nothrow_constructible_v<F, Fn> &&
        (std::is_nothrow_constructible_v<Args, BoundArgs> && ...))
        : callable(std::forward<Fn>(func)), bound_args{std::forward<BoundArgs>(args)...} {
    }

    constexpr auto operator=(const BindBack&) noexcept -> self& = default;

    constexpr auto operator=(BindBack&&) noexcept -> self& = default;

    // TODO: Simplify when deducing this is added
    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) & noexcept(
        std::is_nothrow_invocable_v<F&, CallArgs..., Args&...>) -> decltype(auto) {
        return self::call(*this, bound_indices{}, std::forward<CallArgs>(args)...);
    }

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) const& noexcept(
        std::is_nothrow_invocable_v<const F&, CallArgs..., const Args&...>)
        -> decltype(auto) {
        return self::call(*this, bound_indices{}, std::forward<CallArgs>(args)...);
    }

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) && noexcept(
        std::is_nothrow_invocable_v<F, CallArgs..., Args...>) -> decltype(auto) {
        return self::call(std::move(*this), bound_indices{},
                          std::forward<CallArgs>(args)...);
    }

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) const&& noexcept(
        std::is_nothrow_invocable_v<const F, CallArgs..., const Args...>)
        -> decltype(auto) {
        return self::call(std::move(*this), bound_indices{},
                          std::forward<CallArgs>(args)...);
    }

private:
    template<typename T, std::size_t... I, typename... InArgs>
    static constexpr auto
    call(T&& self, std::index_sequence<I...>, InArgs&&... args) noexcept(noexcept(
        std::invoke(std::forward<T>(self).callable, std::forward<InArgs>(args)...,
                    get<I>(std::forward<T>(self).bound_args)...))) -> decltype(auto) {
        return std::invoke(std::forward<T>(self).callable, std::forward<InArgs>(args)...,
                           get<I>(std::forward<T>(self).bound_args)...);
    }

    [[no_unique_address]] F callable;
    [[no_unique_address]] xme::Tuple<Args...> bound_args;
};

template<typename F>
struct Bind0 {
private:
    using self = Bind0<F>;

public:
    constexpr Bind0(const Bind0&) noexcept = default;

    constexpr Bind0(Bind0&&) noexcept = default;

    template<typename Fn>
    explicit constexpr Bind0(Fn&& func) noexcept(std::is_nothrow_constructible_v<F, Fn>)
        : callable(std::forward<Fn>(func)) {}

    constexpr auto operator=(const Bind0&) noexcept -> self& = default;

    constexpr auto operator=(Bind0&&) noexcept -> self& = default;

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) & noexcept(
        std::is_nothrow_invocable_v<F&, CallArgs...>) -> decltype(auto) {
        return std::invoke(callable, std::forward<CallArgs>(args)...);
    }

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) const& noexcept(
        std::is_nothrow_invocable_v<const F&, CallArgs...>) -> decltype(auto) {
        return std::invoke(callable, std::forward<CallArgs>(args)...);
    }

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) && noexcept(
        std::is_nothrow_invocable_v<F, CallArgs...>) -> decltype(auto) {
        return std::invoke(std::move(callable), std::forward<CallArgs>(args)...);
    }

    template<typename... CallArgs>
    constexpr auto operator()(CallArgs&&... args) const&& noexcept(
        std::is_nothrow_invocable_v<const F, CallArgs...>) -> decltype(auto) {
        return std::invoke(std::move(callable), std::forward<CallArgs>(args)...);
    }

private:
    [[no_unique_address]] F callable;
};
} // namespace detail

template<typename F, typename... Args>
constexpr auto bindFront(F&& func, Args&&... args) {
    static_assert(std::is_constructible_v<std::decay_t<F>, F>);
    static_assert(std::is_move_constructible_v<std::decay<F>>);
    static_assert((std::is_constructible_v<std::decay_t<Args>, Args> && ...));
    static_assert((std::is_move_constructible_v<std::decay_t<Args>> && ...));
    if constexpr (sizeof...(Args) == 0)
        return detail::Bind0<std::decay_t<F>>(std::forward<F>(func));
    else
        return detail::BindFront<std::decay_t<F>, std::decay_t<Args>...>(
            std::forward<F>(func), std::forward<Args>(args)...);
}

template<typename F, typename... Args>
constexpr auto bindBack(F&& func, Args&&... args) {
    static_assert(std::is_constructible_v<std::decay_t<F>, F>);
    static_assert(std::is_move_constructible_v<std::decay<F>>);
    static_assert((std::is_constructible_v<std::decay_t<Args>, Args> && ...));
    static_assert((std::is_move_constructible_v<std::decay_t<Args>> && ...));

    if constexpr (sizeof...(Args) == 0)
        return detail::Bind0<std::decay_t<F>>(std::forward<F>(func));
    else
        return detail::BindBack<std::decay_t<F>, std::decay_t<Args>...>(
            std::forward<F>(func), std::forward<Args>(args)...);
}
} // namespace xme