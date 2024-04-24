#include <concepts>
#include <gtest/gtest.h>
#include <xme/ranges/views.hpp>
#include <vector>

template<typename T>
inline constexpr bool is_ref_view = false;

template<typename T>
inline constexpr bool is_ref_view<xme::ranges::RefView<T>> = true;

template<typename T>
inline constexpr bool is_owning_view = false;

template<typename T>
inline constexpr bool is_owning_view<xme::ranges::OwningView<T>> = true;

struct ViewsTest : public ::testing::Test {
    std::vector<int> v{5, 3, 1};
};

TEST_F(ViewsTest, all) {
    static_assert(is_ref_view<decltype(xme::views::all(v))>);
    static_assert(is_owning_view<decltype(xme::views::all(std::move(v)))>);
    static_assert(std::same_as<decltype(xme::views::all(std::span{v})), decltype(std::span{v})>);

    auto a1 = xme::views::all(v);
    EXPECT_EQ(a1.begin(), v.begin());
    auto a2 = xme::views::all(std::move(v));
    EXPECT_TRUE(v.empty());
}