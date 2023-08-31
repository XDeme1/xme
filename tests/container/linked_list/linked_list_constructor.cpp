#include "../common.hpp"

int main() {
    int errors = 0;
    // xme::LinkedList()
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
    // xme::LinkedList(std::size_t)
    {
        xme::LinkedList<float> a(5);
        const xme::LinkedList<float> b(5);
        std::vector<short> results = {
            a.begin() != nullptr, a.end() == nullptr,   a.cbegin() != nullptr,
            a.cend() == nullptr,  a.isEmpty() == false,
        };

        auto begin = a.begin();
        while (begin != a.end()) {
            results.emplace_back((*begin) == 0);
            ++begin;
        }

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList(std::size_t) error\n";
        }
    }
    // xme::LinkedList(std::size_t, const T&)
    {
        xme::LinkedList<float> a(5, 3);
        const xme::LinkedList<float> b(5, 3);
        std::vector<short> results = {
            a.begin() != nullptr, a.end() == nullptr,   a.cbegin() != nullptr,
            a.cend() == nullptr,  a.isEmpty() == false,
        };

        auto begin = a.begin();
        while (begin != a.end()) {
            results.emplace_back((*begin) == 3);
            ++begin;
        }

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList(std::size_t, const T&) error\n";
        }
    }
    // xme::LinkedList(std::initializer_list)
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
    // xme::LinkedList(Iter, Sent)
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
    // xme::LinkedList(R&&)
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
    // xme::LinkedList(const xme::LinkedList&)
    {
        xme::LinkedList<float> a{v};
        const xme::LinkedList<float> b{v};
        xme::LinkedList<float> c{a};

        auto begin = c.begin();
        auto begin2 = a.begin();
        std::vector<short> results{
            c.begin() != nullptr, a.begin() != nullptr, a.isEmpty() == false,
            c.isEmpty() == false,         c.front() == a.front(),
        };

        results.emplace_back(*(begin++) == *(begin2++));
        results.emplace_back(*(begin++) == *(begin2++));
        results.emplace_back(*(begin++) == *(begin2++));

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::LinkedList(const xme::LinkedList&) error";
        }
    }
    // xme::LinkedList(xme::LinkedList&&)
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