#pragma once

#if __cplusplus >= 202302L
#    define XME_CPP23
#elif __cplusplus >= 202002L
#    define XME_CPP20
#endif

#if defined(__cpp_constexpr)
#    define XME_CONSTEXPR constexpr
#    if __cpp_constexpr >= 202002L
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
