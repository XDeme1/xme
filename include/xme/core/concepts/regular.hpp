#pragma once
#include <xme/core/concepts/constructible.hpp>
#include <xme/core/concepts/copyable.hpp>

namespace xme {
template<typename T>
concept semiregular_c = copyable_c<T> && default_initializable_c<T>;
template<typename T>
concept regular_c = semiregular_c<T>;
}  // namespace xme
