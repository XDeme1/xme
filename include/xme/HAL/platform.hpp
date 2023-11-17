#pragma once
#include "platform_macros.hpp"

#if XME_PLATFORM_WINDOWS
#include "./windows/platform.hpp"
#elif XME_PLATFORM_LINUX
#include "./linux/platform.hpp"
#endif
