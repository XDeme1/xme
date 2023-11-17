#pragma once

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) | defined(__amd64__) \
    || defined(_M_AMD64)
#define XME_ARCH_X86 true
#else
#define XME_ARCH_X86 false
#endif

#if defined(__arm__) || defined(_M_ARM)
#define XME_ARCH_ARM true
#else
#define XME_ARCH_ARM false
#endif
