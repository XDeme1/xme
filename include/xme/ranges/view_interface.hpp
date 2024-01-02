#pragma once
#include <ranges>
#include <xme/core/concepts/same_as.hpp>

namespace xme::ranges {
template<typename D>
    requires std::is_class_v<D> && CSameAs<D, std::remove_cv_t<D>>
class ViewInterface {
public:
    template<std::ranges::sized_range R = D>
    constexpr bool empty() {
        return std::ranges::size(static_cast<R&>(*this)) == 0;
    }

    template<std::ranges::sized_range R = const D>
    constexpr bool empty() const {
        return std::ranges::size(static_cast<R&>(*this)) == 0;
    }

    template<std::ranges::forward_range R = D>
    constexpr bool empty()
        requires(!std::ranges::sized_range<R>)
    {
        return std::ranges::begin(static_cast<R&>(*this))
               == std::ranges::end(static_cast<R&>(*this));
    }

    template<std::ranges::forward_range R = const D>
    constexpr bool empty() const
        requires(!std::ranges::sized_range<R>)
    {
        return std::ranges::begin(static_cast<R&>(*this))
               == std::ranges::end(static_cast<R&>(*this));
    }

    constexpr auto cbegin() { return std::ranges::cbegin(static_cast<D&>(*this)); }

    template<std::ranges::range R = const D>
    constexpr auto cbegin() const {
        return std::ranges::cbegin(static_cast<R&>(*this));
    }

    constexpr auto cend() { return std::ranges::cend(static_cast<D&>(*this)); }

    template<std::ranges::range R = const D>
    constexpr auto cend() const {
        return std::ranges::cend(static_cast<R&>(*this));
    }

    template<typename R = D>
    explicit constexpr operator bool()
        requires requires { std::ranges::empty(static_cast<R&>(*this)); }
    {
        return !std::ranges::empty(static_cast<R&>(*this));
    }

    template<typename R = const D>
    explicit constexpr operator bool() const
        requires requires { std::ranges::empty(static_cast<R&>(*this)); }
    {
        return !std::ranges::empty(static_cast<R&>(*this));
    }

    template<typename R = D>
    constexpr auto data()
        requires std::contiguous_iterator<std::ranges::iterator_t<R>>
    {
        return std::to_address(std::ranges::begin(static_cast<R&>(*this)));
    }

    template<typename R = const D>
    constexpr auto data() const
        requires std::ranges::range<R> && std::contiguous_iterator<std::ranges::iterator_t<R>>
    {
        return std::to_address(std::ranges::begin(static_cast<R&>(*this)));
    }

    template<typename R = D>
    constexpr auto size()
        requires std::ranges::forward_range<R>
                 && std::sized_sentinel_for<std::ranges::sentinel_t<R>, std::ranges::iterator_t<R>>
    {
        return std::ranges::end(static_cast<R&>(*this))
               - std::ranges::begin(static_cast<R&>(*this));
    }

    template<typename R = const D>
    constexpr auto size() const
        requires std::ranges::forward_range<R>
                 && std::sized_sentinel_for<std::ranges::sentinel_t<R>, std::ranges::iterator_t<R>>
    {
        return std::ranges::end(static_cast<R&>(*this))
               - std::ranges::begin(static_cast<R&>(*this));
    }

    template<std::ranges::forward_range R = D>
    constexpr auto front() -> decltype(auto) {
        return *std::ranges::begin(static_cast<R&>(*this));
    }

    template<std::ranges::forward_range R = const D>
    constexpr auto front() const -> decltype(auto) {
        return *std::ranges::begin(static_cast<R&>(*this));
    }

    template<std::ranges::bidirectional_range R = D>
    constexpr auto back() -> decltype(auto)
        requires std::ranges::common_range<R>
    {
        return *std::ranges::prev(std::ranges::end(static_cast<R&>(*this)));
    }

    template<std::ranges::bidirectional_range R = const D>
    constexpr auto back() const -> decltype(auto)
        requires std::ranges::common_range<R>
    {
        return *std::ranges::prev(std::ranges::end(static_cast<R&>(*this)));
    }

    template<std::ranges::random_access_range R = D>
    constexpr auto operator[](std::ranges::range_difference_t<R> n) -> decltype(auto) {
        return std::ranges::begin(static_cast<R&>(*this))[n];
    }

    template<std::ranges::random_access_range R = const D>
    constexpr auto operator[](std::ranges::range_difference_t<R> n) const -> decltype(auto) {
        return std::ranges::begin(static_cast<R&>(*this))[n];
    }
};
}  // namespace xme::ranges
