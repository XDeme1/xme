#include "../common.hpp"

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
            ++errors;
            std::cerr << "xme::Tuple::swap error\n";
        }
    }

    {
        std::vector<short> results;
        xme::Tuple<std::string, std::string> t1{"Hello", "World"};
        const xme::Tuple t2{t1};

        auto str1 = xme::apply([](std::string& s1, std::string& s2) { return s1 + s2; }, t1);
        auto str2 = xme::apply([](const std::string& s1, const std::string& s2){ return s1 + s2; }, t2);
        auto&& str3 = xme::apply([](std::string&& s1, std::string&& s2) { return s1 + s2; }, std::move(t1));

        results.emplace_back(str1 == "HelloWorld");
        results.emplace_back(str2 == "HelloWorld");
        results.emplace_back(str3 == "HelloWorld");

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
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
            ++errors;
            std::cerr << "xme::tie error\n";
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
            ++errors;
            std::cerr << "xme::makeTuple error\n";
        }
    }
    
    {
        std::vector<short> results;
        int a1 = 2;
        const int a2 = 3;
        auto t1 = xme::forwardAsTuple(5, a1, a2);
        static_assert(std::is_same_v<decltype(t1), xme::Tuple<int&&, int&, const int&>>);

        results.emplace_back(get<0>(t1) == 0); //literals doesn't get stored
        results.emplace_back(get<1>(t1) == 2);
        results.emplace_back(get<2>(t1) == 3);

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
            std::cerr << "xme::forwardAsTuple\n";
        }
    }

    {
        std::vector<short> results;
        xme::Tuple<int, const int, const int&> t1{1, 5, 3};
        xme::Tuple<> t2;
        xme::Tuple<float> t3{0.5};
        auto t4 = xme::tupleCat(t1, t2, t3);

        static_assert(std::is_same_v<decltype(t4), xme::Tuple<int, int, const int&, float>>);

        results.emplace_back(get<0>(t4) == 1);
        results.emplace_back(get<1>(t4) == 5);
        results.emplace_back(get<2>(t4) == 3);
        results.emplace_back(get<3>(t4) == 0.5f);

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
            std::cerr << "xme::tupleCat\n";
        }
    }

    return errors;
}