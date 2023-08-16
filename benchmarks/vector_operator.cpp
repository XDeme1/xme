#include <xme/math/math.hpp>
#include <benchmark/benchmark.h>
#include <functional>
#include <memory>

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

void benchAddOperator(benchmark::State& state)
{
    Delegate<void(int)> d{[](int a){ (void)a; }};
    for(auto _ : state) {
        d(2);
        benchmark::DoNotOptimize(d);
    }
}
BENCHMARK(benchAddOperator);

BENCHMARK_MAIN();