#pragma once
#include <algorithm>
#include <cstdint>
#include <string_view>
#include "os_detect.hpp"

#if XME_PLATFORM_WINDOWS
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
#include <dlfcn.h>
#endif

namespace xme {
class SharedLibrary {
public:
    constexpr SharedLibrary() noexcept = default;
    constexpr SharedLibrary(const SharedLibrary&) = delete;
    constexpr auto operator=(const SharedLibrary&) -> SharedLibrary& = delete;

    constexpr SharedLibrary(SharedLibrary&& rhs) noexcept : m_library(rhs.m_library) {
        rhs.m_library = nullptr;
    }

    constexpr auto operator=(SharedLibrary&& rhs) noexcept -> SharedLibrary& {
        std::ranges::swap(m_library, rhs.m_library);
        return *this;
    }

    constexpr SharedLibrary(std::string_view lib_name) noexcept { open(lib_name); }

    constexpr ~SharedLibrary() {
        if (m_library)
            close();
    }

    constexpr bool isOpen() const noexcept { return m_library != nullptr; }

    constexpr void open(std::string_view lib_name) {
#if XME_PLATFORM_WINDOWS
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
        m_library = dlopen(lib_name.data(), RTLD_NOW | RTLD_LOCAL);
#endif
    }

    constexpr void close() {
#if XME_PLATFORM_WINDOWS
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
        dlclose(m_library);
#endif
    }

    template<typename T>
    constexpr auto getProcAddress(std::string_view function) const noexcept {
#if XME_PLATFORM_WINDOWS
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
        return (T)dlsym(m_library, function.data());
#endif
    }

private:
#if XME_PLATFORM_WINDOWS
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
    void* m_library = nullptr;
#endif
};
} // namespace xme