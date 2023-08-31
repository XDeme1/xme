#include "../common.hpp"

int main() {
    int errors = 0;
    {
        xme::LinkedList<float> a;
        int i = 9;
        a.pushFront(5);
        a.pushFront(i);
        a.pushFront(-3);
        a.pushFront(std::move(i));

        auto begin = a.cbegin();
        std::vector<short> results;
        results.emplace_back(*(begin++) == 9);
        results.emplace_back(*(begin++) == -3);
        results.emplace_back(*(begin++) == 9);
        results.emplace_back(*(begin++) == 5);
        results.emplace_back(a.front() == 9);

        a.popFront();
        results.emplace_back(a.front() == -3);
        a.popFront();
        results.emplace_back(a.front() == 9);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr
                << "xme::LinkedList::pushFront && xme::LinkedList::popFront error\n";
        }
    }
    return errors;
}