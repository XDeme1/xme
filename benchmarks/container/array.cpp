#include <xme/container/array.hpp>
#include <benchmark/benchmark.h>
#include <vector>
#include <cstdint>
#include <range/v3/range.hpp>

enum class ELib {
    xme,
    std,
};

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

template<typename T, ELib l>
void bench_insert(benchmark::State& state) {
    for(auto&& _ : state) {
        if constexpr(l == ELib::xme) {
            xme::Array<T> arr;
            arr.insert(ranges::cbegin(arr), T());
            benchmark::DoNotOptimize(arr.data());
        }
        else {
            std::vector<T> arr;
            arr.insert(arr.cbegin(), T());
            benchmark::DoNotOptimize(arr.data());
        }
    }
}

template<typename T, ELib l>
void bench_fill_constructor(benchmark::State& state) {
    for(auto&& _ : state) {
        if constexpr(l == ELib::xme) {
            xme::Array<T> arr(8, T());
            benchmark::DoNotOptimize(arr.data());
        }
        else {
            std::vector<T> arr(8, T());
            benchmark::DoNotOptimize(arr.data());
        }
    }
}

BENCHMARK(bench_push_xme<int64_t>);
BENCHMARK(bench_push_std<int64_t>);
BENCHMARK(bench_push_xme<T>);
BENCHMARK(bench_push_std<T>);

BENCHMARK(bench_insert<int64_t, ELib::xme>);
BENCHMARK(bench_insert<int64_t, ELib::std>);

BENCHMARK(bench_insert<T, ELib::xme>);
BENCHMARK(bench_insert<T, ELib::std>);

BENCHMARK(bench_fill_constructor<int64_t, ELib::xme>);
BENCHMARK(bench_fill_constructor<int64_t, ELib::std>);
BENCHMARK(bench_fill_constructor<T, ELib::xme>);
BENCHMARK(bench_fill_constructor<T, ELib::std>);
BENCHMARK_MAIN();
