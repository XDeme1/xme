#include <gtest/gtest.h>
#include <vector>
#include <xme/ranges/access.hpp>

class AccessTest : public ::testing::Test {
public:
    int a[3]{1, 5, 3};
    std::vector<int> v{5, 3, 8};
};

TEST_F(AccessTest, begin) {
    {
        auto b = xme::ranges::begin(v);
        EXPECT_EQ(*(b++), 5);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 8);
    }
    {
        auto b = xme::ranges::begin(a);
        EXPECT_EQ(*(b++), 1);
        EXPECT_EQ(*(b++), 5);
        EXPECT_EQ(*(b++), 3);
    }
}

TEST_F(AccessTest, end) {
    {
        auto e = xme::ranges::end(v);
        EXPECT_EQ(*(--e), 8);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 5);
    }
    {
        auto e = xme::ranges::end(a);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 5);
        EXPECT_EQ(*(--e), 1);
    }
}

TEST_F(AccessTest, size) {
    EXPECT_EQ(xme::ranges::size(v), 3);
    EXPECT_EQ(xme::ranges::size(a), 3);
}