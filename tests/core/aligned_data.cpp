#include <gtest/gtest.h>
#include <type_traits>
#include <xme/container/aligned_data.hpp>

struct AlignDataTest : ::testing::Test {};

TEST_F(AlignDataTest, AlignData) {
    xme::AlignedData<int> data{};
    static_assert(std::is_trivially_copyable_v<decltype(data)>);
    EXPECT_TRUE((std::is_same_v<decltype(data.data()), int*>));
}