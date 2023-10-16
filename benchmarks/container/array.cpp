#include <xme/container/array.hpp>
#include <benchmark/benchmark.h>
#include <vector>
#include <cstdint>

struct T {
    ~T() {}
};

template<typename T>
void bench_push_xme(benchmark::State& state) {
    xme::Array<int64_t> arr(10'000);
    for(auto&& _ : state) {
        arr.emplace_back();
        benchmark::DoNotOptimize(arr.data());
    }
}

template<typename T>
void bench_push_std(benchmark::State& state) {
    std::vector<int64_t> arr;
    arr.reserve(10'000);
    for(auto&& _ : state) {
        arr.emplace_back();
        benchmark::DoNotOptimize(arr.data());
    }
}

template<typename T>
void bench_insert_xme(benchmark::State& state) {
    xme::Array<T> arr;
    for(auto&& _ : state) {
        arr.insert(arr.cbegin(), T());
        benchmark::DoNotOptimize(arr.data());
    }
}

template<typename T>
void bench_insert_std(benchmark::State& state) {
    std::vector<T> arr;
    for(auto&& _ : state) {
        arr.insert(arr.cbegin(), T());
        benchmark::DoNotOptimize(arr.data());
    }
}
BENCHMARK(bench_push_std<int64_t>);
BENCHMARK(bench_push_xme<int64_t>);
BENCHMARK(bench_push_std<T>);
BENCHMARK(bench_push_xme<T>);

BENCHMARK(bench_insert_std<int64_t>);
BENCHMARK(bench_insert_xme<int64_t>);

BENCHMARK(bench_insert_std<T>);
BENCHMARK(bench_insert_xme<T>);
BENCHMARK_MAIN();