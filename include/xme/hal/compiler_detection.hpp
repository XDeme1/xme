#pragma once

#if defined(__clang__)
#    define XME_COMPILER_CLANG
#elif defined(__GNUC__)
#    define XME_COMPILER_GCC
#endif