#include "../common.hpp"

int main() {
    int errors = 0;
    {
        xme::Pair<int, int> p1{1, 5};
        xme::Pair<int, float> p2{3, 1.5};
        xme::Pair<std::string, int> p3{"Hello", 2};

        static_assert(std::is_trivially_assignable_v<decltype(p1), decltype(p1)>);
        static_assert(!std::is_trivially_assignable_v<decltype(p1), decltype(p2)>);
        static_assert(!std::is_trivially_assignable_v<decltype(p3),
                                                      decltype(p3)>);

        std::vector<short> results{};

        p1 = xme::Pair{5, 3};
        results.emplace_back(get<0>(p1) == 5);
        results.emplace_back(get<1>(p1) == 3);

        p1 = p2;
        results.emplace_back(get<0>(p1) == 3);
        results.emplace_back(get<1>(p1) == 1);
        results.emplace_back(get<0>(p3) == "Hello");
        results.emplace_back(get<1>(p3) == 2);

        xme::Pair<std::string, int> p4{"Test", 1};
        xme::Pair<std::string, int> p5{"Test2", 1};
        p3 = p4;
        results.emplace_back(get<0>(p3) == "Test");
        results.emplace_back(get<0>(p4) == "Test");

        p3 = std::move(p5);
        results.emplace_back(get<0>(p3) == "Test2");
        results.emplace_back(get<0>(p5).empty());

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Pair operator=(P&&) error\n";
        }
    }

    {
        xme::Pair<int, int> p1{5, 1};
        p1 = {1, 2};

        std::vector<short> results;
        results.emplace_back(get<0>(p1) == 1);
        results.emplace_back(get<1>(p1) == 2);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Pair::operator=() default error\n";
        }
    }

    return errors;
}