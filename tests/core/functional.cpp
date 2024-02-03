#include <gtest/gtest.h>
#include <xme/core/functional/scoped_delegate.hpp>
#include <xme/core/functional/bind.hpp>
#include <xme/core/functional/delegate.hpp>

class FunctionalTest : public testing::Test {
public:
};

TEST_F(FunctionalTest, Bind) {
    {
        constexpr auto fn = [](int a) {};
        auto front        = xme::bind_front(fn, 1);
        EXPECT_TRUE(std::is_invocable_v<decltype(front)>);
        EXPECT_TRUE(std::is_invocable_v<decltype(std::as_const(front))>);
        EXPECT_TRUE(std::is_invocable_v<decltype(std::move(front))>);
        EXPECT_TRUE(std::is_invocable_v<decltype(std::move(std::as_const(front)))>);

        auto back = xme::bind_back(fn, 1);
        EXPECT_TRUE(std::is_invocable_v<decltype(back)>);
        EXPECT_TRUE(std::is_invocable_v<decltype(std::as_const(back))>);
        EXPECT_TRUE(std::is_invocable_v<decltype(std::move(back))>);
        EXPECT_TRUE(std::is_invocable_v<decltype(std::move(std::as_const(back)))>);
    }
    {
        constexpr auto fn = [](int, const std::string&) {};
        auto front        = xme::bind_front(fn, 1);
        auto back         = xme::bind_back(fn, "");
        EXPECT_TRUE((std::is_invocable_v<decltype(front), const char*>));
        EXPECT_TRUE((std::is_invocable_v<decltype(back), int>));
    }
}

TEST_F(FunctionalTest, Delegate) {
    xme::Delegate fn{[] {}};
    EXPECT_TRUE(std::is_invocable_v<decltype(fn)>);
    EXPECT_TRUE(std::is_invocable_v<decltype(std::as_const(fn))>);
    EXPECT_TRUE(std::is_invocable_v<decltype(std::move(fn))>);
    EXPECT_TRUE(std::is_invocable_v<decltype(std::move(std::as_const(fn)))>);

    fn = [this]() {};
}

TEST_F(FunctionalTest, ScopedDelegate) {
    int a = 0;
    {
        xme::ScopedDelegate exit{[&]() { ++a; }};
        EXPECT_EQ(a, 0);
    }
    EXPECT_EQ(a, 1);
}