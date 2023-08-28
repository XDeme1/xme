#include "common.hpp"
#include <forward_list>
#include <iostream>
int testContructors() {
    int errors = 0;
    {
        xme::LinkedList<float> a;
        const xme::LinkedList<float> b;
        std::array results = std::to_array({
            a.begin() == nullptr,
            a.end() == nullptr,
            a.cbegin() == nullptr,
            a.cend() == nullptr,
            a.begin() == a.cbegin(),
            a.cbegin() == a.begin(),
            a.isEmpty() == true,
        });

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList() error\n";
        }
    }

    {
        xme::LinkedList<float> a{1, 2, 3};
        const xme::LinkedList<float> b{1, 2, 3};
        auto begin = a.begin();
        auto begin2 = a.begin();
        std::vector<short> results{
            a.begin() != nullptr, a.end() == nullptr,      a.cbegin() != nullptr,
            a.cend() == nullptr,  a.begin() == a.cbegin(), a.front() == 1,
            !a.isEmpty(),
        };
        results.emplace_back(*(begin++) == 1);
        results.emplace_back(*(begin++) == 2);
        results.emplace_back(*(begin++) == 3);

        results.emplace_back(*begin2 == 1);
        ++begin2;
        results.emplace_back(*begin2 == 2);
        ++begin2;
        results.emplace_back(*begin2 == 3);
        ++begin2;

        results.emplace_back(begin == nullptr);
        results.emplace_back(begin2 == nullptr);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList(std::initializer_list) error\n";
        }
    }
    std::vector<float> v{3, 2, 1};
    {
        xme::LinkedList<float> a{v.begin(), v.end()};
        const xme::LinkedList<float> b{v.begin(), v.end()};
        auto begin = a.begin();
        std::vector<short> results{
            a.front() == 3,
        };

        results.emplace_back(*(begin++) == 3);
        results.emplace_back(*(begin++) == 2);
        results.emplace_back(*(begin++) == 1);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList(Iter, Sent) error";
        }
    }

    {
        xme::LinkedList<float> a{v};
        const xme::LinkedList<float> b{v};
        auto begin = a.begin();
        std::vector<short> results{
            a.front() == 3,
        };

        results.emplace_back(*(begin++) == 3);
        results.emplace_back(*(begin++) == 2);
        results.emplace_back(*(begin++) == 1);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList(R&&) error";
        }
    }

    {
        xme::LinkedList<float> a{v};
        const xme::LinkedList<float> b{v};
        xme::LinkedList<float> c{std::move(a)};

        auto begin = c.begin();
        std::vector<short> results{
            c.begin() != nullptr, a.begin() == nullptr, a.isEmpty(),
            !c.isEmpty(),         c.front() == 3,
        };

        results.emplace_back(*(begin++) == 3);
        results.emplace_back(*(begin++) == 2);
        results.emplace_back(*(begin++) == 1);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList(xme::LinkedList&&) error";
        }
    }
    return errors;
}

int testPushPop() {
    int errors = 0;
    {
        xme::LinkedList<float> a;
        int i = 9;
        a.pushFront(5);
        a.pushFront(3);
        a.pushFront(-3);
        a.pushFront(i);

        auto begin = a.begin();
        std::vector<short> results;
        results.emplace_back(*(begin++) == 9);
        results.emplace_back(*(begin++) == -3);
        results.emplace_back(*(begin++) == 3);
        results.emplace_back(*(begin++) == 5);
        results.emplace_back(a.front() == 9);

        a.popFront();
        results.emplace_back(a.front() == -3);
        a.popFront();
        results.emplace_back(a.front() == 3);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr
                << "xme::LinkedList::pushFront && xme::LinkedList::popFront error\n";
        }
    }

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
        int i = 5;
        a.emplaceAfter(a.beforeBegin(), 2);
        a.emplaceAfter(a.begin(), 9);
        a.emplaceAfter(a.beforeBegin(), -3);

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

    std::vector<float> v{8, 4, 7};
    {
        xme::LinkedList<float> a;
        int i = 3;
        a.insertAfter(a.cbeforeBegin(), v.begin(), v.end());
        a.insertAfter(a.cbeforeBegin(), i);
        a.insertAfter(a.cbegin(), v);

        auto begin = a.cbegin();
        std::vector<short> results;
        results.emplace_back(*(begin++) == 3);
        results.emplace_back(*(begin++) == 8);
        results.emplace_back(*(begin++) == 4);
        results.emplace_back(*(begin++) == 7);
        results.emplace_back(*(begin++) == 8);
        results.emplace_back(*(begin++) == 4);
        results.emplace_back(*(begin++) == 7);

        a.clear();

        results.emplace_back(a.isEmpty());
        a.clear(); // should not crash when calling clear with empty LinkedList

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList::insertAfter error\n";
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testContructors();
    errors += testPushPop();
    return errors;
}