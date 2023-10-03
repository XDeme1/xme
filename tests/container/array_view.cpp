#include <xme/container/array_view.hpp>
#include <span>
#include <iostream>

static_assert(sizeof(xme::ArrayView<int>) == sizeof(int*) + sizeof(std::size_t));
static_assert(sizeof(xme::ArrayView<int, 2>) == sizeof(int*));

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

int main() {
    int errors = 0;
    errors += testAccess();
    return errors;
}  