#pragma once
#include <type_traits>
#include <xme/setup.hpp>

namespace xme {
template<typename T>
XME_INLINE constexpr auto to_unsigned(T n) {
    return static_cast<std::make_unsigned_t<T>>(n);
}

#ifdef __sizeof_int128__
XME_INLINE constexpr auto to_unsigned(__int128 n) -> unsigned __int128 {
    return static_cast<unsigned __int128>(n);
}

XME_INLINE constexpr auto to_unsigned(unsigned __int128 n) -> unsigned __int128 {
    return n;
}
#endif
}  // namespace xme