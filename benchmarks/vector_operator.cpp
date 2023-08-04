#include <xme/math/math.hpp>
#include <benchmark/benchmark.h>

void benchAddOperator(benchmark::State& state)
{
    xme::Vector<float, 4> v{1, 2, 3, 4};
    for(auto _ : state) {
        auto r = v * 5;
        benchmark::DoNotOptimize(r);
    }
}
BENCHMARK(benchAddOperator);

BENCHMARK_MAIN();