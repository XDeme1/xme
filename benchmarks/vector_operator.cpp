#include <xme/math/math.hpp>
#include <xme/math/simd/vector.hpp>
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
    xme::dvec4 a{5};
    xme::dvec4 b{2};
    for(auto _ : state) {
        xme::dvec4 c = a / b;
        benchmark::DoNotOptimize(c);
    }
}
BENCHMARK(benchAddOperator);

void benchAddOperator2(benchmark::State& state)
{
    xme::dvec4_simd a{5, 5, 5, 5};
    xme::dvec4_simd b{2, 2, 2, 2};
    for(auto _ : state) {
        xme::dvec4_simd c = xme::vec4Div(a, b);
        benchmark::DoNotOptimize(c);
    }
}
BENCHMARK(benchAddOperator2);

BENCHMARK_MAIN();