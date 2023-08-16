#pragma once
#include <string>
#include <string_view>

#include "architecture.hpp"
#include "os_detect.hpp"

#if XME_PLATFORM_LINUX
#include <dlfcn.h>
#endif

class Platform {
public:
    static constexpr auto getEnvironmentVariable(std::string_view variableName) {
#if XME_PLATFORM_LINUX
        const char* result = ::secure_getenv(variableName.data());
        return (result == nullptr) ? std::string() : result;
#endif
    }

    static constexpr void setEnvironmentVariable(std::string_view variableName,
                                                 std::string_view value) {
#if XME_PLATFORM_LINUX
        if (value.empty())
            ::unsetenv(variableName.data());
        else
            ::setenv(variableName.data(), value.data(), true);
#endif
    }

#if defined(NDEBUG)
    static constexpr bool debugEnabled = false;
#else
    static constexpr bool debugEnabled = true;
#endif
};