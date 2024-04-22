// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include <limits>
#include "size.hpp"

namespace xme::ranges {
struct {
    template<typename T>
    constexpr auto operator()(T&& t) const noexcept {
        auto s       = ranges::size(t);
        using s_type = decltype(s);
        if constexpr(std::integral<s_type>) {
            if constexpr(std::numeric_limits<s_type>::digits
                         < std::numeric_limits<std::ptrdiff_t>::digits)
                return static_cast<std::ptrdiff_t>(s);
            else
                return static_cast<std::make_signed_t<s_type>>(s);
        }
#ifdef __SIZEOF_INT128__
        else {
            return static_cast<signed __int128>(t);
        }
#endif
    }
} inline constexpr ssize;
}  // namespace xme::ranges