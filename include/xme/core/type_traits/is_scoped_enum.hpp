#pragma once
#include <type_traits>

namespace xme {
template<typename E>
inline constexpr bool is_scoped_enum = requires() {
    requires std::is_enum_v<E>;
    requires !std::is_convertible_v<E, std::underlying_type_t<E>>;
};
}  // namespace xme
