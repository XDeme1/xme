#pragma once
#include <type_traits>

namespace xme {
template<typename T>
constexpr auto has_single_bit(T n) noexcept {
    static_assert(std::is_unsigned_v<T>, "T must be unsigned");
    return !((n - 1) & n) && n != 0;
}
}  // namespace xme
