#include <vector>
#include <xme/ranges/iview.hpp>
#include <gtest/gtest.h>

struct Container : public xme::ranges::IView<Container> {
    constexpr auto begin() noexcept { return v.begin(); }
    constexpr auto begin() const noexcept { return v.begin(); }

    constexpr auto end() noexcept { return v.end(); }
    constexpr auto end() const noexcept { return v.end(); }

    std::vector<int> v;
};

struct IContainerTest : ::testing::Test {
    IContainerTest() {
        for(auto&& v : {5, 3, 5, 1}) {
            c.v.emplace_back(v);
        }
    }

    Container c;
};

TEST_F(IContainerTest, Range) {
    auto b = c.begin();
    EXPECT_EQ(*b++, 5);
    EXPECT_EQ(*b++, 3);
    EXPECT_EQ(*b++, 5);
    EXPECT_EQ(*b++, 1);
    EXPECT_EQ(b, c.end());
}

TEST_F(IContainerTest, Methods) {
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(c.size(), 4);
    EXPECT_EQ(c.front(), 5);
    EXPECT_EQ(c.back(), 1);
}