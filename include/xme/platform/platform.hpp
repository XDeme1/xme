#pragma once
#include <string>
#include <string_view>

#include "os_detect.hpp"

#if XME_PLATFORM_LINUX
#include <dlfcn.h>
#endif

class Platform {
public:
    static constexpr auto getEnvironmentVariable(std::string_view variable_name) {
#if XME_PLATFORM_LINUX
        return ::secure_getenv(variable_name.data());
#endif
    }

    static constexpr void setEnvironmentVariable(std::string_view variable_name,
                                                 std::string_view value) {
#if XME_PLATFORM_LINUX
        if (value.empty())
            ::unsetenv(variable_name.data());
        else
            ::setenv(variable_name.data(), value.data(), true);
#endif
    }

#if defined(NDEBUG)
    static constexpr bool debug_enabled = false;
#else
    static constexpr bool debug_enabled = true;
#endif
};