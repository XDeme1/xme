#pragma once
#include "../generic_platform.hpp"

#include <string>
#include <string_view>
#include <cstdlib>
#include <cpuid.h>

namespace xme {
    class Platform : public GenericPlatform {
    public:
        Platform() = delete;

        static constexpr auto getEnvironmentVariable(std::string_view variableName) -> std::string
        {
            const char* result = ::secure_getenv(variableName.data()); 
            return (result == nullptr) ? std::string() : result;
        }

        static constexpr void setEnvironmentVariable(std::string_view variableName, std::string_view value)
        {
            if(value.empty())
                ::unsetenv(variableName.data());
            else
                ::setenv(variableName.data(), value.data(), true);
        } 
    };
}