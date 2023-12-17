#pragma once
#include <xme/setup.hpp>

#if defined(XME_CPP23) && __cpp_lib_ranges >= 202202L  // std::ranges::range_adaptor_closure
#    define XME_RANGE_ADAPTOR_CLOSURE(T) std::ranges::range_adaptor_closure<T>
#elif defined(_LIBCPP_VERSION)
#    define XME_RANGE_ADAPTOR_CLOSURE(T) std::__range_adaptor_closure<T>
#elif defined(__GLIBCXX__)
#    define XME_RANGE_ADAPTOR_CLOSURE(T) std::views::__adaptor::_RangeAdaptorClosure
#else
#    error "Range adaptor closure not yet supported"
#endif
