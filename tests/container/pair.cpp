#include "common.hpp"
#include <xme/container/pair.hpp>
#include <xme/container/tuple.hpp>

static_assert(xme::CTupleLike<xme::Pair<int, int&>>);
static_assert(xme::CPairLike<xme::Pair<int, int&>>);
static_assert(xme::CPairLike<const xme::Pair<int, int&>>);

static_assert(std::is_aggregate_v<xme::Pair<int, std::string>>);

static_assert(std::is_trivial_v<xme::Pair<int, float>>);
static_assert(std::is_trivial_v<xme::Pair<int&, float&&>>);
static_assert(!std::is_trivial_v<xme::Pair<std::string, int>>);

static_assert(std::is_trivially_destructible_v<xme::Pair<int, float>>);
static_assert(std::is_trivially_destructible_v<xme::Pair<int&, float&&>>);
static_assert(!std::is_trivially_destructible_v<xme::Pair<std::string, int>>);

static_assert(std::is_trivially_move_constructible_v<xme::Pair<int, float>>);
static_assert(std::is_trivially_move_constructible_v<xme::Pair<int&, float&&>>);
static_assert(!std::is_trivially_move_constructible_v<xme::Pair<std::string, int>>);

static_assert(std::is_trivially_copy_constructible_v<xme::Pair<int, float>>);
static_assert(std::is_trivially_copy_constructible_v<xme::Pair<int&, float&>>);
static_assert(!std::is_trivially_copy_constructible_v<xme::Pair<std::string, int>>);

static_assert(std::is_trivially_default_constructible_v<xme::Pair<int, float>>);
static_assert(
    !std::is_trivially_default_constructible_v<xme::Pair<int&&, float&>>); // Because of &
static_assert(!std::is_trivially_default_constructible_v<xme::Pair<std::string, int>>);

void testDeductionGuides() {
    int a = 2;
    const int ca = 1;;
    int& ra = a;
    const int& rca = ca;

    xme::Pair p1{1, 5};
    xme::Pair p2{a, ca};
    xme::Pair p3{ra, rca};
    xme::Pair p4{std::ref(a), std::ref(ca)};

    static_assert(std::is_same_v<decltype(p1), xme::Pair<int, int>>);
    static_assert(std::is_same_v<decltype(p2), xme::Pair<int, int>>);
    static_assert(std::is_same_v<decltype(p3), xme::Pair<int, int>>);
    static_assert(std::is_same_v<decltype(p4), xme::Pair<int&, const int&>>);
}

int testAccess() {
    int errors = 0;
    {
        xme::Pair<int, const float&> p{5, 1.5f};
        static_assert(std::is_same_v<decltype(get<0>(p)), int&>);
        static_assert(std::is_same_v<decltype(get<1>(p)), const float&>);
        static_assert(std::is_same_v<decltype(get<0>(std::move(p))), int&&>);
        static_assert(std::is_same_v<decltype(get<1>(std::move(p))), const float&>);

        bool error = get<0>(p) != 5 || get<1>(p) != 1.5;
        if (error) {
            std::cerr << "xme::Pair get error\n";
            ++errors;
        }
    }
    {
        xme::Pair p{3, 2.5f};
        auto&& [a, b] = p;
        bool error = a != 3 || b != 2.5;
        if (error) {
            std::cerr << "xme::Pair structured binding error\n";
            ++errors;
        }
    }
    return errors;
}

int testMoveCopy() {
    int errors = 0;
    {
        xme::Pair<std::string, int> p1{"C++", 5};
        xme::Pair p2{p1};
        bool error = p1.first != "C++" || p2.first != "C++";
        if(error) {
            std::cerr << "xme::Pair copy constructor error\n";
            ++errors;
        }
    }
    {
        xme::Pair<std::string, int> p1{"C++", 5};
        xme::Pair p2{std::move(p1)};
        bool error = !p1.first.empty() || p2.first != "C++";
        if(error) {
            std::cerr << "xme::Pair move constructor error\n";
            ++errors;
        }
    }
    {
        xme::Pair<std::string, int> p1{"C++", 5};
        xme::Pair<std::string, int> p2{"Test", 2};
        p1 = p2; 
        bool error = p1.first != "Test" || p2.first != "Test";
        if(error) {
            std::cerr << "xme::Pair copy assignment error\n";
            ++errors;
        }
    }
    {
        xme::Pair<std::string, int> p1{"C++", 5};
        xme::Pair<std::string, int> p2{"Test", 2};
        p1 = std::move(p2); 
        bool error = p1.first != "Test" || !p2.first.empty();
        if(error) {
            std::cerr << "xme::Pair move assignment error\n";
            ++errors;
        }
    }
    {
        xme::Pair<std::string, int> p1{"C++", 5};
        p1 = {"Hello", 1}; 
        bool error = p1.first != "Hello";
        if(error) {
            std::cerr << "xme::Pair assignment error\n";
            ++errors;
        }
    }
    {
        xme::Pair<std::string, int> p1{"Te", 3};
        xme::Tuple<std::string, int> t{"Op", 1};
        p1 = std::move(t);
        bool error = p1.first != "Op" || !get<0>(t).empty();
        if(error) {
            std::cerr << "xme::Pair generic assignment error\n";
            ++errors;
        }
    }
    return errors;
}

int testOperations() {
    int errors = 0;
    {
        std::vector<short> results;
        xme::Pair<std::string, int> t1{"Hello", 1};
        xme::Pair<std::string, int> t2{"C++", 5};

        xme::swap(t1, t2);

        bool error = t1.first != "C++" || t1.second != 5;
        error |= t2.first != "Hello" || t2.second != 1;
        if(error) {
            ++errors;
            std::cerr << "xme::Pair swap error\n";
        }
    }

    {
        xme::Pair<std::string, std::string> p1{"Hello", "World"};
        const xme::Pair p2{p1};

        auto str1 = xme::apply([](std::string& s1, std::string& s2) { return s1 + s2; }, p1);
        auto str2 = xme::apply([](const std::string& s1, const std::string& s2){ return s1 + s2; }, p2);
        auto&& str3 = xme::apply([](std::string&& s1, std::string&& s2) { return s1 + s2; }, std::move(p1));

        std::string result{"HelloWorld"};
        bool error = str1 != result || str2 != result || str3 != result;

        if(error) {
            ++errors;
            std::cerr << "xme::Pair apply error\n";
        }
    }

    {
        auto p1 = xme::makePair(std::string{"Hello World"}, std::string{"C++ 23"});
        auto p2 = xme::makePair(std::ref(get<0>(p1)), std::ref(get<1>(p1)));
        
        static_assert(std::is_same_v<xme::Pair<std::string, std::string>, decltype(p1)>);
        static_assert(std::is_same_v<xme::Pair<std::string&, std::string&>, decltype(p2)>);

        bool error = p1.first != "Hello World" || p1.second != "C++ 23";
        error |= p1.first.begin() != p2.first.begin();
        if(error) {
            ++errors;
            std::cerr << "xme::makePair error\n";
        }
    }

    return errors;
}

int main() {
    int errors = 0;
    testDeductionGuides();
    errors += testAccess();
    errors += testMoveCopy();
    errors += testOperations();
    return errors;
}