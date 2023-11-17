#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define XME_PLATFORM_WINDOWS true
#else
#define XME_PLATFORM_WINDOWS false
#endif

#if defined(__APPLE__)
#define XME_PLATFORM_APPLE true
#else
#define XME_PLATFORM_APPLE false
#endif

#if defined(__linux__)
#define XME_PLATFORM_LINUX true
#else
#define XME_PLATFORM_LINUX false
#endif

#if XME_PLATFORM_WINDOWS
#include "./windows/platform_macros.hpp"
#elif XME_PLATFORM_LINUX
#include "./linux/platform_macros.hpp"
#endif
