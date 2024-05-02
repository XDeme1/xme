#include <benchmark/benchmark.h>
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

const std::vector<double> v64{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,
};

void std_find(benchmark::State& state) {
    for(auto&& _ : state) {
        benchmark::DoNotOptimize(ranges::find(v64, 9));
    }
}
BENCHMARK(std_find);

void xme_find(benchmark::State& state) {
    for(auto&& _ : state) {
        benchmark::DoNotOptimize(xme::find(v64, 9));
    }
}
BENCHMARK(xme_find);

BENCHMARK_MAIN();
