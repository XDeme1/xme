#pragma once
#include <type_traits>

namespace xme {
template<typename T, typename U>
concept CSameAs = std::is_same_v<T, U> && std::is_same_v<U, T>;
}
