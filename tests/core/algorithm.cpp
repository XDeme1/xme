#include <gtest/gtest.h>
#include <xme/core/algorithm/find.hpp>

struct AlgorithmTest : ::testing::Test {};

TEST_F(AlgorithmTest, find) {
    const std::string lorem =
      "Lorem ipsum dolor sit amet consectetur adipisicing elit. Repellendus cupiditate ullam autem "
      "voluptate a sint dignissimos harum maiores sapiente incidunt? Atque, totam nisi voluptate "
      "eum "
      "officiis rerum sit eaque hic."
      "Lorem ipsum dolor sit amet consectetur adipisicing elit. Repellendus cupiditate ullam autem "
      "voluptate a sint dignissimos harum maiores sapiente incidunt? Atque, totam nisi voluptate "
      "eum "
      "officiis rerum sit eaque hic."
      "Lorem ipsum dolor sit amet consectetur adipisicing elit. Repellendus cupiditate ullam autem "
      "voluptate a sint dignissimos harum maiores sapiente incidunt? Atque, totam nisi voluptate "
      "eum "
      "officiis rerum sit eaque hic."
      "Lorem ipsum dolor sit amet consectetur adipisicing elit. Repellendus cupiditate ullam autem "
      "voluptate a sint dignissimos harum maiores sapiente incidunt? Atque, totam nisi voluptate "
      "eum "
      "officiis rerum5 sit eaque hic.0";

    const std::vector<std::int16_t> v16{
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,
    };
    const std::vector<std::int32_t> v32{
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,
    };
    const std::vector<std::int64_t> v64{
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,
    };

    EXPECT_EQ(ranges::find(lorem, '5'), xme::find(lorem, '5'));
    EXPECT_EQ(ranges::find(lorem, '\\'), xme::find(lorem, '\\'));
    EXPECT_EQ(ranges::find(lorem, '0'), xme::find(lorem, '0'));

    EXPECT_EQ(ranges::find(v16, 4), xme::find(v16, 4));
    EXPECT_EQ(ranges::find(v16, 7), xme::find(v16, 7));
    EXPECT_EQ(ranges::find(v16, 9), xme::find(v16, 9));
    EXPECT_EQ(ranges::find(v16, 10), xme::find(v16, 10));

    EXPECT_EQ(ranges::find(v32, 4), xme::find(v32, 4));
    EXPECT_EQ(ranges::find(v32, 7), xme::find(v32, 7));
    EXPECT_EQ(ranges::find(v32, 9), xme::find(v32, 9));
    EXPECT_EQ(ranges::find(v32, 10), xme::find(v32, 10));

    EXPECT_EQ(ranges::find(v64, 4), xme::find(v64, 4));
    EXPECT_EQ(ranges::find(v64, 7), xme::find(v64, 7));
    EXPECT_EQ(ranges::find(v64, 9), xme::find(v64, 9));
    EXPECT_EQ(ranges::find(v64, 10), xme::find(v64, 10));
}

TEST_F(AlgorithmTest, fill) {
    std::vector<std::int64_t> v16(2);
}