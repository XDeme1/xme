#pragma once
#include <string_view>
#include <cstdlib>

namespace xme::hal {
constexpr auto get_environment_variable(std::string_view name) -> char* {
    return ::secure_getenv(name.data());
}

constexpr auto set_environment_variable(std::string_view name, std::string_view value) {
    if(value.length() == 0) {
        ::unsetenv(name.data());
    }
    else {
        ::setenv(name.data(), value.data(), true);
    }
}
}  // namespace xme::hal
