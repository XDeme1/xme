#pragma once
#include "../common.hpp"

int main() {
    int errors = 0;
    {
        xme::Tuple<int, int> t1{1, 5};
        xme::Tuple<int, float> t2{3, 1.5};
        xme::Tuple<std::string> t3{"Hello"};

        static_assert(std::is_trivially_assignable_v<decltype(t1), decltype(t1)>);
        static_assert(!std::is_trivially_assignable_v<decltype(t1), decltype(t2)>);
        static_assert(!std::is_trivially_assignable_v<xme::Tuple<std::string>,
                                                      xme::Tuple<std::string>>);

        std::vector<short> results{};

        t1 = xme::Tuple{5, 3};
        results.emplace_back(get<0>(t1) == 5);
        results.emplace_back(get<1>(t1) == 3);

        t1 = t2;
        results.emplace_back(get<0>(t1) == 3);
        results.emplace_back(get<1>(t1) == 1);
        results.emplace_back(get<0>(t3) == "Hello");

        xme::Tuple<std::string> t4{"Test"};
        xme::Tuple<std::string> t5{"Test2"};
        t3 = t4;
        results.emplace_back(get<0>(t3) == "Test");
        results.emplace_back(get<0>(t4) == "Test");

        t3 = std::move(t5);
        results.emplace_back(get<0>(t3) == "Test2");
        results.emplace_back(get<0>(t5).empty());

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Tuple operator=(U&&) error\n";
        }
    }

    {
        xme::Tuple<int, int> t1{5, 1};
        t1.assign(1, 2);
        using assign1_t = void (xme::Tuple<int, int>::*)(int&, int&);
        using assign2_t = void (xme::Tuple<int, int>::*)(int&&, int&&);

        static_assert(std::invocable<decltype(static_cast<assign1_t>(
                                         &decltype(t1)::assign<int&, int&>)),
                                     decltype(t1), int&, int&>);

        static_assert(!std::invocable<decltype(static_cast<assign1_t>(
                                          &decltype(t1)::assign<int&, int&>)),
                                      decltype(t1), int&>);

        static_assert(!std::invocable<decltype(static_cast<assign1_t>(
                                          &decltype(t1)::assign<int&, int&>)),
                                      decltype(t1), int&, int&, int&>);

        static_assert(std::invocable<decltype(static_cast<assign2_t>(
                                         &decltype(t1)::assign<int&&, int&&>)),
                                     decltype(t1), int, int>);

        static_assert(std::invocable<decltype(static_cast<assign2_t>(
                                         &decltype(t1)::assign<int&&, int&&>)),
                                     decltype(t1), int&&, int&&>);

        std::vector<short> results;
        results.emplace_back(get<0>(t1) == 1);
        results.emplace_back(get<1>(t1) == 2);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Tuple::assign(U&&) error\n";
        }
    }

    return errors;
}