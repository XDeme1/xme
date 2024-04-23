#pragma once
#include "concepts.hpp"
#include "xme/container/icontainer.hpp"

namespace xme::ranges {
template<typename D>
class IView : public IContainer<D> {
private:
    constexpr auto derived() noexcept -> D& { return static_cast<D&>(*this); }

    constexpr auto derived() const noexcept -> const D& { return static_cast<const D&>(*this); }

public:
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
};
}  // namespace xme::ranges