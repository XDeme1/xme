#include "../common.hpp"

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
    }

    {
        const xme::LinkedList<float> a{v};
        xme::LinkedList<float> b{2, 1, 3, 5, 4};
        b = a;

        auto begin1 = b.begin();
        std::vector<short> results;
        results.emplace_back(b.begin() != a.begin());
        results.emplace_back(*(begin1++) == 1);
        results.emplace_back(*(begin1++) == 2);
        results.emplace_back(*(begin1++) == 3);
        results.emplace_back(begin1 == nullptr);

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
            std::cerr << "xme::LinkedList::operator=(const xme::LinkedList&) error\n";
        }
    }

    {
        xme::LinkedList<float> a{v};
        xme::LinkedList<float> b{2, 1, 3, 5, 4};
        b = std::move(a);

        auto begin1 = b.begin();
        std::vector<short> results;
        results.emplace_back(b.begin() != a.begin());
        results.emplace_back(*(begin1++) == 1);
        results.emplace_back(*(begin1++) == 2);
        results.emplace_back(*(begin1++) == 3);
        results.emplace_back(begin1 == nullptr);
        results.emplace_back(a.begin() == nullptr);

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
            std::cerr << "xme::LinkedList::operator=(xme::LinkedList&&) error\n";
        }
    }

    {
        xme::LinkedList<float> a{v};
        a = {1, 5, 3, 2};

        auto begin1 = a.begin();
        std::vector<short> results;
        results.emplace_back(*(begin1++) == 1);
        results.emplace_back(*(begin1++) == 5);
        results.emplace_back(*(begin1++) == 3);
        results.emplace_back(*(begin1++) == 2);
        results.emplace_back(begin1 == nullptr);

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
            std::cerr << "xme::LinkedList::operator=(std::initializer_list<T>) error\n";
        }
    }
    return errors;
}