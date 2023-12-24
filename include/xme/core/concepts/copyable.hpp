#pragma once
#include <xme/core/concepts/movable.hpp>

namespace xme {
template<typename T>
concept copyable_c = copy_constructible<T> && movable_c<T> && assignable_from_c<T&, T&>
                     && assignable_from_c<T&, const T&> && std::assignable_from<T&, const T>;
}
