#pragma once
#include "architecture_detect.hpp"

#if XME_ARCH_X86
#include "arch/x86/cpu_features.hpp"
#endif

namespace xme {
class Architecture {
public:
    static auto cpuFeatures() {
#if XME_ARCH_X86
        return x86CpuFeatures();
#else
        return (char)0;
#endif 
    }
};
} // namespace xme