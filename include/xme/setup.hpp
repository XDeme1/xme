#pragma once

#if defined(__GNUC__)
#    define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

#if defined(__cpp_concepts)
#    define XME_CONCEPT(Concept, T) Concept T
#    define XME_REQUIRES(Requires)  requires Requires
#else
#    define XME_CONCEPT(Co, T) typename T
#    define XME_REQUIRES(...)
#endif

#if defined(__cpp_constexpr)
#    define XME_CONSTEXPR constexpr
#    if __cpp_constexpr >= 201907 && (!defined(__GNUC__) || (110400 < GCC_VERSION))
#        define XME_CONSTEXPR20 constexpr
#    else
#        define XME_CONSTEXPR20
#    endif
#endif
