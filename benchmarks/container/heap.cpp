#include <xme/container/heap.hpp>
#include <benchmark/benchmark.h>
#include <queue>
#include <cstdint>

struct T {
    ~T() {}

    constexpr auto operator<=>(const T&) const noexcept = default;
};

template<typename T>
void benchEmplaceXme(benchmark::State& state) {
    xme::Heap<T> heap;
    for(auto&& _ : state) {
        heap.emplace(T());
        benchmark::DoNotOptimize(heap);
    }
}

template<typename T>
void benchEmplaceStd(benchmark::State& state) {
    std::priority_queue<T> heap;
    for(auto&& _ : state) {
        heap.emplace(T());
        benchmark::DoNotOptimize(heap);
    }
}

BENCHMARK(benchEmplaceXme<int64_t>);
BENCHMARK(benchEmplaceStd<int64_t>);

BENCHMARK(benchEmplaceXme<T>);
BENCHMARK(benchEmplaceStd<T>);
BENCHMARK_MAIN();