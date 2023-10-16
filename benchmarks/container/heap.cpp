#include <xme/container/heap.hpp>
#include <benchmark/benchmark.h>
#include <queue>
#include <cstdint>

struct T {
    ~T() {}

    constexpr auto operator<=>(const T&) const noexcept = default;
};

template<typename T>
void bench_emplace_xme(benchmark::State& state) {
    xme::Heap<T> heap;
    for(auto&& _ : state) {
        heap.emplace(T());
        benchmark::DoNotOptimize(heap);
    }
}

template<typename T>
void bench_emplace_std(benchmark::State& state) {
    std::priority_queue<T> heap;
    for(auto&& _ : state) {
        heap.emplace(T());
        benchmark::DoNotOptimize(heap);
    }
}

BENCHMARK(bench_emplace_xme<int64_t>);
BENCHMARK(bench_emplace_std<int64_t>);

BENCHMARK(bench_emplace_xme<T>);
BENCHMARK(bench_emplace_std<T>);
BENCHMARK_MAIN();