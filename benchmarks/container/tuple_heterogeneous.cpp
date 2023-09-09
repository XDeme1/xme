#include <vector>
#include <xme/container/container.hpp>
#include <benchmark/benchmark.h>

using std_hetero = std::tuple<std::int8_t, std::int8_t, std::int16_t, std::int32_t>;

using xme_hetero = xme::Tuple<std::int8_t, std::int8_t, std::int16_t, std::int32_t>;
                        
static_assert(sizeof(std_hetero) == 8);
static_assert(sizeof(xme_hetero) == 8);

template<typename T>
void benchCopy(benchmark::State& state, T value) {
    T dest;
    for(auto _ : state) {
        dest = value;
        benchmark::DoNotOptimize(dest);
    }
}

std::vector<std_hetero> std_hetero_4(4);
std::vector<std_hetero> std_hetero_8(8);
std::vector<std_hetero> std_hetero_16(16);
std::vector<std_hetero> std_hetero_32(32);
std::vector<std_hetero> std_hetero_64(64);
std::vector<std_hetero> std_hetero_128(128);
std::vector<std_hetero> std_hetero_256(256);
std::vector<std_hetero> std_hetero_512(512);
std::vector<std_hetero> std_hetero_1024(1024);

std::vector<xme_hetero> xme_hetero_4(4);
std::vector<xme_hetero> xme_hetero_8(8);
std::vector<xme_hetero> xme_hetero_16(16);
std::vector<xme_hetero> xme_hetero_32(32);
std::vector<xme_hetero> xme_hetero_64(64);
std::vector<xme_hetero> xme_hetero_128(128);
std::vector<xme_hetero> xme_hetero_256(256);
std::vector<xme_hetero> xme_hetero_512(512);
std::vector<xme_hetero> xme_hetero_1024(1024);

BENCHMARK_CAPTURE(benchCopy, std_hetero_4, std_hetero_4);
BENCHMARK_CAPTURE(benchCopy, std_hetero_8, std_hetero_8);
BENCHMARK_CAPTURE(benchCopy, std_hetero_16, std_hetero_16);
BENCHMARK_CAPTURE(benchCopy, std_hetero_32, std_hetero_32);
BENCHMARK_CAPTURE(benchCopy, std_hetero_64, std_hetero_64);
BENCHMARK_CAPTURE(benchCopy, std_hetero_128, std_hetero_128);
BENCHMARK_CAPTURE(benchCopy, std_hetero_256, std_hetero_256);
BENCHMARK_CAPTURE(benchCopy, std_hetero_512, std_hetero_512);
BENCHMARK_CAPTURE(benchCopy, std_hetero_1024, std_hetero_1024);

BENCHMARK_CAPTURE(benchCopy, xme_hetero_4, xme_hetero_4);
BENCHMARK_CAPTURE(benchCopy, xme_hetero_8, xme_hetero_8);
BENCHMARK_CAPTURE(benchCopy, xme_hetero_16, xme_hetero_16);
BENCHMARK_CAPTURE(benchCopy, xme_hetero_32, xme_hetero_32);
BENCHMARK_CAPTURE(benchCopy, xme_hetero_64, xme_hetero_64);
BENCHMARK_CAPTURE(benchCopy, xme_hetero_128, xme_hetero_128);
BENCHMARK_CAPTURE(benchCopy, xme_hetero_256, xme_hetero_256);
BENCHMARK_CAPTURE(benchCopy, xme_hetero_512, xme_hetero_512);
BENCHMARK_CAPTURE(benchCopy, xme_hetero_1024, xme_hetero_1024);

BENCHMARK_MAIN();