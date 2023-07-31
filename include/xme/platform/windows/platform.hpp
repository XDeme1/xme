#pragma once
#include "../generic_platform.hpp"

#include <string>
#include <string_view>
#include <Windows.h>

namespace xme {
    class Platform : public GenericPlatform {
    public:
        Platform() = delete;

        static constexpr auto getEnvironmentVariable(std::string_view variableName) -> std::string
        {
            std::string result;
            return result;
        }

        static constexpr void setEnvironmentVariable(std::string_view variableName, std::string_view value) -> std::string
        {
            uint32_t error = ::SetEnvironmentVariable(variableName.data(), value.data());
            if(error == 0) { // Failed to set variable

            }
        }
    };
}