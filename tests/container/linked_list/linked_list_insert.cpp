#include "../common.hpp"

int main() {
    int errors = 0;
    std::vector<float> v{8, 4, 7};
    {
        xme::LinkedList<float> a;
        int i = 3;
        a.insertAfter(a.cbeforeBegin(), v.begin(), v.end());
        a.insertAfter(a.cbeforeBegin(), i);
        a.insertAfter(a.begin(), std::move(i));

        auto begin = a.cbegin();
        std::vector<short> results;
        results.emplace_back(*(begin++) == 3);
        results.emplace_back(*(begin++) == 3);
        results.emplace_back(*(begin++) == 8);
        results.emplace_back(*(begin++) == 4);
        results.emplace_back(*(begin++) == 7);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList::insertAfter 1 error\n";
        }
    }

    {
        xme::LinkedList<float> a{6, 4, 9};
        a.insertAfter(a.cbegin(), v);

        auto begin = a.cbegin();
        std::vector<short> results;
        results.emplace_back(*(begin++) == 6);
        results.emplace_back(*(begin++) == 8);
        results.emplace_back(*(begin++) == 4);
        results.emplace_back(*(begin++) == 7);
        results.emplace_back(*(begin++) == 4);
        results.emplace_back(*(begin++) == 9);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList::insertAfter 2 error\n";
        }
    }
    return errors;
}