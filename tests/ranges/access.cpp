#include <concepts>
#include <iterator>
#include <vector>
#include <gtest/gtest.h>
#include "xme/core/iterators/const_iterator.hpp"
#include "xme/core/iterators/reverse_iterator.hpp"
#include <xme/ranges/access.hpp>

struct Container1 {
    int a[3]{7, 3, 1};
};
struct Container2 {
    int a[3]{8, 56, 1};
};

constexpr auto begin(Container1& c) {
    return c.a;
}
constexpr auto end(Container1& c) {
    return c.a + 3;
}

constexpr auto size(Container2& c) -> std::size_t {
    return (c.a + 3) - c.a;
}

class AccessTest : public ::testing::Test {
public:
#ifdef __SIZEOF_INT128__
    __int128
#else
    int
#endif
      a[3]{1, 5, 3};
    std::vector<int> v{5, 3, 8};
    Container1 c1;
    Container2 c2;
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
    {
        auto b = xme::ranges::begin(c1);
        EXPECT_EQ(*(b++), 7);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 1);
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
    {
        auto e = xme::ranges::end(c1);
        EXPECT_EQ(*(--e), 1);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 7);
    }
}

TEST_F(AccessTest, cbegin) {
    {
        auto b = xme::ranges::cbegin(v);
        static_assert(std::same_as<decltype(v)::const_iterator, decltype(b)>);
        EXPECT_EQ(*(b++), 5);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 8);
    }
    {
        auto b = xme::ranges::cbegin(a);
        static_assert(std::is_const_v<std::remove_pointer_t<decltype(b)>>);
        EXPECT_EQ(*(b++), 1);
        EXPECT_EQ(*(b++), 5);
        EXPECT_EQ(*(b++), 3);
    }
    {
        auto b = xme::ranges::cbegin(c1);
        static_assert(std::same_as<xme::ConstIterator<int*>, decltype(b)>);
        EXPECT_EQ(*(b++), 7);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 1);
    }
}

TEST_F(AccessTest, cend) {
    {
        auto e = xme::ranges::cend(v);
        static_assert(std::same_as<decltype(v)::const_iterator, decltype(e)>);
        EXPECT_EQ(*(--e), 8);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 5);
    }
    {
        auto e = xme::ranges::cend(a);
        static_assert(std::is_const_v<std::remove_pointer_t<decltype(e)>>);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 5);
        EXPECT_EQ(*(--e), 1);
    }
    {
        auto e = xme::ranges::cend(c1);
        static_assert(std::same_as<xme::ConstIterator<int*>, decltype(e)>);
        EXPECT_EQ(*(--e), 1);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 7);
    }
}

TEST_F(AccessTest, rbegin) {
    {
        auto b = xme::ranges::rbegin(v);
        static_assert(std::same_as<std::reverse_iterator<decltype(v)::iterator>, decltype(b)>);
        EXPECT_EQ(*(b++), 8);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 5);
    }
    {
        auto b = xme::ranges::rbegin(a);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 5);
        EXPECT_EQ(*(b++), 1);
    }
    {
        auto b = xme::ranges::rbegin(c1);
        static_assert(std::same_as<xme::ReverseIterator<int*>, decltype(b)>);
        EXPECT_EQ(*(b++), 1);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 7);
    }
}

TEST_F(AccessTest, rend) {
    {
        auto e = xme::ranges::rend(v);
        static_assert(std::same_as<std::reverse_iterator<decltype(v)::iterator>, decltype(e)>);
        EXPECT_EQ(*(--e), 5);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 8);
    }
    {
        auto e = xme::ranges::rend(a);
        EXPECT_EQ(*(--e), 1);
        EXPECT_EQ(*(--e), 5);
        EXPECT_EQ(*(--e), 3);
    }
    {
        auto e = xme::ranges::rend(c1);
        static_assert(std::same_as<xme::ReverseIterator<int*>, decltype(e)>);
        EXPECT_EQ(*(--e), 7);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 1);
    }
}

TEST_F(AccessTest, crbegin) {
    {
        auto b = xme::ranges::crbegin(v);
        static_assert(
          std::same_as<std::reverse_iterator<decltype(v)::const_iterator>, decltype(b)>);
        EXPECT_EQ(*(b++), 8);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 5);
    }
    {
        auto b = xme::ranges::crbegin(a);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 5);
        EXPECT_EQ(*(b++), 1);
    }
    {
        auto b = xme::ranges::crbegin(c1);
        static_assert(std::same_as<xme::ConstIterator<xme::ReverseIterator<int*>>, decltype(b)>);
        EXPECT_EQ(*(b++), 1);
        EXPECT_EQ(*(b++), 3);
        EXPECT_EQ(*(b++), 7);
    }
}

TEST_F(AccessTest, crend) {
    {
        auto e = xme::ranges::crend(v);
        static_assert(
          std::same_as<std::reverse_iterator<decltype(v)::const_iterator>, decltype(e)>);
        EXPECT_EQ(*(--e), 5);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 8);
    }
    {
        auto e = xme::ranges::crend(a);
        EXPECT_EQ(*(--e), 1);
        EXPECT_EQ(*(--e), 5);
        EXPECT_EQ(*(--e), 3);
    }
    {
        auto e = xme::ranges::crend(c1);
        static_assert(std::same_as<xme::ConstIterator<xme::ReverseIterator<int*>>, decltype(e)>);
        EXPECT_EQ(*(--e), 7);
        EXPECT_EQ(*(--e), 3);
        EXPECT_EQ(*(--e), 1);
    }
}

TEST_F(AccessTest, size) {
    static_assert(std::is_unsigned_v<decltype(xme::ranges::size(v))>);
    static_assert(std::is_unsigned_v<decltype(xme::ranges::size(a))>);
    static_assert(std::is_unsigned_v<decltype(xme::ranges::size(c1))>);
    static_assert(std::is_unsigned_v<decltype(xme::ranges::size(c2))>);
    EXPECT_EQ(xme::ranges::size(v), 3);
    EXPECT_EQ(xme::ranges::size(a), 3);
    EXPECT_EQ(xme::ranges::size(c1), 3);
    EXPECT_EQ(xme::ranges::size(c2), 3);
}

TEST_F(AccessTest, ssize) {
    static_assert(std::is_signed_v<decltype(xme::ranges::ssize(v))>);
    static_assert(std::is_signed_v<decltype(xme::ranges::ssize(a))>);
    static_assert(std::is_signed_v<decltype(xme::ranges::ssize(c1))>);
    static_assert(std::is_signed_v<decltype(xme::ranges::ssize(c2))>);
    EXPECT_EQ(xme::ranges::ssize(v), 3);
    EXPECT_EQ(xme::ranges::ssize(a), 3);
    EXPECT_EQ(xme::ranges::ssize(c1), 3);
    EXPECT_EQ(xme::ranges::ssize(c2), 3);
}

TEST_F(AccessTest, empty) {
    EXPECT_EQ(xme::ranges::empty(v), false);
    EXPECT_EQ(xme::ranges::empty(a), false);
    EXPECT_EQ(xme::ranges::empty(c1), false);
    EXPECT_EQ(xme::ranges::empty(c2), false);
    EXPECT_EQ(xme::ranges::empty(std::vector<int>{}), true);
}

TEST_F(AccessTest, data) {
    EXPECT_EQ(xme::ranges::data(v), std::to_address(xme::ranges::begin(v)));
    EXPECT_EQ(xme::ranges::data(a), std::to_address(xme::ranges::begin(a)));
    EXPECT_EQ(xme::ranges::data(c1), std::to_address(xme::ranges::begin(c1)));
}
TEST_F(AccessTest, cdata) {
    static_assert(std::is_const_v<std::remove_pointer_t<decltype(xme::ranges::cdata(v))>>);
    static_assert(std::is_const_v<std::remove_pointer_t<decltype(xme::ranges::cdata(a))>>);
    static_assert(std::is_const_v<std::remove_pointer_t<decltype(xme::ranges::cdata(c1))>>);
    EXPECT_EQ(xme::ranges::cdata(v), std::to_address(xme::ranges::cbegin(v)));
    EXPECT_EQ(xme::ranges::cdata(a), std::to_address(xme::ranges::cbegin(a)));
    EXPECT_EQ(xme::ranges::cdata(c1), std::to_address(xme::ranges::cbegin(c1)));
}