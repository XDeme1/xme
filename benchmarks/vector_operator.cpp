#include <xme/math/math.hpp>
#include <xme/math/simd/vector.hpp>
#include <benchmark/benchmark.h>
#include <functional>
#include <memory>
#include <xme/functional/delegate.hpp>
#include <forward_list>
/*
template<typename>
class Delegate;

template<typename R, typename... Args>
class Delegate<R(Args...)> {
public:
    template<typename Callable>
    constexpr Delegate(Callable callable)
        : m_Callable(std::make_unique<CallableImpl<Callable>>(std::move(callable))) {}

    constexpr Delegate() = default;

    constexpr R operator()(Args... args) { m_Callable->invoke(args...); }

private:
    struct ICallable {
        virtual constexpr R invoke(Args...) = 0;
        virtual ~ICallable() = default;
    };

    template<typename Callable>
    struct CallableImpl final : ICallable {
        constexpr CallableImpl(Callable callable)
            : m_CallableBuffer(std::move(callable)) {}

        constexpr R invoke(Args... args) final {
            return std::invoke(m_CallableBuffer, args...);
        }
        Callable m_CallableBuffer;
    };

    std::unique_ptr<ICallable> m_Callable = nullptr;
};
*/

constexpr void test(int a) {}

void benchAddOperator(benchmark::State& state)
{
    std::size_t a = 0;
    std::function<void(int)> fn{&test};
    for(auto _ : state) {
        fn(10);
        benchmark::DoNotOptimize(fn);
    }
}
BENCHMARK(benchAddOperator);

void benchAddOperator2(benchmark::State& state)
{
    std::size_t a = 0;
    xme::Delegate<void(int)> fn;
    fn.bind(&test);
    for(auto _ : state) {
        fn.execute(10);
        benchmark::DoNotOptimize(fn);
    }
}
BENCHMARK(benchAddOperator2);

BENCHMARK_MAIN();