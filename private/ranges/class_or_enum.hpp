#pragma once
#include <type_traits>

namespace xme::ranges::detail {
template<typename T>
concept class_or_enum_c = std::is_class_v<T> || std::is_union_v<T> || std::is_enum_v<T>;
}
