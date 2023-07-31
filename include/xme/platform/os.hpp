#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define XME_PLATFORM_WINDOWS true

#elif defined(__APPLE__)
#define XME_PLATFORM_MAC true

#elif defined(__ANDROID__)
#deinfe XME_PLATFORM_ANDROID true

#elif defined(__linux__)
#define XME_PLATFORM_LINUX true

#elif defined(__FreeBSD__)
#define XME_PLATFORM_FREEBSD true

el#if defined(__OpenBSD__)
#define XME_PLATFORM_OPENBSD 1

#endif

#if !defined(XME_PLATFORM_WINDOWS)
#define XME_PLATFORM_WINDOWS false
#endif

#if !defined(XME_PLATFORM_APPLE)
#define XME_PLATFORM_MAC false
#endif

#if !defined(XME_PLATFORM_ANDROID)
#define XME_PLATFORM_ANDROID false
#endif

#if !defined(XME_PLATFORM_LINUX)
#define XME_PLATFORM_LINUX false
#endif

#if !defined(XME_PLATFORM_FREEBSD)
#define XME_PLATFORM_FREEBSD false
#endif

#if !defined(XME_PLATFORM_OPENBSD)
#define XME_PLATFORM_OPENBSD false
#endif