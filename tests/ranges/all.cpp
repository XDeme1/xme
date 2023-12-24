#include <xme/ranges/all.hpp>
#include <vector>
#include <cassert>
#include <span>
#include <list>
#include <utility>

void test_forward() {
    {
        int arr[]{1, 5, 3, 5};
        std::span s{arr};
        auto a = xme::views::all(s);
        static_assert(std::same_as<decltype(a), std::span<int, 4>>);
        static_assert(std::ranges::contiguous_range<decltype(a)>);
        static_assert(std::ranges::range<decltype(a)>);
        static_assert(std::ranges::view<decltype(a)>);
        static_assert(requires { s | xme::views::all; });
        static_assert(a.size() == 4);
        for(std::size_t i = 0; i < 4; ++i) {
            assert(a[i] == s[i]);
        }
    }
}

void test_ref() {
    {
        std::vector<int> v{1, 5, 3, 5};
        auto a = xme::views::all(v);
        static_assert(std::same_as<decltype(a), xme::ranges::RefView<std::vector<int>>>);
        static_assert(std::ranges::contiguous_range<decltype(a)>);
        static_assert(std::ranges::range<decltype(a)>);
        static_assert(std::ranges::view<decltype(a)>);
        static_assert(requires {
            { a.begin() } -> std::same_as<std::ranges::iterator_t<decltype(v)>>;
            a.end();
            a.cbegin();
            a.cend();
            !!a;
            a.front();
            a.back();
            a.size();
            { a.data() } -> std::same_as<int*>;
        });
        static_assert(requires {
            std::as_const(a).begin();
            std::as_const(a).end();
            std::as_const(a).cbegin();
            std::as_const(a).cend();
            !!std::as_const(a);
            std::as_const(a).front();
            std::as_const(a).back();
            std::as_const(a).size();
            { std::as_const(a).data() } -> std::same_as<int*>;
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
        std::list l{1, 5, 3, 5};
        auto a = xme::views::all(l);
        static_assert(std::ranges::bidirectional_range<decltype(a)>);
        static_assert(std::ranges::range<decltype(a)>);
        static_assert(requires { l | xme::views::all; });
        assert(a.size() == 4);
        auto b = a.begin();
        for(auto&& r : l) {
            assert(*b == r);
            ++b;
        }
    }
}

void test_owning() {
    {
        std::vector<int> v{1, 5, 3, 1};
        auto a = xme::views::all(std::move(v));
        static_assert(std::same_as<decltype(a), xme::ranges::OwningView<std::vector<int>>>);
        static_assert(std::ranges::contiguous_range<decltype(a)>);
        static_assert(std::ranges::view<decltype(a)>);
        static_assert(requires {
            {
                std::move(v) | xme::views::all
            } -> std::same_as<xme::ranges::OwningView<std::vector<int>>>;
            { a.begin() } -> std::same_as<std::ranges::iterator_t<decltype(v)>>;
            { a.end() } -> std::same_as<std::ranges::sentinel_t<decltype(v)>>;
            { !!a } -> std::same_as<bool>;
            { a.front() } -> std::same_as<int&>;
            { a.back() } -> std::same_as<int&>;
            { a.size() } -> std::same_as<std::ranges::range_size_t<decltype(v)>>;
            { a.data() } -> std::same_as<int*>;
        });
        assert(a.size() == 4);
        for(std::size_t i = 0; i < 4; ++i)
            assert(a[i] == v[i]);
    }
}

int main() {
    test_forward();
    test_ref();
    test_owning();
}
