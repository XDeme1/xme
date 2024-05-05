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

const std::vector<std::int16_t> v16{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,
};
const std::vector<std::int32_t> v32{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,
};
const std::vector<std::int64_t> v64{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,
};

template<std::size_t size>
void std_find(benchmark::State& state) {
    for(auto&& _ : state) {
        if constexpr(size == 1)
            benchmark::DoNotOptimize(ranges::find(lorem, '5'));
        else if constexpr(size == 2)
            benchmark::DoNotOptimize(ranges::find(v16, 9));
        else if constexpr(size == 4)
            benchmark::DoNotOptimize(ranges::find(v32, 9));
        else if constexpr(size == 8)
            benchmark::DoNotOptimize(ranges::find(v64, 9));
    }
}

template<std::size_t size>
void xme_find(benchmark::State& state) {
    for(auto&& _ : state) {
        if constexpr(size == 1)
            benchmark::DoNotOptimize(xme::find(lorem, '5'));
        else if constexpr(size == 2)
            benchmark::DoNotOptimize(xme::find(v16, 9));
        else if constexpr(size == 4)
            benchmark::DoNotOptimize(xme::find(v32, 9));
        else if constexpr(size == 8)
            benchmark::DoNotOptimize(xme::find(v64, 9));
    }
}

BENCHMARK(std_find<1>);
BENCHMARK(std_find<2>);
BENCHMARK(std_find<4>);
BENCHMARK(std_find<8>);
BENCHMARK(xme_find<1>);
BENCHMARK(xme_find<2>);
BENCHMARK(xme_find<4>);
BENCHMARK(xme_find<8>);

BENCHMARK_MAIN();
