#include "common.hpp"

int main() {
    int errors = 0;

    {
        xme::LinkedList<float> a;
        int i = 5;
        a.emplaceFront(1);
        a.emplaceFront(i);
        a.emplaceFront(9);

        auto begin = a.begin();
        std::vector<short> results;
        results.emplace_back(*(begin++) == 9);
        results.emplace_back(*(begin++) == 5);
        results.emplace_back(*(begin++) == 1);
        results.emplace_back(a.front() == 9);

        a.popFront();
        results.emplace_back(a.front() == 5);
        a.popFront();
        results.emplace_back(a.front() == 1);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList::emplaceFront error\n";
        }
    }

    {
        xme::LinkedList<float> a;
        a.emplaceAfter(a.cbeforeBegin(), 2);
        a.emplaceAfter(a.cbegin(), 9);
        a.emplaceAfter(a.cbeforeBegin(), -3);

        auto begin = a.begin();
        std::vector<short> results;
        results.emplace_back(*(begin++) == -3);
        results.emplace_back(*(begin++) == 2);
        results.emplace_back(*(begin++) == 9);
        results.emplace_back(a.front() == -3);

        a.popFront();
        results.emplace_back(a.front() == 2);
        a.popFront();
        results.emplace_back(a.front() == 9);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList::emplaceAfter error\n";
        }
    }
    return errors;
}