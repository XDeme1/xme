#include "../common.hpp"
#include <tuple>

int main() {
    int errors = 0;
    {
        static_assert(xme::CTupleLike<xme::Tuple<>>);
        static_assert(xme::CTupleLike<xme::Tuple<int, int, int&>>);
        static_assert(xme::CTupleLike<xme::Tuple<int, int, int&>&>);

        std::vector<short> results;
        xme::Tuple<std::string, std::string> t1{"Hello", "World"};
        xme::Tuple<std::string, std::string> t2{"C++", "23"};

        swap(t1, t2);

        results.emplace_back(get<0>(t1) == "C++");
        results.emplace_back(get<1>(t1) == "23");

        results.emplace_back(get<0>(t2) == "Hello");
        results.emplace_back(get<1>(t2) == "World");


        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "xme::Tuple::swap error\n";
        }
    }

    {
        std::vector<short> results;
        xme::Tuple<std::string, std::string> t1{"Hello", "World"};

        auto str = xme::apply([](std::string& s1, std::string& s2) { return s1 + s2; }, t1);

        results.emplace_back(str == "HelloWorld");

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "xme::Tuple::apply error\n";
        }
    }

    {
        std::vector<short> results;
        std::string s1{"Hello World"};
        std::string s2{"C++ 23"};

        auto t1 = xme::tie(s1, s2);

        static_assert(std::is_same_v<xme::Tuple<std::string&, std::string&>, decltype(t1)>);

        results.emplace_back(get<0>(t1) == "Hello World");
        results.emplace_back(get<1>(t1) == "C++ 23");
        results.emplace_back(get<0>(t1).begin() == s1.begin());

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "xme::Tuple::tie error\n";
        }
    }

    {
        std::vector<short> results;
        auto t1 = xme::makeTuple(std::string{"Hello World"}, std::string{"C++ 23"});
        auto t2 = xme::makeTuple(std::ref(get<0>(t1)), std::ref(get<1>(t1)));
        
        static_assert(std::is_same_v<xme::Tuple<std::string, std::string>, decltype(t1)>);
        static_assert(std::is_same_v<xme::Tuple<std::string&, std::string&>, decltype(t2)>);

        results.emplace_back(get<0>(t1) == "Hello World");
        results.emplace_back(get<1>(t1) == "C++ 23");
        results.emplace_back(get<0>(t1).begin() == get<0>(t2).begin());

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "xme::Tuple::makeTuple error\n";
        }
    }
    
    return errors;
}