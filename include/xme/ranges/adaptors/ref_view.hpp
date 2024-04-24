// IWYU pragma: private, include <xme/ranges/views.hpp>
#pragma once
#include "xme/ranges/concepts.hpp"
#include "xme/ranges/iview.hpp"

namespace xme::ranges {
template<ranges::CRange R>
    requires std::is_object_v<R>
class RefView : public IView<RefView<R>> {
public:
    template<CDifferentFromSelf<RefView> T>
        requires std::convertible_to<T, R&> && std::is_lvalue_reference_v<T>
    constexpr RefView(T&& t) noexcept :
      m_ref(std::addressof(static_cast<R&>(std::forward<T>(t)))) {}

    constexpr auto begin() const noexcept { return ranges::begin(*m_ref); }

    constexpr auto end() const noexcept { return ranges::end(*m_ref); }

    constexpr bool empty() const noexcept { return ranges::empty(*m_ref); }

    constexpr auto size() const noexcept
        requires ranges::CSizedRange<R>
    {
        return ranges::size(*m_ref);
    }
    constexpr auto data() const noexcept
        requires ranges::CContiguousRange<R>
    {
        return ranges::data(*m_ref);
    }

private:
    R* m_ref = nullptr;
};

template<typename R>
RefView(R& r) -> RefView<R>;
}  // namespace xme::ranges

template<typename R>
inline constexpr bool xme::ranges::enable_borrowed_range<xme::ranges::RefView<R>> = true;