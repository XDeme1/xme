#include <xme/ranges/all.hpp>
#include <vector>
#include <cassert>
#include <span>
#include <list>

int main() {
    {
        std::vector<int> v{1, 5, 3, 5};
        auto a = xme::views::all(v);
        static_assert(std::same_as<decltype(a), xme::ranges::RefView<std::vector<int>>>);
        static_assert(std::ranges::contiguous_range<decltype(a)>);
        static_assert(requires {
            a.begin();
            a.end();
            a.front();
            a.back();
            a.empty();
            a.size();
            { a.data() } -> std::same_as<int*>;
        });
        assert(a.size() == 4);
        for(std::size_t i = 0; i < 4; ++i)
            assert(a[i] == v[i]);
    }

    {
        int arr[]{1, 5, 3, 5};
        auto a = xme::views::all(arr);
        static_assert(std::same_as<decltype(a), xme::ranges::RefView<int[4]>>);
        static_assert(std::ranges::contiguous_range<decltype(a)>);
        static_assert(requires { arr | xme::views::all; });
        assert(a.size() == 4);
        for(std::size_t i = 0; i < 4; ++i)
            assert(a[i] == arr[i]);
    }

    {
        int arr[]{1, 5, 3, 5};
        std::span s{arr};
        auto a = xme::views::all(s);
        static_assert(std::same_as<decltype(a), std::span<int, 4>>);
        static_assert(std::ranges::contiguous_range<decltype(a)>);
        static_assert(requires { s | xme::views::all; });
        static_assert(a.size() == 4);
        for(std::size_t i = 0; i < 4; ++i) {
            assert(a[i] == s[i]);
        }
    }

    {
        std::list l{1, 5, 3, 5};
        auto a = xme::views::all(l);
        static_assert(std::ranges::bidirectional_range<decltype(a)>);
        static_assert(requires { l | xme::views::all; });
        assert(a.size() == 4);
        auto b = a.begin();
        for(auto&& r : l) {
            assert(*b == r);
            ++b;
        }
    }
}
