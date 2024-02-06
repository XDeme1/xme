#include <gtest/gtest.h>
#include <xme/math/math.hpp>
#include <xme/math/glsl_mapping.hpp>

namespace {
using namespace xme::math;

class QuaternionTests : public testing::Test {};

TEST_F(QuaternionTests, Quaternion) {
    Quaternion<float> quat{1, 5, 3, 4};

    EXPECT_EQ(quat.w, 1);
    EXPECT_EQ(quat.x, 5);
    EXPECT_EQ(quat.y, 3);
    EXPECT_EQ(quat.z, 4);

    {
        Quaternion<float> tmp{3, 1, 0, 3};
        Quaternion<float> expected{4, 6, 3, 7};
        EXPECT_EQ(quat + tmp, expected);

        expected = {-2, 4, 3, 1};
        EXPECT_EQ(quat - tmp, expected);

        expected = {-14, 25, -2, 12};
        EXPECT_EQ(quat * tmp, expected);
    }
}
}  // namespace