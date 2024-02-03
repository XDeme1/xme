#include <gtest/gtest.h>
#include <concepts>
#include <xme/core/utility/forward_like.hpp>

class UtilityTest : public testing::Test {
public:
};

TEST_F(UtilityTest, ForwardLike) {
    int a = 0;
    class ForwardClass;
    EXPECT_TRUE((requires {
        { xme::forward_like<const ForwardClass&&>(a) } -> std::same_as<const int&&>;
    }));
}