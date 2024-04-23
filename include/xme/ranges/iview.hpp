#pragma once
#include "concepts.hpp"

namespace xme::ranges {
template<typename D>
class IView {
private:
    constexpr auto derived() noexcept -> D& { return static_cast<D&>(*this); }

    constexpr auto derived() const noexcept -> const D& { return static_cast<const D&>(*this); }

public:
    [[nodiscard]]
    constexpr auto operator[](std::ptrdiff_t i) noexcept -> decltype(auto)
        requires(ranges::CRandomAccessRange<D>)
    {
        return ranges::begin(derived())[i];
    }

    [[nodiscard]]
    constexpr auto operator[](std::ptrdiff_t i) const noexcept -> decltype(auto)
        requires(ranges::CRandomAccessRange<const D>)
    {
        return ranges::begin(derived())[i];
    }

    [[nodiscard]]
    constexpr bool empty() noexcept
        requires(ranges::CForwardRange<D>)
    {
        if constexpr(ranges::CSizedRange<D>) {
            return ranges::size(derived()) == 0;
        }
        return ranges::begin(derived()) == ranges::end(derived());
    }

    [[nodiscard]]
    constexpr bool empty() const noexcept
        requires(ranges::CForwardRange<const D>)
    {
        if constexpr(ranges::CSizedRange<const D>) {
            return ranges::size(derived()) == 0;
        }
        return ranges::begin(derived()) == ranges::end(derived());
    }

    [[nodiscard]]
    constexpr auto cbegin() noexcept {
        return ranges::cbegin(derived());
    }

    [[nodiscard]]
    constexpr auto cbegin() const noexcept
        requires ranges::CRange<const D>
    {
        return ranges::cbegin(derived());
    }

    [[nodiscard]]
    constexpr auto cend() noexcept {
        return ranges::cend(derived());
    }

    [[nodiscard]]
    constexpr auto cend() const noexcept
        requires ranges::CRange<const D>
    {
        return ranges::cend(derived());
    }

    [[nodiscard]]
    constexpr auto data() noexcept
        requires(std::contiguous_iterator<ranges::iterator_t<D>>)
    {
        return std::to_address(ranges::begin(derived()));
    }

    [[nodiscard]]
    constexpr auto data() const noexcept
        requires(std::contiguous_iterator<ranges::iterator_t<const D>>)
    {
        return std::to_address(ranges::begin(derived()));
    }

    [[nodiscard]]
    constexpr auto size() noexcept -> std::size_t
        requires ranges::CForwardRange<D>
                 && std::sized_sentinel_for<ranges::sentinel_t<D>, ranges::iterator_t<D>>
    {
        return ranges::end(derived()) - ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto size() const noexcept -> std::size_t
        requires ranges::CForwardRange<const D>
                 && std::sized_sentinel_for<ranges::sentinel_t<const D>,
                                            ranges::iterator_t<const D>>
    {
        return ranges::end(derived()) - ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto front() noexcept -> decltype(auto)
        requires(ranges::CForwardRange<D>)
    {
        return *ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto front() const noexcept -> decltype(auto)
        requires(ranges::CForwardRange<const D>)
    {
        return *ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto back() noexcept -> decltype(auto)
        requires(ranges::CBidirectionalRange<D>)
    {
        return *std::ranges::prev(ranges::end(derived()));
    }

    [[nodiscard]]
    constexpr auto back() const noexcept -> decltype(auto)
        requires(ranges::CBidirectionalRange<const D>)
    {
        return *std::ranges::prev(ranges::end(derived()));
    }
};
}  // namespace xme::ranges