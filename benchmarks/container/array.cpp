#include <xme/container/array.hpp>
#include <benchmark/benchmark.h>
#include <vector>
#include <cstdint>

struct T {
    ~T() {}
};

template<typename T>
void benchPushXme(benchmark::State& state) {
    for(auto&& _ : state) {
        xme::Array<int64_t> arr(10'000);
        for(auto i = 0; i < 10'000; ++i)
            arr.emplaceBack();
        benchmark::DoNotOptimize(arr);
    }
}

template<typename T>
void benchPushStd(benchmark::State& state) {
    for(auto&& _ : state) {
        std::vector<int64_t> arr;
        arr.reserve(10'000);
        for(auto i = 0; i < 10'000; ++i)
            arr.emplace_back();
        benchmark::DoNotOptimize(arr);
    }
}

BENCHMARK(benchPushStd<int64_t>);
BENCHMARK(benchPushXme<int64_t>);
BENCHMARK(benchPushStd<T>);
BENCHMARK(benchPushXme<T>);

BENCHMARK_MAIN();