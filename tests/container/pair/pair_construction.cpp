#include "../common.hpp"
#include <xme/container/pair.hpp>

int main() {
    int errors = 0;
    int a = 1;
    int& b = a;
    const int& c = 1;
    int&& d = 6;
    xme::Pair p1{1, 5};
    xme::Pair p2{a, b};
    xme::Pair p3{c, d};
    xme::Pair p4{std::ref(b), std::ref(c)};
    xme::Pair p5{std::ref(d), 0};

    static_assert(std::is_aggregate_v<decltype(p1)>);
    static_assert(std::is_same_v<decltype(p1), xme::Pair<int, int>>);
    static_assert(std::is_same_v<decltype(p2), xme::Pair<int, int>>);
    static_assert(std::is_same_v<decltype(p3), xme::Pair<int, int>>);
    static_assert(std::is_same_v<decltype(p4), xme::Pair<int&, const int&>>);
    static_assert(std::is_same_v<decltype(p5), xme::Pair<int&, int>>);

    static_assert(std::is_trivial_v<decltype(p1)>);
    static_assert(std::is_trivial_v<decltype(p4)>);
    static_assert(std::is_trivial_v<decltype(p5)>);
    static_assert(!std::is_trivial_v<xme::Pair<std::string, int>>);

    static_assert(std::is_trivially_destructible_v<decltype(p1)>);
    static_assert(std::is_trivially_destructible_v<decltype(p4)>);
    static_assert(std::is_trivially_destructible_v<decltype(p5)>);
    static_assert(!std::is_trivially_destructible_v<xme::Pair<std::string, int>>);

    static_assert(std::is_trivially_move_constructible_v<decltype(p1)>);
    static_assert(std::is_trivially_move_constructible_v<decltype(p4)>);
    static_assert(std::is_trivially_move_constructible_v<decltype(p5)>);
    static_assert(!std::is_trivially_move_constructible_v<xme::Pair<std::string, int>>);

    static_assert(std::is_trivially_copy_constructible_v<decltype(p1)>);
    static_assert(std::is_trivially_copy_constructible_v<decltype(p4)>);
    static_assert(std::is_trivially_copy_constructible_v<decltype(p5)>);
    static_assert(!std::is_trivially_copy_constructible_v<xme::Pair<std::string, int>>);

    static_assert(std::is_trivially_default_constructible_v<decltype(p1)>);
    static_assert(
        !std::is_trivially_default_constructible_v<decltype(p4)>); // Because of &
    static_assert(
        !std::is_trivially_default_constructible_v<decltype(p5)>); // Because of &
    static_assert(
        !std::is_trivially_default_constructible_v<xme::Pair<std::string, int>>);

    xme::Pair<std::string, int> p6{"Hello World", 3};
    const xme::Pair<std::string, int> p7{"Hello World", 2};
    static_assert(std::is_same_v<std::string&&, decltype(get<0>(std::move(p6)))>);
    static_assert(std::is_same_v<std::string&, decltype(get<0>(p6))>);
    static_assert(std::is_same_v<const std::string&, decltype(get<0>(p7))>);

    if (auto [tmp1, tmp2] = p1; tmp1 != 1 || tmp2 != 5)
        ++errors;

    if (auto [tmp1, tmp2] = p2; tmp1 != 1 || tmp2 != 1)
        ++errors;

    if (auto [tmp1, tmp2] = p3; tmp1 != 1 || tmp2 != 6)
        ++errors;

    if (auto [tmp1, tmp2] = p4; tmp1 != 1 || tmp2 != 1)
        ++errors;

    if (auto [tmp1, tmp2] = p5; tmp1 != 6)
        ++errors;

    if (errors)
        std::cerr << "Pair construction error\n";

    return errors;
}