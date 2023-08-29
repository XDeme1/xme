#include "common.hpp"
#include <forward_list>

int main() {
    int errors = 0;
    {
        xme::LinkedList<float> a{1, 6, 3};
        a.assign({1, 4});

        auto begin = a.begin();
        std::vector<short> results;
        results.emplace_back(*(begin++) == 1);
        results.emplace_back(*(begin++) == 4);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList::assign 1 Error\n";
        }
    }

    std::vector<double> v{ 1, 2, 3};
    {
        xme::LinkedList<float> a;
        a.assign(v);

        auto begin1 = a.begin();
        std::vector<short> results;
        results.emplace_back(*(begin1++) == 1);
        results.emplace_back(*(begin1++) == 2);
        results.emplace_back(*(begin1++) == 3);

        auto begin2 = a.begin();
        a.assign(v.rbegin(), v.rend());
        results.emplace_back(*(begin2++) == 3);
        results.emplace_back(*(begin2++) == 2);
        results.emplace_back(*(begin2++) == 1);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList::assign 2 Error\n";
        }
        std::forward_list<float> c;
    }
    return errors;
}