#include <xme/core/functional/delegate.hpp>
#include <xme/core/functional/bind.hpp>
#include <iostream>

void static_test(const char*) {}

struct Test {
    Test() {
        fn1 = [this] { test(); };
    }

    void test() & {}

    xme::Delegate<void()> fn1;
};

int test_move_parameters() {
    int errors = 0;
    {
        std::string a = "Hello";
        xme::Delegate<void(std::string&&)> fn1{
            [](std::string&& b) { std::string a = std::move(b); }};
        fn1(std::move(a));
        bool error = !a.empty();
        if(error) {
            std::cerr << "xme::Delegate move parameters failed";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_move_parameters();

    xme::Delegate<void()> fn1{[]() {}};
    const xme::Delegate<void()> fn2{[]() {}};

    xme::Delegate<void(int)> fn3{xme::bind_front([](int, int) {}, 1)};
    const xme::Delegate<void(int)> fn4{xme::bind_front([](int, int) {}, 1)};

    xme::Delegate<void(const char*)> fn5{&static_test};
    const xme::Delegate<void(const char*)> fn6{&static_test};

    xme::Delegate<void()> fn7{[a = 0LL, b = 0LL, c = 0LL]() {}};
    const xme::Delegate<void()> fn8{[a = 0LL, b = 0LL, c = 0LL]() {}};
    Test t1;

    static_assert(std::invocable<decltype(fn1)>);
    static_assert(std::invocable<decltype(fn2)>);

    static_assert(std::invocable<decltype(fn3), int>);
    static_assert(std::invocable<decltype(fn4), int>);

    static_assert(std::invocable<decltype(fn5), char*>);
    static_assert(std::invocable<decltype(fn6), char*>);
    static_assert(std::invocable<decltype(fn7)>);
    static_assert(std::invocable<decltype(fn8)>);

    static_assert(std::invocable<decltype(t1.fn1)>);
    return errors;
}
