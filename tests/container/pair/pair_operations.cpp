#include "../common.hpp"

int main() {
    int errors = 0;
    {
        static_assert(xme::CTupleLike<xme::Pair<int, int&>>);
        static_assert(xme::CPairLike<xme::Pair<int, int&>>);
        static_assert(xme::CPairLike<const xme::Pair<int, int&>>);

        std::vector<short> results;
        xme::Pair<std::string, std::string> t1{"Hello", "World"};
        xme::Pair<std::string, std::string> t2{"C++", "23"};

        xme::swap(t1, t2);

        results.emplace_back(get<0>(t1) == "C++");
        results.emplace_back(get<1>(t1) == "23");

        results.emplace_back(get<0>(t2) == "Hello");
        results.emplace_back(get<1>(t2) == "World");

        swap(t1, t2);

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
            std::cerr << "xme::swap error\n";
        }
    }

    {
        std::vector<short> results;
        xme::Pair<std::string, std::string> p1{"Hello", "World"};
        const xme::Pair p2{p1};

        auto str1 = xme::apply([](std::string& s1, std::string& s2) { return s1 + s2; }, p1);
        auto str2 = xme::apply([](const std::string& s1, const std::string& s2){ return s1 + s2; }, p2);
        auto&& str3 = xme::apply([](std::string&& s1, std::string&& s2) { return s1 + s2; }, std::move(p1));

        results.emplace_back(str1 == "HelloWorld");
        results.emplace_back(str2 == "HelloWorld");
        results.emplace_back(str3 == "HelloWorld");

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
            std::cerr << "xme::apply error\n";
        }
    }

    {
        std::vector<short> results;
        auto p1 = xme::makePair(std::string{"Hello World"}, std::string{"C++ 23"});
        auto p2 = xme::makePair(std::ref(get<0>(p1)), std::ref(get<1>(p1)));
        
        static_assert(std::is_same_v<xme::Pair<std::string, std::string>, decltype(p1)>);
        static_assert(std::is_same_v<xme::Pair<std::string&, std::string&>, decltype(p2)>);

        results.emplace_back(get<0>(p1) == "Hello World");
        results.emplace_back(get<1>(p1) == "C++ 23");
        results.emplace_back(get<0>(p1).begin() == get<0>(p2).begin());

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
            std::cerr << "xme::makePair error\n";
        }
    }

    return errors;
}