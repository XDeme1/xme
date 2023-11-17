#pragma once
#include <type_traits>

namespace xme {
template<typename E>
    struct IsScopedEnum : std::bool_constant < requires() {
    requires std::is_enum_v<E>;
    requires !std::is_convertible_v<E, std::underlying_type_t<E>>;
} > {};

template<typename E>
inline constexpr bool is_scoped_enum_v = IsScopedEnum<E>::value;
}  // namespace xme
