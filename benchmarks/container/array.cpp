#include <xme/container/array.hpp>
#include <benchmark/benchmark.h>
#include <vector>
#include <cstdint>

struct T {
    ~T() {}
};

template<typename T>
void benchPushXme(benchmark::State& state) {
    xme::Array<int64_t> arr(10'000);
    for(auto&& _ : state) {
        arr.emplaceBack();
        benchmark::DoNotOptimize(arr.data());
    }
}

template<typename T>
void benchPushStd(benchmark::State& state) {
    std::vector<int64_t> arr;
    arr.reserve(10'000);
    for(auto&& _ : state) {
        arr.emplace_back();
        benchmark::DoNotOptimize(arr.data());
    }
}

template<typename T>
void benchInsertXme(benchmark::State& state) {
    xme::Array<T> arr;
    for(auto&& _ : state) {
        arr.insert(arr.cbegin(), T());
        benchmark::DoNotOptimize(arr.data());
    }
}

template<typename T>
void benchInsertStd(benchmark::State& state) {
    std::vector<T> arr;
    for(auto&& _ : state) {
        arr.insert(arr.cbegin(), T());
        benchmark::DoNotOptimize(arr.data());
    }
}
BENCHMARK(benchPushStd<int64_t>);
BENCHMARK(benchPushXme<int64_t>);
BENCHMARK(benchPushStd<T>);
BENCHMARK(benchPushXme<T>);

BENCHMARK(benchInsertStd<int64_t>);
BENCHMARK(benchInsertXme<int64_t>);

BENCHMARK(benchInsertStd<T>);
BENCHMARK(benchInsertXme<T>);
BENCHMARK_MAIN();