#include <xme/core/functional/delegate.hpp>
#include <xme/core/functional/bind.hpp>
#include <benchmark/benchmark.h>

void function1024(benchmark::State& state) {
    std::vector<std::function<void()>> v;
    v.reserve(1024);
    for(std::size_t i = 0; i < 1024; ++i)
        v.emplace_back(xme::bind_front([](int a) {}, 1));
    for(auto&& _ : state) {
        for(auto&& f : v) {
            f();
            benchmark::DoNotOptimize(f);
        }
    }
}
BENCHMARK(function1024);

void delegate1024(benchmark::State& state) {
    std::vector<xme::Delegate<void()>> v;
    v.reserve(1024);
    for(std::size_t i = 0; i < 1024; ++i)
        v.emplace_back(xme::bind_front([](int a) {}, 1));
    for(auto&& _ : state) {
        for(auto&& f : v) {
            f();
            benchmark::DoNotOptimize(f);
        }
    }
}
BENCHMARK(delegate1024);

BENCHMARK_MAIN();
