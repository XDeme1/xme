#pragma once
#include <functional>
#include <memory>

namespace xme {
template<typename F>
class Delegate;

template<typename R, typename... Args>
class Delegate<R(Args...)> {
public:
    constexpr Delegate() = default;

    template<typename Fn>
    constexpr Delegate(Fn func) :
      m_callable(std::make_unique<GenericCallable<Fn>>(std::move(func))) {}

    template<typename Fn>
    constexpr auto operator=(Fn func) -> Delegate& {
        m_callable = std::make_unique<GenericCallable<Fn>>(std::move(func));
        return *this;
    }

    constexpr auto operator()(Args... args) -> R { return m_callable->invoke(args...); }

    constexpr auto operator()(Args... args) const -> R { return m_callable->invoke(args...); }

private:
    struct ICallable {
        virtual constexpr ~ICallable() = default;

        virtual constexpr auto invoke(Args...) -> R = 0;
    };

    template<typename F>
    struct GenericCallable final : ICallable {
        constexpr GenericCallable(F fn) : callable(std::move(fn)) {}

        constexpr auto invoke(Args... args) -> R final { return std::invoke(callable, args...); }

        F callable;
    };

    std::unique_ptr<ICallable> m_callable = nullptr;
};
}  // namespace xme
