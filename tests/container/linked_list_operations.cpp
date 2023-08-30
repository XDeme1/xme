#include "common.hpp"
#include <forward_list>

int main() {
    int errors = 0;
    {
        std::vector<float> v{8, 6, 5};
        xme::LinkedList<float> a{v};

        a.reverse();
        auto begin = a.begin();
        std::vector<short> results;

        results.emplace_back(*(begin++) == 5);
        results.emplace_back(*(begin++) == 6);
        results.emplace_back(*(begin++) == 8);
        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList::reverse() error\n";
        }
    }

    {
        xme::LinkedList<float> a{2, 5, 3, 1};

        std::vector<short> results;
        results.emplace_back(a.begin() != nullptr);
        a.clear();
        results.emplace_back(a.begin() == nullptr);
        results.emplace_back(a.isEmpty() == true);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList::clear() error\n";
        }
    }
    return errors;
}