#include <benchmark/benchmark.h>
#include <execution>
#include <xme/core/algorithm/find.hpp>

const std::string lorem =
  "Lorem ipsum dolor sit amet consectetur adipisicing elit. Repellendus cupiditate ullam autem "
  "voluptate a sint dignissimos harum maiores sapiente incidunt? Atque, totam nisi voluptate eum "
  "officiis rerum sit eaque hic."
  "Lorem ipsum dolor sit amet consectetur adipisicing elit. Repellendus cupiditate ullam autem "
  "voluptate a sint dignissimos harum maiores sapiente incidunt? Atque, totam nisi voluptate eum "
  "officiis rerum sit eaque hic."
  "Lorem ipsum dolor sit amet consectetur adipisicing elit. Repellendus cupiditate ullam autem "
  "voluptate a sint dignissimos harum maiores sapiente incidunt? Atque, totam nisi voluptate eum "
  "officiis rerum sit eaque hic."
  "Lorem ipsum dolor sit amet consectetur adipisicing elit. Repellendus cupiditate ullam autem "
  "voluptate a sint dignissimos harum maiores sapiente incidunt? Atque, totam nisi voluptate eum "
  "officiis rerum5 sit eaque hic.";

void std_find(benchmark::State& state) {
    for(auto&& _ : state) {
        benchmark::DoNotOptimize(std::find(lorem.begin(), lorem.end(), '.'));
    }
}
BENCHMARK(std_find);

void xme_find(benchmark::State& state) {
    for(auto&& _ : state) {
        benchmark::DoNotOptimize(xme::find(lorem, '.'));
    }
}
BENCHMARK(xme_find);

BENCHMARK_MAIN();
