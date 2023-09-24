#include "common.hpp"
#include <xme/functional/delegate.hpp>
#include <xme/functional/bind.hpp>

void staticTest(const char*) {}

struct Test {
    Test() {
        fn1 = [this]{ test(); };
    }

    void test() {
    }

    xme::Delegate<void()> fn1;
};

int main() {
    xme::Delegate<void()> fn1{[](){}};
    const xme::Delegate<void()> fn2{[](){}};

    xme::Delegate<void(int)> fn3{xme::bindFront([](int, int){}, 1)};
    const xme::Delegate<void(int)> fn4{xme::bindFront([](int, int){}, 1)};

    xme::Delegate<void(const char*)> fn5{&staticTest};
    const xme::Delegate<void(const char*)> fn6{&staticTest};

    Test t1;

    static_assert(std::invocable<decltype(fn1)>);
    static_assert(std::invocable<decltype(fn2)>);

    static_assert(std::invocable<decltype(fn3), int>);
    static_assert(std::invocable<decltype(fn4), int>);

    static_assert(std::invocable<decltype(fn5), char*>);
    static_assert(std::invocable<decltype(fn6), char*>);

    static_assert(std::invocable<decltype(t1.fn1)>);
}