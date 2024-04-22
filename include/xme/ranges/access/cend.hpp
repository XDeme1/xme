// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include "cbegin.hpp"

namespace xme::ranges {
struct {
    template<detail::basic_borrowed_range T>
    constexpr auto operator()(T&& t) const noexcept {
        return xme::make_const_sentinel(ranges::end(detail::possibly_const_range(t)));
    }
} inline constexpr cend;
}  // namespace xme::ranges