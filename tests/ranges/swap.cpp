#include <cassert>
#include <xme/ranges/swap.hpp>
#include <xme/container/tuple.hpp>

struct Foo {
    int a = 0;
};

void swap(Foo& a, Foo& b) noexcept(false) {
    xme::ranges::swap(a.a, b.a);
}

int main() {
    {
        int a = 1;
        int b = 2;
        static_assert(noexcept(xme::ranges::swap(a, b)));
        xme::ranges::swap(a, b);
        assert(a == 2 && b == 1);
    }

    {
        xme::Tuple<int> a{5};
        xme::Tuple<int> b{3};
        static_assert(noexcept(xme::ranges::swap(a, b)));
        xme::ranges::swap(a, b);
        assert(get<0>(a) == 3 && get<0>(b) == 5);
    }

    {
        struct Foo {
            int a = 0;
        };
        Foo a{2};
        Foo b{7};
        static_assert(noexcept(xme::ranges::swap(a, b)));
        xme::ranges::swap(a, b);
        assert(a.a == 7 && b.a == 2);
    }

    {
        std::array<int, 2> a{5, 3};
        std::array<int, 2> b{1, 2};
        static_assert(noexcept(xme::ranges::swap(a, b)));
        xme::ranges::swap(a, b);
        assert(a[0] == 1 && a[1] == 2 && b[0] == 5 && b[1] == 3);
    }

    {
        Foo a{5};
        Foo b{3};
        static_assert(!noexcept(xme::ranges::swap(a, b)));
        xme::ranges::swap(a, b);
        assert(a.a == 3 && b.a == 5);
    }
}
