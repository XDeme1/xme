#include <xme/core/concepts/concepts.hpp>

int main() {
    {
        static_assert(xme::same_as_c<int, int>);
        static_assert(!xme::same_as_c<int, const int>);
        static_assert(!xme::same_as_c<int, int&>);
    }

    {
        class B {};
        class D1 : public B {};
        class D2 : B {};
        static_assert(xme::derived_from_c<B, B>);
        static_assert(xme::derived_from_c<D1, B>);
        static_assert(!xme::derived_from_c<D2, B>);
        static_assert(!xme::derived_from_c<D2, D1>);
    }

    {
        static_assert(xme::convertible_to_c<int, int>);
        static_assert(xme::convertible_to_c<const int, int>);
        static_assert(xme::convertible_to_c<int&, int>);
        static_assert(xme::convertible_to_c<int&, const int&>);
        static_assert(xme::convertible_to_c<int, int&&>);
    }

    {
        static_assert(xme::common_reference_with_c<int&&, const int>);
        static_assert(xme::common_reference_with_c<const int&&, int&>);
        static_assert(xme::common_reference_with_c<int&, float&>);

        static_assert(xme::common_with_c<int, char&>);
        static_assert(!xme::common_with_c<int, char*>);
        static_assert(xme::common_with_c<decltype(nullptr), char*>);
    }

    {
        static_assert(xme::integral_c<int>);
        static_assert(xme::integral_c<bool>);
        static_assert(xme::integral_c<const signed char>);
        static_assert(xme::integral_c<const volatile unsigned char>);
        static_assert(!xme::integral_c<float>);
        static_assert(!xme::integral_c<int&>);

        static_assert(xme::signed_integral_c<int>);
        static_assert(!xme::signed_integral_c<unsigned int>);

        static_assert(xme::unsigned_integral_c<unsigned int>);
        static_assert(!xme::unsigned_integral_c<char>);

        static_assert(xme::floating_point_c<float>);
        static_assert(xme::floating_point_c<const double>);
        static_assert(xme::floating_point_c<long double>);
        static_assert(!xme::floating_point_c<float&>);

        static_assert(xme::arithmetic_c<int>);
        static_assert(xme::arithmetic_c<float>);
    }

    {
        static_assert(xme::assignable_from_c<int&, int>);
        static_assert(xme::assignable_from_c<int&, int&&>);
        static_assert(xme::assignable_from_c<int&, const int&>);
        static_assert(!xme::assignable_from_c<const int&, int>);
    }

    {
        static_assert(xme::swappable_c<int>);
        static_assert(!xme::swappable_c<const int>);
    }

    {
        struct Foo {};
        struct Foo2 {
            ~Foo2() = delete;
        };
        struct Foo3 {
            ~Foo3() noexcept(false) = default;
        };
        static_assert(xme::destructible_c<int>);
        static_assert(xme::destructible_c<Foo>);
        static_assert(!xme::destructible_c<Foo2>);
        static_assert(!xme::destructible_c<Foo3>);

        struct Foo4 {
            Foo4() = delete;
            Foo4(int) {}
        };
        static_assert(xme::constructible_from_c<Foo>);
        static_assert(!xme::constructible_from_c<Foo4>);
        static_assert(xme::constructible_from_c<Foo4, int>);
        static_assert(xme::constructible_from_c<Foo4, int&>);
        static_assert(xme::constructible_from_c<Foo4, int&&>);

        static_assert(!xme::default_initializable_c<int&>);
        static_assert(xme::default_initializable_c<Foo>);
        static_assert(!xme::default_initializable_c<Foo4>);

        struct Foo5 {
            Foo5(const Foo5&) = delete;
            Foo5(Foo5&&)      = delete;
        };
        struct Foo6 {
            Foo6(const Foo6&) = delete;
            Foo6(Foo6&&)      = default;
        };

        static_assert(!xme::move_constructible_c<Foo2>);
        static_assert(xme::move_constructible_c<Foo4>);
        static_assert(!xme::move_constructible_c<Foo5>);
        static_assert(xme::move_constructible_c<Foo5&>);
        static_assert(xme::move_constructible_c<Foo5&&>);
        static_assert(xme::move_constructible_c<Foo6>);

        static_assert(xme::copy_constructible_c<Foo4>);
        static_assert(!xme::copy_constructible_c<Foo6>);
        static_assert(xme::copy_constructible_c<Foo6&>);
        static_assert(!xme::copy_constructible_c<Foo6&&>);
    }

    {
        struct Foo {
            bool operator==(const Foo&) = delete;
        };

        static_assert(xme::equality_comparable_c<int&&>);
        static_assert(xme::equality_comparable_c<float>);
        static_assert(!xme::equality_comparable_c<Foo>);
    }

    {
        struct Foo {
            bool operator==(const Foo&) const  = default;
            auto operator<=>(const Foo&) const = delete;
        };

        static_assert(!xme::totally_ordered_c<Foo>);
        static_assert(xme::equality_comparable_c<Foo>);
    }
}
