#pragma once
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <ranges>

namespace xme {
template<typename Container>
class IContainer {
public:
    [[nodiscard]]
    constexpr auto operator[](std::ptrdiff_t i) noexcept -> decltype(auto)
        requires(std::ranges::random_access_range<Container>)
    {
        return std::ranges::begin(static_cast<Container&>(*this))[i];
    }

    [[nodiscard]]
    constexpr auto operator[](std::ptrdiff_t i) const noexcept -> decltype(auto)
        requires(std::ranges::random_access_range<Container>)
    {
        return std::ranges::begin(static_cast<const Container&>(*this))[i];
    }

    [[nodiscard]]
    constexpr bool empty() noexcept
        requires(std::ranges::forward_range<Container>)
    {
        auto&& derived = static_cast<Container&>(*this);
        if constexpr(std::ranges::sized_range<Container>) {
            return std::ranges::size(derived) == 0;
        }
        return std::ranges::begin(derived) == std::ranges::end(derived);
    }

    [[nodiscard]]
    constexpr bool empty() const noexcept
        requires(std::ranges::forward_range<const Container>)
    {
        auto&& derived = static_cast<const Container&>(*this);
        if constexpr(std::ranges::sized_range<Container>) {
            return std::ranges::size(derived) == 0;
        }
        return std::ranges::begin(derived) == std::ranges::end(derived);
    }

    [[nodiscard]]
    constexpr auto cbegin() noexcept {
        return std::ranges::cbegin(static_cast<Container&>(*this));
    }

    [[nodiscard]]
    constexpr auto cbegin() const noexcept {
        return std::ranges::cbegin(static_cast<const Container&>(*this));
    }

    [[nodiscard]]
    constexpr auto cend() noexcept {
        return std::ranges::cend(static_cast<Container&>(*this));
    }

    [[nodiscard]]
    constexpr auto cend() const noexcept {
        return std::ranges::cend(static_cast<const Container&>(*this));
    }

    [[nodiscard]]
    constexpr auto rbegin() noexcept
        requires requires { typename Container::reverse_iterator; }
    {
        return
          typename Container::reverse_iterator(std::ranges::end(static_cast<Container&>(*this)));
    }

    [[nodiscard]]
    constexpr auto rbegin() const noexcept
        requires requires { typename Container::const_reverse_iterator; }
    {
        return Container::const_reverse_iterator(
          std::ranges::end(static_cast<const Container&>(*this)));
    }

    [[nodiscard]]
    constexpr auto rend() noexcept
        requires requires { typename Container::reverse_iterator; }
    {
        return
          typename Container::reverse_iterator(std::ranges::begin(static_cast<Container&>(*this)));
    }

    [[nodiscard]]
    constexpr auto rend() const noexcept
        requires requires { typename Container::const_reverse_iterator; }
    {
        return Container::const_reverse_iterator(
          std::ranges::begin(static_cast<const Container&>(*this)));
    }

    [[nodiscard]]
    constexpr auto crbegin() noexcept
        requires requires { typename Container::const_reverse_iterator; }
    {
        return Container::const_reverse_iterator(cend());
    }

    [[nodiscard]]
    constexpr auto crbegin() const noexcept
        requires requires { typename Container::const_reverse_iterator; }
    {
        return Container::const_reverse_iterator(cend());
    }

    [[nodiscard]]
    constexpr auto crend() noexcept
        requires requires { typename Container::const_reverse_iterator; }
    {
        return Container::const_reverse_iterator(cbegin());
    }

    [[nodiscard]]
    constexpr auto crend() const noexcept
        requires requires { typename Container::const_reverse_iterator; }
    {
        return Container::const_reverse_iterator(cbegin());
    }

    [[nodiscard]]
    constexpr auto data() noexcept
        requires(std::contiguous_iterator<std::ranges::iterator_t<Container>>)
    {
        return std::to_address(std::ranges::begin(static_cast<Container&>(*this)));
    }

    [[nodiscard]]
    constexpr auto data() const noexcept
        requires(std::contiguous_iterator<std::ranges::iterator_t<const Container>>)
    {
        return std::to_address(std::ranges::begin(static_cast<const Container&>(*this)));
    }

    [[nodiscard]]
    constexpr auto size() noexcept -> std::size_t
        requires std::ranges::forward_range<Container>
                 && std::sized_sentinel_for<std::ranges::sentinel_t<Container>,
                                            std::ranges::iterator_t<Container>>
    {
        auto&& derived = static_cast<Container&>(*this);
        return std::ranges::end(derived) - std::ranges::begin(derived);
    }

    [[nodiscard]]
    constexpr auto size() const noexcept -> std::size_t
        requires std::ranges::forward_range<const Container>
                 && std::sized_sentinel_for<std::ranges::sentinel_t<const Container>,
                                            std::ranges::iterator_t<const Container>>
    {
        auto&& derived = static_cast<const Container&>(*this);
        return std::ranges::end(derived) - std::ranges::begin(derived);
    }

    [[nodiscard]]
    constexpr auto front() noexcept -> decltype(auto)
        requires(std::ranges::forward_range<Container>)
    {
        return *std::ranges::begin(static_cast<Container&>(*this));
    }

    [[nodiscard]]
    constexpr auto front() const noexcept -> decltype(auto)
        requires(std::ranges::forward_range<Container>)
    {
        return *std::ranges::begin(static_cast<const Container&>(*this));
    }

    [[nodiscard]]
    constexpr auto back() noexcept -> decltype(auto)
        requires(std::ranges::bidirectional_range<Container>)
    {
        return *std::ranges::prev(std::ranges::end(static_cast<Container&>(*this)));
    }

    [[nodiscard]]
    constexpr auto back() const noexcept -> decltype(auto)
        requires(std::ranges::bidirectional_range<const Container>)
    {
        return *std::ranges::prev(std::ranges::end(static_cast<const Container&>(*this)));
    }
};
}  // namespace xme