#pragma once
#include <cstdint>

#ifdef _WIN32
#include <intrin.h>
#else
#include <cpuid.h>
#endif

namespace xme {

// https://en.m.wikipedia.org/wiki/CPUID
struct X86CpuFeatures {
    struct {
        std::uint32_t fpu : 1 = false;
        std::uint32_t vme : 1 = false;
        std::uint32_t de : 1 = false;
        std::uint32_t pse : 1 = false;
        std::uint32_t tsc : 1 = false;
        std::uint32_t msr : 1 = false;
        std::uint32_t pae : 1 = false;
        std::uint32_t mce : 1 = false;
        std::uint32_t cx8 : 1 = false;
        std::uint32_t apic : 1 = false;
        std::uint32_t _reserved : 1 = false;
        std::uint32_t sep : 1 = false;
        std::uint32_t mtrr : 1 = false;
        std::uint32_t pge : 1 = false;
        std::uint32_t mca : 1 = false;
        std::uint32_t cmov : 1 = false;
        std::uint32_t pat : 1 = false;
        std::uint32_t pse_36 : 1 = false;
        std::uint32_t psn : 1 = false;
        std::uint32_t clfsh : 1 = false;
        std::uint32_t nx : 1 = false;
        std::uint32_t ds : 1 = false;
        std::uint32_t acpi : 1 = false;
        std::uint32_t mmx : 1 = false;
        std::uint32_t fxsr : 1 = false;
        std::uint32_t sse : 1 = false;
        std::uint32_t sse2 : 1 = false;
        std::uint32_t ss : 1 = false;
        std::uint32_t htt : 1 = false;
        std::uint32_t tm : 1 = false;
        std::uint32_t ia64 : 1 = false;
        std::uint32_t pbe : 1 = false;
    } info1;

    struct {
        std::uint32_t sse3 : 1 = false;
        std::uint32_t pclmulqdq : 1 = false;
        std::uint32_t dtes64 : 1 = false;
        std::uint32_t monitor : 1 = false;
        std::uint32_t ds_cpl : 1 = false;
        std::uint32_t vmx : 1 = false;
        std::uint32_t smx : 1 = false;
        std::uint32_t est : 1 = false;
        std::uint32_t tm2 : 1 = false;
        std::uint32_t ssse3 : 1 = false;
        std::uint32_t cnxt_id : 1 = false;
        std::uint32_t sdbg : 1 = false;
        std::uint32_t fma : 1 = false;
        std::uint32_t cx16 : 1 = false;
        std::uint32_t xtpr : 1 = false;
        std::uint32_t pdcm : 1 = false;
        std::uint32_t _reserved : 1 = false;
        std::uint32_t pcid : 1 = false;
        std::uint32_t dca : 1 = false;
        std::uint32_t sse41 : 1 = false;
        std::uint32_t sse42 : 1 = false;
        std::uint32_t x2apic : 1 = false;
        std::uint32_t movbe : 1 = false;
        std::uint32_t popcnt : 1 = false;
        std::uint32_t tsc_deadline : 1 = false;
        std::uint32_t aes_ni : 1 = false;
        std::uint32_t xsave : 1 = false;
        std::uint32_t osxsave : 1 = false;
        std::uint32_t avx : 1 = false;
        std::uint32_t f16c : 1 = false;
        std::uint32_t rdrnd : 1 = false;
        std::uint32_t hypervisor : 1 = false;
    } info2;
};

inline void cpuid(int leaf, std::uint32_t& eax, std::uint32_t& ebx, std::uint32_t& ecx,
                  std::uint32_t& edx) {
#ifdef _WIN32
    std::uint32_t registers[4];
    __cpuid(static_cast<int*>(registers), leaf);
    *eax = registers[0];
    *ebx = registers[1];
    *ecx = registers[2];
    *edx = registers[3];
#else
    __cpuid(leaf, eax, ebx, ecx, edx);
#endif
}

inline void cpuidex(int leaf, int count, std::uint32_t& eax, std::uint32_t& ebx,
                    std::uint32_t& ecx, std::uint32_t& edx) {
#ifdef _WIN32
    std::uint32_t registers[4];
    __cpuidex(static_cast<int*>(registers), leaf, count);
    *eax = registers[0];
    *ebx = registers[1];
    *ecx = registers[2];
    *edx = registers[3];
#else
    __cpuid_count(leaf, count, eax, ebx, ecx, edx);
#endif
}

inline auto x86_cpu_features() {
    std::uint32_t max_leaf;
    std::uint32_t eax, ebx, ecx, edx;

    // cpuid should be called with leaf = 0 first, as this will store
    // in the eax parameter the highest leaf calling parameter
    // the cpu implements
    cpuid(0, max_leaf, ebx, ecx, edx);
    cpuid(1, eax, ebx, ecx, edx);

    X86CpuFeatures cpu_features{
        .info1{
            .fpu = static_cast<bool>(edx & 0x1),
            .vme = static_cast<bool>(edx & 0x2),
            .de = static_cast<bool>(edx & 0x4),
            .pse = static_cast<bool>(edx & 0x8),
            .tsc = static_cast<bool>(edx & 0x10),
            .msr = static_cast<bool>(edx & 0x20),
            .pae = static_cast<bool>(edx & 0x40),
            .mce = static_cast<bool>(edx & 0x80),

            .cx8 = static_cast<bool>(edx & 0x1'00),
            .apic = static_cast<bool>(edx & 0x2'00),
            ._reserved = static_cast<bool>(edx & 0x4'00),
            .sep = static_cast<bool>(edx & 0x8'00),
            .mtrr = static_cast<bool>(edx & 0x10'00),
            .pge = static_cast<bool>(edx & 0x20'00),
            .mca = static_cast<bool>(edx & 0x40'00),
            .cmov = static_cast<bool>(edx & 0x80'00),

            .pat = static_cast<bool>(edx & 0x1'00'00),
            .pse_36 = static_cast<bool>(edx & 0x2'00'00),
            .psn = static_cast<bool>(edx & 0x4'00'00),
            .clfsh = static_cast<bool>(edx & 0x8'00'00),
            .nx = static_cast<bool>(edx & 0x10'00'00),
            .ds = static_cast<bool>(edx & 0x20'00'00),
            .acpi = static_cast<bool>(edx & 0x40'00'00),
            .mmx = static_cast<bool>(edx & 0x80'00'00),

            .fxsr = static_cast<bool>(edx & 0x1'00'00'00),
            .sse = static_cast<bool>(edx & 0x2'00'00'00),
            .sse2 = static_cast<bool>(edx & 0x4'00'00'00),
            .ss = static_cast<bool>(edx & 0x8'00'00'00),
            .htt = static_cast<bool>(edx & 0x10'00'00'00),
            .tm = static_cast<bool>(edx & 0x20'00'00'00),
            .ia64 = static_cast<bool>(edx & 0x40'00'00'00),
            .pbe = static_cast<bool>(edx & 0x80'00'00'00),
        },

        .info2{
            .sse3 = static_cast<bool>(ecx & 0x1),
            .pclmulqdq = static_cast<bool>(ecx & 0x2),
            .dtes64 = static_cast<bool>(ecx & 0x4),
            .monitor = static_cast<bool>(ecx & 0x8),
            .ds_cpl = static_cast<bool>(ecx & 0x10),
            .vmx = static_cast<bool>(ecx & 0x20),
            .smx = static_cast<bool>(ecx & 0x40),
            .est = static_cast<bool>(ecx & 0x80),

            .tm2 = static_cast<bool>(ecx & 0x1'00),
            .ssse3 = static_cast<bool>(ecx & 0x2'00),
            .cnxt_id = static_cast<bool>(ecx & 0x4'00),
            .sdbg = static_cast<bool>(ecx & 0x8'00),
            .fma = static_cast<bool>(ecx & 0x10'00),
            .cx16 = static_cast<bool>(ecx & 0x20'00),
            .xtpr = static_cast<bool>(ecx & 0x40'00),
            .pdcm = static_cast<bool>(ecx & 0x80'00),

            ._reserved = static_cast<bool>(ecx & 0x1'00'00),
            .pcid = static_cast<bool>(ecx & 0x2'00'00),
            .dca = static_cast<bool>(ecx & 0x4'00'00),
            .sse41 = static_cast<bool>(ecx & 0x8'00'00),
            .sse42 = static_cast<bool>(ecx & 0x10'00'00),
            .x2apic = static_cast<bool>(ecx & 0x20'00'00),
            .movbe = static_cast<bool>(ecx & 0x40'00'00),
            .popcnt = static_cast<bool>(ecx & 0x80'00'00),

            .tsc_deadline = static_cast<bool>(ecx & 0x1'00'00'00),
            .aes_ni = static_cast<bool>(ecx & 0x2'00'00'00),
            .xsave = static_cast<bool>(ecx & 0x4'00'00'00),
            .osxsave = static_cast<bool>(ecx & 0x8'00'00'00),
            .avx = static_cast<bool>(ecx & 0x10'00'00'00),
            .f16c = static_cast<bool>(ecx & 0x20'00'00'00),
            .rdrnd = static_cast<bool>(ecx & 0x40'00'00'00),
            .hypervisor = static_cast<bool>(ecx & 0x80'00'00'00),
        },
    };

    if(max_leaf >= 7) {
        //cpuidex(7, 0, eax, ebx, ecx, edx);
    }
    return cpu_features;
}
} // namespace xme