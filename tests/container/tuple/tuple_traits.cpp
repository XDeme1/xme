#include "../common.hpp"
#include <xme/container/tuple.hpp>

struct Empty {};

int main() {
    static_assert(std::is_aggregate_v<xme::Tuple<>>);
    static_assert(std::is_aggregate_v<xme::Tuple<std::string, int>>);

    static_assert(std::is_empty_v<xme::Tuple<>>);
    static_assert(std::is_empty_v<xme::Tuple<Empty, Empty>>);

    static_assert(std::is_trivial_v<xme::Tuple<>>);
    static_assert(std::is_trivial_v<xme::Tuple<int, int&, int&&>>);
    static_assert(!std::is_trivial_v<xme::Tuple<std::string>>);

    static_assert(std::is_trivially_destructible_v<xme::Tuple<int, int&, int&&>>);
    static_assert(!std::is_trivially_destructible_v<xme::Tuple<std::string, int>>);

    static_assert(std::is_trivially_move_constructible_v<xme::Tuple<int, int&, int&&>>);
    static_assert(!std::is_trivially_move_constructible_v<xme::Tuple<std::string, int>>);

    static_assert(
        std::is_trivially_copy_constructible_v<xme::Tuple<int, int&, const int&>>);
    static_assert(!std::is_trivially_copy_constructible_v<xme::Tuple<std::string, int>>);

    static_assert(std::is_trivially_default_constructible_v<xme::Tuple<int>>);
    static_assert(!std::is_trivially_default_constructible_v<xme::Tuple<std::string>>);

    static_assert(std::is_trivially_assignable_v<xme::Tuple<int>, xme::Tuple<int>>);
    static_assert(!std::is_trivially_assignable_v<xme::Tuple<int>, xme::Tuple<float>>);
    static_assert(!std::is_trivially_assignable_v<xme::Tuple<std::string>,
                                                  xme::Tuple<std::string>>);

    static_assert(xme::CTupleLike<xme::Tuple<>>);
    static_assert(xme::CTupleLike<xme::Tuple<int, int, int&>>);
    static_assert(xme::CTupleLike<const xme::Tuple<int, int, int&>>);

    static_assert(xme::CPairLike<xme::Tuple<int, int>>);
    static_assert(!xme::CPairLike<xme::Tuple<>>);
    return 0;
}