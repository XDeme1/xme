#pragma once
#include <range/v3/range.hpp>

namespace xme {
template<typename D>
class IContainer {
private:
    constexpr auto derived() noexcept -> D& { return static_cast<D&>(*this); }

    constexpr auto derived() const noexcept -> const D& { return static_cast<const D&>(*this); }

public:
    [[nodiscard]]
    constexpr auto operator[](std::ptrdiff_t i) noexcept -> decltype(auto)
        requires(::ranges::random_access_range<D>)
    {
        return ::ranges::begin(derived())[i];
    }

    [[nodiscard]]
    constexpr auto operator[](std::ptrdiff_t i) const noexcept -> decltype(auto)
        requires(::ranges::random_access_range<const D>)
    {
        return ::ranges::begin(derived())[i];
    }

    [[nodiscard]]
    constexpr bool empty() noexcept
        requires(::ranges::forward_range<D>)
    {
        if constexpr(::ranges::sized_range<D>) {
            return ::ranges::size(derived()) == 0;
        }
        return ::ranges::begin(derived()) == ::ranges::end(derived());
    }

    [[nodiscard]]
    constexpr bool empty() const noexcept
        requires(::ranges::forward_range<const D>)
    {
        if constexpr(::ranges::sized_range<const D>) {
            return ::ranges::size(derived()) == 0;
        }
        return ::ranges::begin(derived()) == ::ranges::end(derived());
    }

    [[nodiscard]]
    constexpr auto data() noexcept
        requires(::ranges::contiguous_iterator<::ranges::iterator_t<D>>)
    {
        return std::to_address(::ranges::begin(derived()));
    }

    [[nodiscard]]
    constexpr auto data() const noexcept
        requires(::ranges::contiguous_iterator<::ranges::iterator_t<const D>>)
    {
        return std::to_address(::ranges::begin(derived()));
    }

    [[nodiscard]]
    constexpr auto size() noexcept -> std::size_t
        requires ::ranges::forward_range<D>
                 && ::ranges::sized_sentinel_for<::ranges::sentinel_t<D>, ::ranges::iterator_t<D>>
    {
        return ::ranges::end(derived()) - ::ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto size() const noexcept -> std::size_t
        requires ::ranges::forward_range<const D>
                 && ::ranges::sized_sentinel_for<::ranges::sentinel_t<const D>,
                                            ::ranges::iterator_t<const D>>
    {
        return ::ranges::end(derived()) - ::ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto front() noexcept -> decltype(auto)
        requires(::ranges::forward_range<D>)
    {
        return *::ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto front() const noexcept -> decltype(auto)
        requires(::ranges::forward_range<const D>)
    {
        return *::ranges::begin(derived());
    }

    [[nodiscard]]
    constexpr auto back() noexcept -> decltype(auto)
        requires(::ranges::bidirectional_range<D>)
    {
        return *::ranges::prev(::ranges::end(derived()));
    }

    [[nodiscard]]
    constexpr auto back() const noexcept -> decltype(auto)
        requires(::ranges::bidirectional_range<const D>)
    {
        return *::ranges::prev(::ranges::end(derived()));
    }
};
}  // namespace xme