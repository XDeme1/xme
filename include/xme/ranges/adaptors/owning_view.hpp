// IWYU pragma: private, include <xme/ranges/views.hpp>
#pragma once
#include "xme/core/type_traits/is_initializer_list.hpp"
#include "xme/ranges/iview.hpp"

namespace xme::ranges {
template<ranges::CRange R>
    requires std::movable<R> && (!xme::is_initializer_list<R>)
class OwningView : public IView<OwningView<R>> {
public:
    constexpr OwningView()
        requires std::default_initializable<R>
    = default;

    constexpr OwningView(const OwningView&) = delete;

    constexpr OwningView(OwningView&&) = default;

    constexpr OwningView(R&& r) noexcept : m_range(std::move(r)) {}

    constexpr auto operator=(const OwningView&) = delete;

    constexpr auto operator=(OwningView&&) -> OwningView& = default;

    constexpr auto begin() noexcept { return ranges::begin(m_range); }

    constexpr auto begin() const noexcept
        requires ranges::CRange<const R>
    {
        return ranges::begin(m_range);
    }

    constexpr auto end() noexcept { return ranges::end(m_range); }

    constexpr auto end() const noexcept
        requires ranges::CRange<const R>
    {
        return ranges::end(m_range);
    }

    constexpr bool empty() noexcept
        requires requires { ranges::empty(std::declval<R&>()); }
    {
        return ranges::empty(m_range);
    }

    constexpr bool empty() const noexcept
        requires requires { ranges::empty(std::declval<R&>()); }
    {
        return ranges::empty(m_range);
    }

    constexpr auto size() noexcept
        requires ranges::CSizedRange<R>
    {
        return ranges::size(m_range);
    }

    constexpr auto size() const noexcept
        requires ranges::CSizedRange<const R>
    {
        return ranges::size(m_range);
    }

    constexpr auto data() noexcept
        requires ranges::CContiguousRange<R>
    {
        return ranges::data(m_range);
    }

    constexpr auto data() const noexcept
        requires ranges::CContiguousRange<const R>
    {
        return ranges::data(m_range);
    }

private:
    R m_range{};
};
}  // namespace xme::ranges

template<typename R>
inline constexpr bool xme::ranges::enable_borrowed_range<xme::ranges::OwningView<R>> =
  xme::ranges::enable_borrowed_range<R>;