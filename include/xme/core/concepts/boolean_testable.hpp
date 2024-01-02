#pragma once
#include <xme/core/concepts/convertible.hpp>

namespace xme {

template<typename T>
concept boolean_testable_c = CConvertibleTo<T, bool> && requires(T& t) {
    { !static_cast<T&&>(t) } -> CConvertibleTo<bool>;
};
}  // namespace xme
