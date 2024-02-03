#include <gtest/gtest.h>
#include <xme/core/type_traits/is_scoped_enum.hpp>

class TypeTraitsTest : public testing::Test {
public:
    enum E1 {};
    enum class E2 {};
};

TEST_F(TypeTraitsTest, IsScopedEnum) {
    EXPECT_TRUE(!xme::is_scoped_enum<int>);
    EXPECT_TRUE(!xme::is_scoped_enum<E1>);
    EXPECT_TRUE(xme::is_scoped_enum<E2>);
}