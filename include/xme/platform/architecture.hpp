#pragma once
#include "architecture_detect.hpp"

#if XME_ARCH_X86
#include "arch/x86/cpu_features.hpp"
#endif

namespace xme {
class Architecture {
public:
    static auto cpu_features() {
#if XME_ARCH_X86
        return x86_cpu_features();
#else
        return (char)0;
#endif 
    }
};
} // namespace xme