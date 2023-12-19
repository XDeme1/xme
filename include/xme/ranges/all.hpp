#pragma once
#include <ranges>
#include "../../../private/ranges/setup.hpp"

namespace xme::ranges {
namespace detail {
template<typename>
inline constexpr bool is_initializer_list = false;

template<typename T>
inline constexpr bool is_initializer_list<std::initializer_list<T>> = true;
}  // namespace detail

template<std::ranges::range R>
    requires(std::is_object_v<R>)
class RefView : public std::ranges::view_interface<RefView<R>> {
    static void fun(R&);
    static void fun(R&&) = delete;

    using iterator = std::ranges::iterator_t<R>;

public:
    template<typename T>
        requires(!std::same_as<RefView, std::remove_cvref_t<T>>)
                && std::convertible_to<T, R&> && requires { fun(std::declval<T>()); }
    constexpr RefView(T&& t) noexcept(noexcept(static_cast<R&>(std::declval<T>()))) :
      m_range(std::addressof(static_cast<R&>(std::forward<T>(t)))) {}

    [[nodiscard]]
    constexpr auto begin() const -> iterator {
        return std::ranges::begin(*m_range);
    }

    [[nodiscard]]
    constexpr auto end() const -> iterator {
        return std::ranges::end(*m_range);
    }

    [[nodiscard]]
    constexpr bool empty() const
        requires requires { std::ranges::empty(*std::declval<R*>()); }
    {
        return std::ranges::empty(*m_range);
    }

    [[nodiscard]]
    constexpr auto size() const
        requires(std::ranges::sized_range<R>)
    {
        return std::ranges::size(*m_range);
    }

    [[nodiscard]]
    constexpr auto data() const
        requires(std::ranges::contiguous_range<R>)
    {
        return std::ranges::data(*m_range);
    }

private:
    R* m_range;
};

template<typename R>
RefView(R&) -> RefView<R>;

template<std::ranges::range R>
    requires(std::movable<R>) && (!detail::is_initializer_list<std::remove_cvref_t<R>>)
class OwningView : public std::ranges::view_interface<OwningView<R>> {
private:
    using iterator = std::ranges::iterator_t<R>;
    using sentinel = std::ranges::sentinel_t<R>;

public:
    constexpr OwningView()
        requires(std::default_initializable<R>)
    = default;

    constexpr OwningView(const OwningView&) = delete;

    constexpr OwningView(OwningView&&) = default;

    constexpr OwningView(R&& r) noexcept(std::is_nothrow_move_constructible_v<R>) :
      m_range(std::move(r)) {}

    constexpr auto operator=(const OwningView&) = delete;

    constexpr auto operator=(OwningView&&) -> OwningView& = default;

    [[nodiscard]]
    constexpr auto begin() -> iterator {
        return std::ranges::begin(m_range);
    }

    [[nodiscard]]
    constexpr auto begin() const
        requires(std::ranges::range<const R>)
    {
        return std::ranges::begin(m_range);
    }

    [[nodiscard]]
    constexpr auto end() -> sentinel {
        return std::ranges::end(m_range);
    }

    [[nodiscard]]
    constexpr auto end() const -> sentinel
        requires(std::ranges::range<const R>)
    {
        return std::ranges::end(m_range);
    }

    [[nodiscard]]
    constexpr bool empty()
        requires requires { std::ranges::empty(std::declval<R>()); }
    {
        return std::ranges::empty(m_range);
    }

    [[nodiscard]]
    constexpr bool empty() const
        requires requires { std::ranges::empty(std::declval<R>()); }
    {
        return std::ranges::empty(m_range);
    }

    [[nodiscard]]
    constexpr auto size()
        requires std::ranges::sized_range<R>
    {
        return std::ranges::size(m_range);
    }

    [[nodiscard]]
    constexpr auto size() const
        requires std::ranges::sized_range<const R>
    {
        return std::ranges::size(m_range);
    }

    [[nodiscard]]
    constexpr auto data()
        requires(std::ranges::contiguous_range<R>)
    {
        return std::ranges::data(m_range);
    }

    [[nodiscard]]
    constexpr auto data() const
        requires(std::ranges::contiguous_range<const R>)
    {
        return std::ranges::data(m_range);
    }

private:
    R m_range = R();
};

namespace views {
namespace detail {
template<typename R>
concept CRefViewPossible = requires { RefView{std::declval<R>()}; };

template<typename R>
concept COwningViewPossible = requires { OwningView{std::declval<R>()}; };

struct All : XME_RANGE_ADAPTOR_CLOSURE(All) {
private:
    template<typename R>
    static consteval bool is_noexcept() {
        if constexpr(std::ranges::view<std::decay_t<R>>)
            return std::is_nothrow_constructible_v<std::decay_t<R>, R>;
        else if constexpr(CRefViewPossible<R>)
            return noexcept(RefView{std::declval<R>()});
        else
            return noexcept(OwningView{std::declval<R>()});
    }

public:
    template<std::ranges::viewable_range R>
        requires std::ranges::view<std::decay_t<R>> || CRefViewPossible<R> || COwningViewPossible<R>
    constexpr auto operator()(R&& r) const noexcept(is_noexcept<R>()) {
        if constexpr(std::ranges::view<std::decay_t<R>>) {
            return std::forward<R>(r);
        }
        else if constexpr(detail::CRefViewPossible<R>) {
            return RefView{std::forward<R>(r)};
        }
        else {
            return OwningView{std::forward<R>(r)};
        }
    }
};
}  // namespace detail

inline constexpr detail::All all;

template<std::ranges::viewable_range R>
using all_t = decltype(all(std::declval<R>()));
}  // namespace views
}  // namespace xme::ranges

namespace xme {
namespace views = xme::ranges::views;
}

template<typename T>
inline constexpr bool std::ranges::enable_borrowed_range<xme::ranges::RefView<T>> = true;

template<typename T>
inline constexpr bool std::ranges::enable_borrowed_range<xme::ranges::OwningView<T>> =
  std::ranges::enable_borrowed_range<T>;
