#pragma once
#include <type_traits>

namespace xme {
template<typename From, typename To>
concept CConvertibleTo =
  std::is_convertible_v<From, To> && requires { static_cast<To>(std::declval<From>()); };

}  // namespace xme
