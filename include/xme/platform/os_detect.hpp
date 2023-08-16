#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define XME_PLATFORM_WINDOWS true
#else
#define XME_PLATFORM_WINDOWS false
#endif

#if defined(__APPLE__)
#define XME_PLATFORM_MAC true
#else
#define XME_PLATFORM_MAC false
#endif

#if defined(__linux__)
#define XME_PLATFORM_LINUX true
#else
#define XME_PLATFORM_LINUX false
#endif