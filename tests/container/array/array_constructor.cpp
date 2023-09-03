#include "../common.hpp"

int main() {
    int errors = 0;
    {
        xme::Array<float> a;
        std::array results{
            a.begin() == a.end(),
            a.capacity() == 0,
            a.size() == 0,
            a.isEmpty() == true,
        };

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Array() error\n";
        }
    }

    {
        xme::Array<float> a(5);
        std::array results{
            a.begin() == a.end(),
            a.capacity() == 5,
            a.size() == 0,
            a.isEmpty() == true,
        };

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Array(std::size_t) error\n";
        }
    }

    {
        xme::Array<float> a(5, 7);
        std::vector<short> results{
            a.begin() != a.end(),
            a.capacity() == 5,
            a.size() == 5,
            a.isEmpty() == false,
        };

        auto begin = a.cbegin();
        for (std::size_t i = 0; i < 5; ++i)
            results.emplace_back(*(begin++) == 7);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Array(std::size_t, const T&) error\n";
        }
    }

    {
        xme::Array<float> a{1, 2, 6, -3};
        std::vector<short> results{
            a.begin() != a.end(),
            a.isEmpty() == false,
        };

        auto begin = a.begin();
        results.emplace_back(*(begin++) == 1);
        results.emplace_back(*(begin++) == 2);
        results.emplace_back(*(begin++) == 6);
        results.emplace_back(*(begin++) == -3);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Array(std::initializer_list<T>) error\n";
        }
    }
    const std::vector<int> v{1, 5, 3, 2};
    {
        xme::Array<float> a{v.begin(), v.end()};
        std::vector<short> results{
            a.capacity() == 4,
            a.size() == 4,
        };

        auto begin = a.begin();
        results.emplace_back(*(begin++) == 1);
        results.emplace_back(*(begin++) == 5);
        results.emplace_back(*(begin++) == 3);
        results.emplace_back(*(begin++) == 2);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Array(Iter, Sent) error\n";
        }
    }

    {
        xme::Array<float> a{v};
        std::vector<short> results{
            a.capacity() == 4,
            a.size() == 4,
        };

        auto begin = a.begin();
        results.emplace_back(*(begin++) == 1);
        results.emplace_back(*(begin++) == 5);
        results.emplace_back(*(begin++) == 3);
        results.emplace_back(*(begin++) == 2);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Array(R&&) error\n";
        }
    }

    {
        const xme::Array<float> a{v};
        xme::Array<float> b{a};

        std::vector<short> results{
            a.begin() != b.begin(),
            a.end() != b.end(),
        };

        auto begin1 = a.begin();
        auto begin2 = b.begin();
        results.emplace_back(*(begin1++) == *(begin2++));
        results.emplace_back(*(begin1++) == *(begin2++));
        results.emplace_back(*(begin1++) == *(begin2++));
        results.emplace_back(*(begin1++) == *(begin2++));

        xme::Array<float> c{std::move(b)};
        auto begin3 = c.begin();

        results.emplace_back(b.begin() == b.end());
        results.emplace_back(b.isEmpty() == true);
        results.emplace_back(*(begin3++) == 1);
        results.emplace_back(*(begin3++) == 5);
        results.emplace_back(*(begin3++) == 3);
        results.emplace_back(*(begin3++) == 2);

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            ++errors;
            std::cerr << "xme::Array(const Array&) || xme::Array(Array&&) error\n";
        }
    }
    std::vector<int> a;
    a.emplace_back(1);
    return errors;
}

