#include "xme/core/algorithm/reverse.hpp"
#include <benchmark/benchmark.h>
#include <xme/core/algorithm/reverse.hpp>

template<std::size_t size>
void std_reverse(benchmark::State& state) {
    std::vector<std::uint8_t> v32(10000);
    for(auto&& _ : state) {
        if constexpr(size == 1) {
            benchmark::DoNotOptimize(std::ranges::reverse(v32));
        }
    }
}

template<std::size_t size>
void xme_reverse(benchmark::State& state) {
    std::vector<std::uint8_t> v32(10000);
    for(auto&& _ : state) {
        if constexpr(size == 1) {
            benchmark::DoNotOptimize(xme::reverse(v32));
        }
    }
}

// BENCHMARK(std_reverse<2>);
// BENCHMARK(std_reverse<4>);
// BENCHMARK(std_reverse<8>);
BENCHMARK(std_reverse<1>);
BENCHMARK(xme_reverse<1>);
// BENCHMARK(xme_reverse<2>);
// BENCHMARK(xme_reverse<4>);
// BENCHMARK(xme_reverse<8>);

BENCHMARK_MAIN();