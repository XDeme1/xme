#include <gtest/gtest.h>
#include <xme/core/iterators/const_iterator.hpp>
#include <xme/core/iterators/reverse_iterator.hpp>

class IteratorsTest : public testing::Test {
public:
    std::vector<int> vec{1, 5, 3};
};

TEST_F(IteratorsTest, Traits) {
    using it_t = decltype(vec.begin());
    EXPECT_TRUE((std::same_as<xme::iter_const_reference_t<it_t>, const int&>));
}

TEST_F(IteratorsTest, ConstIterators) {
    xme::ConstIterator it{vec.begin()};
    xme::ConstIterator sent{vec.end()};
    using it_t = decltype(it);
    EXPECT_TRUE(std::contiguous_iterator<it_t>);

    EXPECT_EQ(it[0], 1);
    EXPECT_EQ(it[1], 5);
    EXPECT_EQ(it[2], 3);

    xme::ConstIterator tmp{it++};
    EXPECT_EQ(*tmp, 1);
    EXPECT_EQ(*it, 5);

    tmp = it--;
    EXPECT_EQ(*tmp, 5);
    EXPECT_EQ(*it, 1);

    tmp = ++it;
    EXPECT_EQ(*it, *tmp);

    tmp = --it;
    EXPECT_EQ(*it, *tmp);

    EXPECT_EQ(*(it + 2), 3);
    EXPECT_EQ(*(2 + it), 3);
    EXPECT_EQ(*(sent - 2), 5);

    EXPECT_EQ(sent - it, 3);
    EXPECT_EQ(it - sent, -3);

    it += 2;
    EXPECT_EQ(*it, 3);

    it -= 2;
    EXPECT_EQ(*it, 1);

    EXPECT_TRUE(it == tmp);
    EXPECT_FALSE(it != tmp);
}

TEST_F(IteratorsTest, ReverseIterators) {
    xme::ReverseIterator it{vec.end()};
    xme::ReverseIterator sent{vec.begin()};
    using it_t = decltype(it);
    EXPECT_FALSE(std::contiguous_iterator<it_t>);
    EXPECT_TRUE(std::random_access_iterator<it_t>);

    EXPECT_EQ(it[0], 3);
    EXPECT_EQ(it[1], 5);
    EXPECT_EQ(it[2], 1);

    xme::ReverseIterator tmp{it++};
    EXPECT_EQ(*tmp, 3);
    EXPECT_EQ(*it, 5);

    tmp = it--;
    EXPECT_EQ(*tmp, 5);
    EXPECT_EQ(*it, 3);

    tmp = ++it;
    EXPECT_EQ(*it, *tmp);

    tmp = --it;
    EXPECT_EQ(*it, *tmp);

    EXPECT_EQ(*(it + 2), 1);
    EXPECT_EQ(*(2 + it), 1);
    EXPECT_EQ(*(sent - 2), 5);

    EXPECT_EQ(sent - it, 3);
    EXPECT_EQ(it - sent, -3);

    it += 2;
    EXPECT_EQ(*it, 1);

    it -= 2;
    EXPECT_EQ(*it, 3);

    EXPECT_TRUE(it == tmp);
    EXPECT_FALSE(it != tmp);
}