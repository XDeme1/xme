#pragma once
#include "os.hpp"
#include "architecture.hpp"

#include "generic_platform.hpp"

#if XME_PLATFORM_WINDOWS
#include "windows/platform.hpp"
#elif XME_PLATFORM_MAC
#include "mac/platform.hpp"
#elif XME_PLATFORM_LINUX
#include "linux/platform.hpp"
#endif