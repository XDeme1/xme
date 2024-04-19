#include <cstddef>
#include <gtest/gtest.h>
#include <xme/container/array_view.hpp>
#include <xme/container/array.hpp>
#include <array>
#include <bit>

static_assert(sizeof(xme::ArrayView<int>) == sizeof(int*) + sizeof(std::size_t));
static_assert(sizeof(xme::ArrayView<int, 2>) == sizeof(int*));
static_assert(std::ranges::view<xme::ArrayView<int>>);
static_assert(std::ranges::borrowed_range<xme::ArrayView<int>>);

struct ArrayViewTest : ::testing::Test {};

TEST_F(ArrayViewTest, deduction) {
    int a1[2]{};
    const int a2[2]{};
    std::array<int, 2> a3{};
    std::array<const int, 2> a4{1, 2};
    const std::array<int, 2> a5{1, 2};

    xme::ArrayView v1{a1, 2};
    xme::ArrayView v2{a2, 2};
    xme::ArrayView v3{a1};
    xme::ArrayView v4{a2};
    xme::ArrayView v5{a3};
    xme::ArrayView v6{a4};
    xme::ArrayView v7{a5};

    static_assert(std::is_same_v<decltype(v1), xme::ArrayView<int>>);
    static_assert(std::is_same_v<decltype(v2), xme::ArrayView<const int>>);
    static_assert(std::is_same_v<decltype(v3), xme::ArrayView<int, 2>>);
    static_assert(std::is_same_v<decltype(v4), xme::ArrayView<const int, 2>>);  //
    static_assert(std::is_same_v<decltype(v5), xme::ArrayView<int, 2>>);
    static_assert(std::is_same_v<decltype(v6), xme::ArrayView<const int, 2>>);
    static_assert(std::is_same_v<decltype(v7), xme::ArrayView<const int, 2>>);
}

TEST_F(ArrayViewTest, access) {
    {
        int arr[2]{-6, 3};
        xme::ArrayView<const int, 2> view{arr};
        bool error = view[0] != -6 || view[1] != 3;
        EXPECT_EQ(view[0], -6);
        EXPECT_EQ(view[1], 3);
    }
    {
        const int arr[2]{-3, 1};
        xme::ArrayView<const int> view{arr, 2};
        static_assert(std::is_same_v<decltype(view.data()), const int*>);
        EXPECT_EQ(*view.data(), -3);
        EXPECT_EQ(*(view.data() + 1), 1);
        EXPECT_EQ(view.size(), 2);
    }
    {
        std::array<int, 2> arr{7, 1};
        xme::ArrayView<int, 2> view{arr};
        auto begin = view.begin();
        EXPECT_EQ(*begin++, 7);
        EXPECT_EQ(*begin++, 1);
        EXPECT_EQ(begin, view.end());
        EXPECT_EQ(view.size(), 2);
    }
    {
        const std::array<int, 2> arr{3, 2};
        xme::ArrayView<const int> view{arr};
        auto rbegin = view.rbegin();
        EXPECT_EQ(*rbegin++, 2);
        EXPECT_EQ(*rbegin++, 3);
        EXPECT_EQ(rbegin, view.rend());
    }
    {
        std::array<const int, 2> arr{5, 4};
        xme::ArrayView<const int, 2> view{arr};
        EXPECT_EQ(view.front(), 5);
        EXPECT_EQ(view.back(), 4);
    }
}

TEST_F(ArrayViewTest, subviews) {
    {
        std::array<int, 2> arr{3, -1};
        xme::ArrayView<int, 2> v{arr};
        const xme::ArrayView<int, 2> v2{arr};
        xme::ArrayView<int, 2> view1{v};
        void(xme::ArrayView<int, 2>{v2});
        auto sub  = view1.subview(1, 1);
        auto sub2 = view1.subview<1, 1>();
        EXPECT_EQ(view1.begin() + 1, sub.begin());
        EXPECT_EQ(view1.end(), sub.end());
        EXPECT_EQ(view1.begin() + 1, sub2.begin());
        EXPECT_EQ(view1.end(), sub2.end());
    }
    {
        std::array<int, 3> arr{1, 8, 3};
        xme::ArrayView<int, 3> view{arr};
        auto f1 = view.first(2);
        auto f2 = view.first<2>();
        EXPECT_EQ(f1.begin(), view.begin());
        EXPECT_EQ(f1.end(), view.begin() + 2);
        EXPECT_EQ(f2.begin(), view.begin());
        EXPECT_EQ(f2.end(), view.begin() + 2);
    }
    {
        const std::array<const int, 3> arr{1, 8, 3};
        const xme::ArrayView<const int, 3> view{arr};
        auto f1 = view.last(2);
        auto f2 = view.last<2>();
        EXPECT_EQ(f1.begin(), view.begin() + 1);
        EXPECT_EQ(f1.end(), view.end());
        EXPECT_EQ(f2.begin(), view.begin() + 1);
        EXPECT_EQ(f2.end(), view.end());
    }
}

TEST_F(ArrayViewTest, Bytes) {
    int a1[1]{0x12'43'12'05};
    xme::ArrayView v1{a1};
    xme::ArrayView v2{xme::as_bytes(v1)};

    bool error = false;
    if constexpr(std::endian::native == std::endian::little) {
        EXPECT_EQ(*v2.data(), std::byte(0x5));
        EXPECT_EQ(*(v2.data() + 1), std::byte(0x12));
        EXPECT_EQ(*(v2.data() + 2), std::byte(0x43));
        EXPECT_EQ(*(v2.data() + 3), std::byte(0x12));
    }
    else {
        EXPECT_EQ(*v2.data(), std::byte(0x12));
        EXPECT_EQ(*(v2.data() + 1), std::byte(0x43));
        EXPECT_EQ(*(v2.data() + 2), std::byte(0x12));
        EXPECT_EQ(*(v2.data() + 3), std::byte(0x5));
    }
}