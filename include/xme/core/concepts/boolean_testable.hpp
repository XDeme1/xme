#pragma once
#include <xme/core/concepts/convertible.hpp>

namespace xme {
namespace detail {
template<typename T>
concept boolean_testable_impl_c = convertible_to_c<T, bool>;
}

template<typename T>
concept boolean_testable_c = detail::boolean_testable_impl_c<T> && requires(T& t) {
    { !static_cast<T&&>(t) } -> detail::boolean_testable_impl_c;
};
}  // namespace xme
