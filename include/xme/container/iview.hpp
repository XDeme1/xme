#pragma once
#include <cstddef>
#include <iterator>
#include <memory>
#include <ranges>

namespace xme {
template<typename D>
class IView {
private:
    constexpr auto derived() noexcept -> D& { return static_cast<D&>(*this); }

    constexpr auto derived() const noexcept -> const D& { return static_cast<const D&>(*this); }

public:
    [[nodiscard]]
    constexpr auto operator[](std::ptrdiff_t i) noexcept -> decltype(auto)
        requires(std::ranges::random_access_range<D>)
    {
        return std::ranges::begin(derived())[i];
    }

    [[nodiscard]]
    constexpr auto operator[](std::ptrdiff_t i) const noexcept -> decltype(auto)
        requires(std::ranges::random_access_range<const D>)
    {
        return std::ranges::begin(derived())[i];
    }

    [[nodiscard]]
    constexpr bool empty() noexcept
        requires(std::ranges::forward_range<D>)
    {
        if constexpr(std::ranges::sized_range<D>) {
            return std::ranges::size(derived()) == 0;
        }
        return std::ranges::begin(derived()) == std::ranges::end(derived());
    }

    [[nodiscard]]
    constexpr bool empty() const noexcept
        requires(std::ranges::forward_range<const D>)
    {
        if constexpr(std::ranges::sized_range<const D>) {
            return std::ranges::size(derived()) == 0;
        }
        return std::ranges::begin(derived()) == std::ranges::end(derived());
    }

    [[nodiscard]]
    constexpr auto cbegin() noexcept {
        return std::ranges::cbegin(derived());
    }

    [[nodiscard]]
    constexpr auto cbegin() const noexcept
        requires std::ranges::range<const D>
    {
        return std::ranges::cbegin(derived());
    }

    [[nodiscard]]
    constexpr auto cend() noexcept {
        return std::ranges::cend(derived());
    }

    [[nodiscard]]
    constexpr auto cend() const noexcept
        requires std::ranges::range<const D>
    {
        return std::ranges::cend(derived());
    }

    [[nodiscard]]
    constexpr auto data() noexcept
        requires(std::contiguous_iterator<std::ranges::iterator_t<D>>)
    {
        return std::to_address(std::ranges::begin(derived()));
    }

    [[nodiscard]]
    constexpr auto data() const noexcept
        requires(std::contiguous_iterator<std::ranges::iterator_t<const D>>)
    {
        return std::to_address(std::ranges::begin(derived()));
    }

    [[nodiscard]]
    constexpr auto size() noexcept -> std::size_t
        requires std::ranges::forward_range<D>
                 && std::sized_sentinel_for<std::ranges::sentinel_t<D>, std::ranges::iterator_t<D>>
    {
        return std::ranges::end(derived()) - std::ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto size() const noexcept -> std::size_t
        requires std::ranges::forward_range<const D>
                 && std::sized_sentinel_for<std::ranges::sentinel_t<const D>,
                                            std::ranges::iterator_t<const D>>
    {
        return std::ranges::end(derived()) - std::ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto front() noexcept -> decltype(auto)
        requires(std::ranges::forward_range<D>)
    {
        return *std::ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto front() const noexcept -> decltype(auto)
        requires(std::ranges::forward_range<const D>)
    {
        return *std::ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto back() noexcept -> decltype(auto)
        requires(std::ranges::bidirectional_range<D>)
    {
        return *std::ranges::prev(std::ranges::end(derived()));
    }

    [[nodiscard]]
    constexpr auto back() const noexcept -> decltype(auto)
        requires(std::ranges::bidirectional_range<const D>)
    {
        return *std::ranges::prev(std::ranges::end(derived()));
    }
};

template<typename D>
class IReverseView {
private:
    constexpr auto derived() noexcept -> D& { return static_cast<D&>(*this); }

    constexpr auto derived() const noexcept -> const D& { return static_cast<const D&>(*this); }

public:
    [[nodiscard]]
    constexpr auto rbegin() noexcept
        requires requires { typename D::reverse_iterator; }
    {
        return typename D::reverse_iterator(std::ranges::end(derived()));
    }

    [[nodiscard]]
    constexpr auto rbegin() const noexcept
        requires requires { typename D::const_reverse_iterator; }
    {
        return D::const_reverse_iterator(std::ranges::end(derived()));
    }

    [[nodiscard]]
    constexpr auto rend() noexcept
        requires requires { typename D::reverse_iterator; }
    {
        return typename D::reverse_iterator(std::ranges::begin(derived()));
    }

    [[nodiscard]]
    constexpr auto rend() const noexcept
        requires requires { typename D::const_reverse_iterator; }
    {
        return D::const_reverse_iterator(std::ranges::begin(derived()));
    }

    [[nodiscard]]
    constexpr auto crbegin() noexcept
        requires requires { typename D::const_reverse_iterator; }
    {
        return D::const_reverse_iterator(std::ranges::cend(derived()));
    }

    [[nodiscard]]
    constexpr auto crbegin() const noexcept
        requires requires { typename D::const_reverse_iterator; }
    {
        return D::const_reverse_iterator(std::ranges::cend(derived()));
    }

    [[nodiscard]]
    constexpr auto crend() noexcept
        requires requires { typename D::const_reverse_iterator; }
    {
        return D::const_reverse_iterator(std::ranges::cbegin(derived()));
    }

    [[nodiscard]]
    constexpr auto crend() const noexcept
        requires requires { typename D::const_reverse_iterator; }
    {
        return D::const_reverse_iterator(std::ranges::cbegin(derived()));
    }
};
}  // namespace xme