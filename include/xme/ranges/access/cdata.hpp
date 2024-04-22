// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include "data.hpp"
#include "cbegin.hpp"

namespace xme::ranges {
struct {
    template<typename T>
    constexpr auto operator()(T&& t) const noexcept -> const auto* {
        return ranges::data(detail::possibly_const_range(t));
    }
} inline constexpr cdata;
}  // namespace xme::ranges