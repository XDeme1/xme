#include <xme/ranges/enumerate.hpp>
#include <xme/container/array.hpp>
#include <xme/container/heap.hpp>
#include <xme/container/array_view.hpp>
#include <forward_list>

int test_enumerate() {
    int errors = 0;
    {
        int arr[]{5, 3, 1, 4};
        auto e           = xme::views::enumerate(arr);
        using it         = decltype(e.begin());
        using const_it   = decltype(std::as_const(e).begin());
        using sent       = decltype(e.end());
        using const_sent = decltype(std::as_const(e).end());
        static_assert(std::same_as<it, sent>);
        static_assert(std::same_as<const_it, const_sent>);
        static_assert(std::same_as<it::iterator_concept, std::random_access_iterator_tag>);
        static_assert(std::ranges::random_access_range<decltype(e)>);
        static_assert(requires {
            e.begin() - e.end();
            e.end() - e.begin();
            e.begin() == e.end();
            e.begin() == std::as_const(e).end();
            e.size();
        });

        int order = 0;
        for(auto&& [i, v] : e) {
            errors += order != i;
            errors += arr[i] != v;
            ++order;
        }
        errors += order != 4;

        order   = 0;
        auto e2 = arr | xme::views::enumerate;
        for(auto&& [i, v] : e2) {
            errors += order != i;
            errors += arr[i] != v;
            ++order;
        }
        errors += order != 4;
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_enumerate();
    {
        std::forward_list<int> l{1, 5, 3, 2};
        const auto e     = l | xme::views::enumerate;
        auto b           = l.begin();
        using it         = decltype(e.begin());
        using const_it   = decltype(std::as_const(e).begin());
        using sent       = decltype(e.end());
        using const_sent = decltype(std::as_const(e).end());
        static_assert(!std::same_as<it, sent>);
        static_assert(!std::same_as<const_it, const_sent>);
        static_assert(std::same_as<it::iterator_concept, std::forward_iterator_tag>);
        static_assert(std::ranges::forward_range<decltype(e)>);

        int order = 0;
        for(auto&& [i, v] : e) {
            errors += order != i;
            errors += *b != v;
            ++b;
            ++order;
        }
        errors += order != 4;
    }
    return errors;
}
