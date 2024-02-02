#pragma once
#include <iterator>

namespace xme {
template<std::indirectly_readable T>
using iter_const_reference_t =
  std::common_reference_t<const std::iter_value_t<T>&&, std::iter_reference_t<T>>;
}