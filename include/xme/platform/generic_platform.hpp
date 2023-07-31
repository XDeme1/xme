#pragma once

namespace xme {
    class GenericPlatform {
    public:
#if defined(NDEBUG)
        static constexpr bool debugEnabled = false;
#else
        static constexpr bool debugEnabled = true;
#endif
    };
}