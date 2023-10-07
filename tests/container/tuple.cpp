#include "common.hpp"
#include <xme/container/tuple.hpp>

struct Empty {};

static_assert(std::is_aggregate_v<xme::Tuple<>>);
static_assert(std::is_aggregate_v<xme::Tuple<std::string, int>>);

static_assert(std::is_empty_v<xme::Tuple<>>);
static_assert(std::is_empty_v<xme::Tuple<Empty, Empty>>);

static_assert(std::is_trivial_v<xme::Tuple<>>);
static_assert(std::is_trivial_v<xme::Tuple<int, int&, int&&>>);
static_assert(!std::is_trivial_v<xme::Tuple<std::string>>);

static_assert(std::is_trivially_destructible_v<xme::Tuple<int, int&, int&&>>);
static_assert(!std::is_trivially_destructible_v<xme::Tuple<std::string, int>>);

static_assert(std::is_trivially_move_constructible_v<xme::Tuple<int, int&, int&&>>);
static_assert(!std::is_trivially_move_constructible_v<xme::Tuple<std::string, int>>);

static_assert(std::is_trivially_copy_constructible_v<xme::Tuple<int, int&, const int&>>);
static_assert(!std::is_trivially_copy_constructible_v<xme::Tuple<std::string, int>>);

static_assert(std::is_trivially_default_constructible_v<xme::Tuple<int>>);
static_assert(!std::is_trivially_default_constructible_v<xme::Tuple<std::string>>);

static_assert(std::is_trivially_assignable_v<xme::Tuple<int>, xme::Tuple<int>>);
static_assert(!std::is_trivially_assignable_v<xme::Tuple<int>, xme::Tuple<float>>);
static_assert(
    !std::is_trivially_assignable_v<xme::Tuple<std::string>, xme::Tuple<std::string>>);

static_assert(xme::CTupleLike<xme::Tuple<>>);
static_assert(xme::CTupleLike<xme::Tuple<int, int, int&>>);
static_assert(xme::CTupleLike<const xme::Tuple<int, int, int&>>);

static_assert(xme::CPairLike<xme::Tuple<int, int>>);
static_assert(!xme::CPairLike<xme::Tuple<>>);

int testAccess() {
    int errors = 0;
    {
        xme::Tuple<int, const float&> t1{5, 1.5f};
        static_assert(std::is_same_v<decltype(get<0>(t1)), int&>);
        static_assert(std::is_same_v<decltype(get<1>(t1)), const float&>);
        static_assert(std::is_same_v<decltype(get<0>(std::move(t1))), int&&>);
        static_assert(std::is_same_v<decltype(get<1>(std::move(t1))), const float&>);

        bool error = get<0>(t1) != 5 || get<1>(t1) != 1.5;
        if (error) {
            std::cerr << "xme::Tuple get error\n";
            ++errors;
        }
    }
    {
        xme::Tuple t1{3, 2.5f};
        auto&& [a, b] = t1;
        static_assert(std::is_same_v<decltype(a), int>);
        static_assert(std::is_same_v<decltype(b), float>);
        bool error = a != 3 || b != 2.5;
        if (error) {
            std::cerr << "xme::Tuple structured binding error\n";
            ++errors;
        }
    }
    return errors;
}

int testAssign() {
    int errors = 0;
    {
        xme::Tuple<std::string> t1{"Hello"};
        xme::Tuple<std::string> t2;
        t2 = t1;
        bool error = get<0>(t1) != "Hello" || get<0>(t2) != "Hello";
        if (error) {
            std::cerr << "xme::Tuple copy assignment error\n";
            ++errors;
        }
    }
    {
        xme::Tuple<std::string> t1{"C++"};
        xme::Tuple<std::string> t2;
        t2 = std::move(t1);
        bool error = !get<0>(t1).empty() || get<0>(t2) != "C++";
        if (error) {
            std::cerr << "xme::Tuple move assignment error\n";
            ++errors;
        }
    }

    {
        xme::Tuple<int, int> t1{5, 1};
        t1 = {1, 2};
        bool error = get<0>(t1) != 1 || get<1>(t1) != 2;

        if (error) {
            ++errors;
            std::cerr << "xme::Tuple::operator=(U&&) error\n";
        }
    }
    return errors;
}

int testOperations() {
    int errors = 0;
    {
        xme::Tuple<std::string> t1{"Hello"};
        xme::Tuple<std::string> t2{"C++"};

        xme::swap(t1, t2);
        bool error = get<0>(t1) != "C++" || get<0>(t2) != "Hello";

        if(error) {
            ++errors;
            std::cerr << "xme::Tuple swap error\n";
        }
    }

    {
        xme::Tuple<std::string, std::string> t1{"Hello", "World"};
        const xme::Tuple t2{t1};

        auto str1 = xme::apply([](std::string& s1, std::string& s2) { return s1 + s2; }, t1);
        auto str2 = xme::apply([](const std::string& s1, const std::string& s2){ return s1 + s2; }, t2);
        auto&& str3 = xme::apply([](std::string&& s1, std::string&& s2) { return s1 + s2; }, std::move(t1));

        bool error = str1 != "HelloWorld" || str2 != "HelloWorld" || str3 != "HelloWorld";

        if(error) {
            ++errors;
            std::cerr << "xme::Tuple apply error\n";
        }
    }

    {
        std::string s1{"He"};
        std::string s2{"23"};

        auto t1 = xme::tie(s1, s2);

        static_assert(std::is_same_v<xme::Tuple<std::string&, std::string&>, decltype(t1)>);

        bool error = get<0>(t1) != "He" || get<1>(t1) != "23"; 
        error |= get<0>(t1).begin() != s1.begin();
        if(error) {
            ++errors;
            std::cerr << "xme::Tuple tie error\n";
        }
    }

    {
        auto t1 = xme::makeTuple(std::string{"World"}, std::string{"23"});
        auto t2 = xme::makeTuple(std::ref(get<0>(t1)), std::ref(get<1>(t1)));
        
        static_assert(std::is_same_v<xme::Tuple<std::string, std::string>, decltype(t1)>);
        static_assert(std::is_same_v<xme::Tuple<std::string&, std::string&>, decltype(t2)>);

        bool error = get<0>(t1) != "World" || get<1>(t1) != "23";
        error |= get<0>(t1).begin() != get<0>(t2).begin();
        if(error) {
            ++errors;
            std::cerr << "xme::Tuple makeTuple error\n";
        }
    }
    
    {
        int a1 = 2;
        const int a2 = 3;
        auto t1 = xme::forwardAsTuple(a1, a2);
        static_assert(std::is_same_v<decltype(t1), xme::Tuple<int&, const int&>>);

        bool error = get<0>(t1) != 2 || get<1>(t1) != 3;
        if(error) {
            ++errors;
            std::cerr << "xme::Tuple forwardAsTuple\n";
        }
    }

    {
        xme::Tuple<int, const int, const int&> t1{1, 5, 3};
        xme::Tuple<> t2;
        xme::Tuple<float> t3{0.5};
        auto t4 = xme::tupleCat(t1, t2, t3);

        static_assert(std::is_same_v<decltype(t4), xme::Tuple<int, int, const int&, float>>);

        bool error = get<0>(t4) != 1 || get<1>(t4) != 5;
        error |= get<2>(t4) != 3 || get<3>(t4) != 0.5f;
        if(error) {
            ++errors;
            std::cerr << "xme::Tuple tupleCat error\n";
        }
    }

    return errors;
}

int main() {
    int errors = 0;
    errors += testAccess();
    errors += testAssign();
    errors += testOperations();
    return errors;
}