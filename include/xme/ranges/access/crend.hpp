// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include <xme/core/iterators/const_iterator.hpp>
#include "rend.hpp"
#include "cbegin.hpp"

namespace xme::ranges {
struct {
    template<detail::basic_borrowed_range T>
    constexpr auto operator()(T&& t) const noexcept {
        return xme::make_const_iterator(ranges::rend(detail::possibly_const_range(t)));
    }
} inline constexpr crend;
}  // namespace xme::ranges