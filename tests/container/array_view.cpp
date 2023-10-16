#include <xme/container/array_view.hpp>
#include <xme/container/array.hpp>
#include <iostream>
#include <array>

static_assert(sizeof(xme::ArrayView<int>) == sizeof(int*) + sizeof(std::size_t));
static_assert(sizeof(xme::ArrayView<int, 2>) == sizeof(int*));
static_assert(std::ranges::view<xme::ArrayView<int>>);
static_assert(std::ranges::borrowed_range<xme::ArrayView<int>>);

void testDeductionGuides() {
    {
        int a1[2]{};
        const int a2[2]{};
        xme::ArrayView v1{a1, 2};
        xme::ArrayView v2{a2, 2};
        static_assert(std::is_same_v<decltype(v1), xme::ArrayView<int>>);
        static_assert(std::is_same_v<decltype(v2), xme::ArrayView<const int>>);
    }
    {
        int arr1[2]{};
        const int arr2[2]{};
        xme::ArrayView v1{arr1};
        xme::ArrayView v2{arr2};
        static_assert(std::is_same_v<decltype(v1), xme::ArrayView<int, 2>>);
        static_assert(std::is_same_v<decltype(v2), xme::ArrayView<const int, 2>>);
    }
    {
        std::array<int, 2> a1{};
        std::array<const int, 2> a3{1, 2};
        const std::array<int, 2> a2{1, 2};
        xme::ArrayView v1{a1};
        xme::ArrayView v2{a2};
        xme::ArrayView v3{a3};
        static_assert(std::is_same_v<decltype(v1), xme::ArrayView<int, 2>>);
        static_assert(std::is_same_v<decltype(v2), xme::ArrayView<const int, 2>>);
        static_assert(std::is_same_v<decltype(v3), xme::ArrayView<const int, 2>>);
    }
    {
        xme::Array<int> a1{1, 5, 3};
        const xme::Array<int> a2{1, 5, 3};
        xme::ArrayView v1{a1};
        xme::ArrayView v2{a2};

        static_assert(std::is_same_v<decltype(v1), xme::ArrayView<int>>);
        static_assert(std::is_same_v<decltype(v2), xme::ArrayView<const int>>);
    }
}

int testAccess() {
    int errors = 0;
    {
        int arr[2]{-6, 3};
        xme::ArrayView<const int, 2> view{arr};
        bool error = view[0] != -6 || view[1] != 3;
        if(error) {
            std::cerr << "xme::ArrayView operator[] error\n";
            ++errors;
        }
    }
    {
        const int arr[2]{-3, 1};
        xme::ArrayView<const int, 2> view{arr};
        static_assert(std::is_same_v<decltype(view.data()), const int*>);
        bool error = *view.data() != -3 || *(view.data()+1) != 1;
        if(error) {
            std::cerr << "xme::ArrayView::data error\n";
            ++errors;
        }
    }
    {
        std::array<int, 2> arr{7, 1};
        xme::ArrayView<int, 2> view{arr};
        auto begin = view.begin();
        bool error = *(begin++) != 7;
        error |= *(begin++) != 1;
        error |= begin != view.end();
        if(error) {
            std::cerr << "xme::ArrayView::begin error\n";
            ++errors;
        }
    }
    {
        const std::array<int, 2> arr{3, 2};
        xme::ArrayView<const int, 2> view{arr};
        auto rbegin = view.rbegin();
        bool error = *(rbegin++) != 2;
        error |= *(rbegin++) != 3;
        error |= rbegin != view.rend();
        if(error) {
            std::cerr << "xme::ArrayView::rbegin error\n";
            ++errors;
        }
    }
    {
        std::array<const int, 2> arr{5, 4};
        xme::ArrayView<const int, 2> view{arr};
        bool error = view.front() != 5 || view.back() != 4;
        if(error) {
            std::cerr << "xme::ArrayView::front/back error\n";
            ++errors;
        }
    }
    return errors;
}

int testSubviews() {
    int errors = 0;
    {
        std::array<int, 2> arr{3, -1};
        xme::ArrayView<int, 2> v{arr};
        const xme::ArrayView<int, 2> v2{arr};
        xme::ArrayView<int, 2> view1{v};
        void(xme::ArrayView<int, 2>{v2});
        auto sub = view1.subview(1, 1);
        auto sub2 = view1.subview<1, 1>();
        bool error = view1.begin()+1 != sub.begin() || view1.end() != sub.end();
        error |= view1.begin()+1 != sub2.begin() || view1.end() != sub2.end();
        if(error) {
            std::cerr << "xme::ArrayView::subview error\n";
            ++errors;
        }
    }
    {
        std::array<int, 3> arr{1, 8, 3};
        xme::ArrayView<int, 3> view{arr};
        auto f1 = view.first(2);
        auto f2 = view.first<2>();
        bool error = f1.begin() != view.begin() || f1.end() != view.begin()+2;
        error |= f2.begin() != view.begin() || f2.end() != view.begin()+2;
        if(error) {
            std::cerr << "xme::ArrayView::first error\n";
            ++errors;
        }
    }
    {
        const std::array<const int, 3> arr{1, 8, 3};
        const  xme::ArrayView<const int, 3> view{arr};
        auto f1 = view.last(2);
        auto f2 = view.last<2>();
        bool error = f1.begin() != view.begin()+1 || f1.end() != view.end();
        error |= f2.begin() != view.begin()+1 || f2.end() != view.end();
        if(error) {
            std::cerr << "xme::ArrayView::last error\n";
            ++errors;
        }
    }
    return errors;
}

int testAsBytes() {
    int errors = 0;
    {
        int a1[1]{0x12'43'12'05};
        xme::ArrayView v1{a1};
        xme::ArrayView v2{xme::asBytes(v1)};
        
        bool error = false;
        if constexpr(std::endian::native == std::endian::little) {
            error |= *v2.data() != std::byte(0x5) || *(v2.data()+1) != std::byte(0x12);
            error |= *(v2.data()+2) != std::byte(0x43) || *(v2.data()+3) != std::byte(0x12);
        }
        else {
            error |= *(v2.data()) != std::byte(0x12) || *(v2.data()+1) != std::byte(0x43);
            error |= *(v2.data()+2) != std::byte(0x12) || *(v2.data()+3) != std::byte(0x05);
        }

        if(error) {
            std::cerr << "xme::ArrayView asBytes error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    testDeductionGuides();
    errors += testAccess();
    errors += testSubviews();
    errors += testAsBytes();
    return errors;
}  