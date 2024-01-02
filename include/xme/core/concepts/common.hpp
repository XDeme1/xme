#pragma once
#include <type_traits>
#include <xme/core/concepts/same_as.hpp>
#include <xme/core/concepts/convertible.hpp>

namespace xme {
template<typename T, typename U>
concept CCommonReferenceWith = CSameAs<std::common_reference_t<T, U>, std::common_reference_t<U, T>>
                               && CConvertibleTo<T, std::common_reference_t<T, U>>
                               && CConvertibleTo<U, std::common_reference_t<T, U>>;

template<typename T, typename U>
concept CCommonWith = CSameAs<std::common_type_t<T, U>, std::common_type_t<U, T>> && requires {
    static_cast<std::common_type_t<T, U>>(std::declval<T>());
    static_cast<std::common_type_t<T, U>>(std::declval<U>());
} && CCommonReferenceWith<std::add_lvalue_reference_t<const T>, std::add_lvalue_reference_t<const U>> && CCommonReferenceWith<std::add_lvalue_reference_t<std::common_type_t<T, U>>, std::common_reference_t<std::add_lvalue_reference_t<const T>, std::add_lvalue_reference_t<U>>>;
}  // namespace xme
