#pragma once

#if defined(__GNUC__)
#    define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

#if defined(__cpp_constexpr)
#    define XME_CONSTEXPR constexpr
#    if __cpp_constexpr >= 201907 && (!defined(__GNUC__) || (110400 < GCC_VERSION))
#        define XME_CONSTEXPR20 constexpr
#    else
#        define XME_CONSTEXPR20
#    endif
#endif

#if defined(__clang__)
#    if __has_attribute(always_inline)
#        define XME_INLINE __attribute__((always_inline)) __inline__
#    else
#        define XME_INLINE inline
#    endif
#elif defined(__GNUC__)
#    define XME_INLINE __attribute__((always_inline)) __inline__
#elif defined(_MSC_VER)
#    define XME_INLINE inline
#else
#    define XME_INLINE inline
#endif
