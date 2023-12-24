#include <xme/core/concepts/concepts.hpp>

int main() {
    {
        static_assert(xme::same_as<int, int>);
        static_assert(!xme::same_as<int, const int>);
        static_assert(!xme::same_as<int, int&>);
    }

    {
        class B {};
        class D1 : public B {};
        class D2 : B {};
        static_assert(xme::derived_from<B, B>);
        static_assert(xme::derived_from<D1, B>);
        static_assert(!xme::derived_from<D2, B>);
        static_assert(!xme::derived_from<D2, D1>);
    }

    {
        static_assert(xme::convertible_to<int, int>);
        static_assert(xme::convertible_to<const int, int>);
        static_assert(xme::convertible_to<int&, int>);
        static_assert(xme::convertible_to<int&, const int&>);
        static_assert(xme::convertible_to<int, int&&>);
    }

    {
        static_assert(xme::common_reference_with<int&&, const int>);
        static_assert(xme::common_reference_with<const int&&, int&>);
        static_assert(xme::common_reference_with<int&, float&>);

        static_assert(xme::common_with<int, char&>);
        static_assert(!xme::common_with<int, char*>);
        static_assert(xme::common_with<decltype(nullptr), char*>);
    }

    {
        static_assert(xme::integral<int>);
        static_assert(xme::integral<bool>);
        static_assert(xme::integral<const signed char>);
        static_assert(xme::integral<const volatile unsigned char>);
        static_assert(!xme::integral<float>);
        static_assert(!xme::integral<int&>);

        static_assert(xme::signed_integral<int>);
        static_assert(!xme::signed_integral<unsigned int>);

        static_assert(xme::unsigned_integral<unsigned int>);
        static_assert(!xme::unsigned_integral<char>);

        static_assert(xme::floating_point<float>);
        static_assert(xme::floating_point<const double>);
        static_assert(xme::floating_point<long double>);
        static_assert(!xme::floating_point<float&>);

        static_assert(xme::arithmetic<int>);
        static_assert(xme::arithmetic<float>);
    }

    {
        static_assert(xme::assignable_from<int&, int>);
        static_assert(xme::assignable_from<int&, int&&>);
        static_assert(xme::assignable_from<int&, const int&>);
        static_assert(!xme::assignable_from<const int&, int>);
    }

    {
        struct Foo {};
        struct Foo2 {
            ~Foo2() = delete;
        };
        struct Foo3 {
            ~Foo3() noexcept(false) = default;
        };
        static_assert(xme::destructible<int>);
        static_assert(xme::destructible<Foo>);
        static_assert(!xme::destructible<Foo2>);
        static_assert(!xme::destructible<Foo3>);

        struct Foo4 {
            Foo4() = delete;
            Foo4(int) {}
        };
        static_assert(xme::constructible_from<Foo>);
        static_assert(!xme::constructible_from<Foo4>);
        static_assert(xme::constructible_from<Foo4, int>);
        static_assert(xme::constructible_from<Foo4, int&>);
        static_assert(xme::constructible_from<Foo4, int&&>);

        static_assert(!xme::default_initializable<int&>);
        static_assert(xme::default_initializable<Foo>);
        static_assert(!xme::default_initializable<Foo4>);

        struct Foo5 {
            Foo5(const Foo5&) = delete;
            Foo5(Foo5&&)      = delete;
        };
        struct Foo6 {
            Foo6(const Foo6&) = delete;
            Foo6(Foo6&&)      = default;
        };

        static_assert(!xme::move_constructible<Foo2>);
        static_assert(xme::move_constructible<Foo4>);
        static_assert(!xme::move_constructible<Foo5>);
        static_assert(xme::move_constructible<Foo5&>);
        static_assert(xme::move_constructible<Foo5&&>);
        static_assert(xme::move_constructible<Foo6>);

        static_assert(xme::copy_constructible<Foo4>);
        static_assert(!xme::copy_constructible<Foo6>);
        static_assert(xme::copy_constructible<Foo6&>);
        static_assert(!xme::copy_constructible<Foo6&&>);
    }
}
