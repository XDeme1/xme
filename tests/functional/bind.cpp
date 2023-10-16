#include <xme/functional/bind.hpp>
#include "common.hpp"

int main() {
    int errors = 0;
    {
        auto fn1 = xme::bind_front([](){});
        static_assert(sizeof(decltype(fn1)) == 1);

        auto fn2 = xme::bind_back([](){});
        static_assert(sizeof(decltype(fn2)) == 1);
    }

    {
        auto fn1 = xme::bind_front([](int, int&, int&&) {});

        static_assert(std::is_invocable_v<decltype(fn1), int, int&, int>);
        static_assert(std::is_invocable_v<decltype(fn1), int, int&, int&&>);
        static_assert(std::is_invocable_v<decltype(fn1), int&, int&, int&&>);
        static_assert(std::is_invocable_v<decltype(fn1), int&&, int&, int&&>);

        auto fn2 = xme::bind_front([](int&&, const int&, const int&&){}, 1);

        static_assert(std::is_invocable_v<decltype(fn2), int&, int&&>);
        static_assert(std::is_invocable_v<decltype(fn2), const int&, const int&&>);
        static_assert(std::is_invocable_v<decltype(fn2), int, int>);

        auto fn3 = xme::bind_back([](int, int&, int&&){});

        static_assert(std::is_invocable_v<decltype(fn3), int, int&, int>);
        static_assert(std::is_invocable_v<decltype(fn3), int, int&, int&&>);
        static_assert(std::is_invocable_v<decltype(fn3), int&, int&, int&&>);
        static_assert(std::is_invocable_v<decltype(fn3), int&&, int&, int&&>);

        auto fn4 = xme::bind_back([](const int&, const int&&, int&&){}, 5);
        static_assert(std::is_invocable_v<decltype(fn4), int&, int&&>);
        static_assert(std::is_invocable_v<decltype(fn4), const int&, const int&&>);
        static_assert(std::is_invocable_v<decltype(fn4), int, int>);
    }

    {
        std::vector<short> results;
        auto fn1 = xme::bind_front([](int a, int b){ return xme::Tuple{a, b}; }, 5);
        {
            auto r = fn1(3);
            results.emplace_back(get<0>(r) == 5);
            results.emplace_back(get<1>(r) == 3);
        }

        auto fn2 = xme::bind_back([](int a, int b){ return xme::Tuple{a, b}; }, 5);
        {
            auto r = fn2(3);
            results.emplace_back(get<0>(r) == 3);
            results.emplace_back(get<1>(r) == 5);
        }

        bool error = std::ranges::any_of(results, [](bool b){ return b == false; });
        if(error) {
            std::cerr << "bind(Back|Front) variable binding place error\n";
            ++errors;
        }
    }
    return errors;
}