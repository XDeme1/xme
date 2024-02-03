#include <gtest/gtest.h>
#include <xme/core/concepts/concepts.hpp>

class ConceptsTest : public testing::Test {
public:
};

TEST_F(ConceptsTest, Arithmetic) {
    EXPECT_TRUE(xme::CSignedIntegral<std::int32_t>);
    EXPECT_FALSE(xme::CSignedIntegral<std::uint32_t>);

    EXPECT_TRUE(xme::CFloatingPoint<long double>);
    EXPECT_FALSE(xme::CFloatingPoint<long int>);

    EXPECT_TRUE(xme::CArithmetic<bool>);
    EXPECT_TRUE(xme::CArithmetic<std::int8_t>);
    EXPECT_TRUE(xme::CArithmetic<std::uint8_t>);
}

TEST_F(ConceptsTest, DifferentFrom) {
    EXPECT_FALSE((xme::CDifferentFrom<int, int>));
    EXPECT_TRUE((xme::CDifferentFrom<int, const int>));
}