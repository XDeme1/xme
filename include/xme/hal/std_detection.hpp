#pragma once

#if defined(__LIBCPP_VERSION)
#    define XME_LIBSTD_CLANG
#elif defined(__GLIBCXX__)
#    define XME_LIBSTD_GCC
#endif