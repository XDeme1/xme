#include <vector>
#include <xme/container/container.hpp>
#include <benchmark/benchmark.h>
#include <cstdint>

using std_homo = std::tuple<std::int16_t, std::int16_t, std::int16_t, std::int16_t>;

using xme_homo = xme::Tuple<std::int16_t, std::int16_t, std::int16_t, std::int16_t>;
                        
static_assert(sizeof(std_homo) == 8);
static_assert(sizeof(xme_homo) == 8);

template<typename T>
void benchCopy(benchmark::State& state, T value) {
    T dest;
    for(auto _ : state) {
        dest = value;
        benchmark::DoNotOptimize(dest);
    }
}

std::vector<std_homo> std_homo_4(4);
std::vector<std_homo> std_homo_8(8);
std::vector<std_homo> std_homo_16(16);
std::vector<std_homo> std_homo_32(32);
std::vector<std_homo> std_homo_64(64);
std::vector<std_homo> std_homo_128(128);
std::vector<std_homo> std_homo_256(256);
std::vector<std_homo> std_homo_512(512);
std::vector<std_homo> std_homo_1024(1024);

std::vector<xme_homo> xme_homo_4(4);
std::vector<xme_homo> xme_homo_8(8);
std::vector<xme_homo> xme_homo_16(16);
std::vector<xme_homo> xme_homo_32(32);
std::vector<xme_homo> xme_homo_64(64);
std::vector<xme_homo> xme_homo_128(128);
std::vector<xme_homo> xme_homo_256(256);
std::vector<xme_homo> xme_homo_512(512);
std::vector<xme_homo> xme_homo_1024(1024);

BENCHMARK_CAPTURE(benchCopy, std_homo_4, std_homo_4);
BENCHMARK_CAPTURE(benchCopy, std_homo_8, std_homo_8);
BENCHMARK_CAPTURE(benchCopy, std_homo_16, std_homo_16);
BENCHMARK_CAPTURE(benchCopy, std_homo_32, std_homo_32);
BENCHMARK_CAPTURE(benchCopy, std_homo_64, std_homo_64);
BENCHMARK_CAPTURE(benchCopy, std_homo_128, std_homo_128);
BENCHMARK_CAPTURE(benchCopy, std_homo_256, std_homo_256);
BENCHMARK_CAPTURE(benchCopy, std_homo_512, std_homo_512);
BENCHMARK_CAPTURE(benchCopy, std_homo_1024, std_homo_1024);

BENCHMARK_CAPTURE(benchCopy, xme_homo_4, xme_homo_4);
BENCHMARK_CAPTURE(benchCopy, xme_homo_8, xme_homo_8);
BENCHMARK_CAPTURE(benchCopy, xme_homo_16, xme_homo_16);
BENCHMARK_CAPTURE(benchCopy, xme_homo_32, xme_homo_32);
BENCHMARK_CAPTURE(benchCopy, xme_homo_64, xme_homo_64);
BENCHMARK_CAPTURE(benchCopy, xme_homo_128, xme_homo_128);
BENCHMARK_CAPTURE(benchCopy, xme_homo_256, xme_homo_256);
BENCHMARK_CAPTURE(benchCopy, xme_homo_512, xme_homo_512);
BENCHMARK_CAPTURE(benchCopy, xme_homo_1024, xme_homo_1024);

BENCHMARK_MAIN();