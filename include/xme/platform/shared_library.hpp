#pragma once
#include <algorithm>
#include <string_view>
#include <cstdint>
#include "os.hpp"

#if XME_PLATFORM_WINDOWS
using HINSTANCE = struct HINSTANCE__*;
typedef std::int64_t( __stdcall * FARPROC )();

extern "C" __declspec(dllimport) HINSTANCE __stdcall LoadLibraryA(const char* lpLibFileName);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HINSTANCE hLibModule);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HINSTANCE hModule, const char* lpProcName);
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
#include <dlfcn.h>
#endif

namespace xme {
    class SharedLibrary {
    public:
        constexpr SharedLibrary() noexcept = default;
        constexpr SharedLibrary(const SharedLibrary&) = delete;
        constexpr SharedLibrary(SharedLibrary&& rhs) noexcept
            : m_Library(rhs.m_Library)
        { rhs.m_Library = nullptr; }

        constexpr auto operator=(const SharedLibrary&) -> SharedLibrary& = delete;
        constexpr auto operator=(SharedLibrary&& rhs) noexcept -> SharedLibrary&
        {
            std::ranges::swap(m_Library, rhs.m_Library);
            return *this;
        }

        constexpr SharedLibrary(std::string_view libName) noexcept
        { open(libName); }

        constexpr ~SharedLibrary()
        {
            if(m_Library)
                close();
        }

        constexpr bool isOpen() const noexcept
        { return m_Library != nullptr; }

        constexpr void open(std::string_view libName)
        {
#if XME_PLATFORM_WINDOWS
            m_Library = ::LoadLibraryA(libName.data());
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
            m_Library = dlopen(libName.data(), RTLD_NOW | RTLD_LOCAL);
#endif
        }

        constexpr void close()
        {
#if XME_PLATFORM_WINDOWS
            ::FreeLibrary(m_Library);
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
            dlclose(m_Library);
#endif
        }

        template<typename T>
        constexpr auto getProcAddress(std::string_view function) const noexcept -> T
        {
#if XME_PLATFORM_WINDOWS
            return (T)::GetProcAddress(m_Library, function.data());
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
            return (T)dlsym(m_Library, function.data());
#endif
        }

    private:
#if XME_PLATFORM_WINDOWS
        HINSTANCE m_Library = nullptr;
#elif XME_PLATFORM_LINUX || XME_PLATFORM_MAC
        void* m_Library = nullptr;
#endif
    };
}