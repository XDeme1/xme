#pragma once
#include <concepts>
#include <type_traits>
#include <xme/hal/std_detection.hpp>
#include <ranges>

namespace xme::ranges {
#if __cpp_lib_ranges < 202202L
template<typename D>
    requires std::is_object_v<D> && std::same_as<D, std::remove_cv_t<D>>
struct range_adaptor_closure
#    if defined(XME_LIBSTD_GCC)
  : std::views::__adaptor::_RangeAdaptorClosure
#    endif
{
};
#else
using std::ranges::range_adaptor_closure;
#endif
}  // namespace xme::ranges