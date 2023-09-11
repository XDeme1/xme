#include "common.hpp"
#include <algorithm>

int testAccess() {
    int errros = 0;
    {
        xme::vec4 v1{1, 6, 3, 0};
        xme::Vector<float, 6> v2{9, -5, 2, 7, 3, 1};
        std::array results{
            v1[0] == 1,  v1[1] == 6, v1[2] == 3, v1[3] == 0, v2[0] == 9,
            v2[1] == -5, v2[2] == 2, v2[3] == 7, v2[4] == 3, v2[5] == 1,
        };

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Vector<T, Size>::operator[] operator error\n";
            ++errros;
        }
    }

    {
        xme::vec3 v1{5, 3, -3};
        auto&& [a, b, c] = v1;
        decltype(auto) d = get<0>(v1);

        static_assert(std::is_same_v<float, decltype(a)>);
        static_assert(std::is_same_v<float, decltype(b)>);
        static_assert(std::is_same_v<float, decltype(c)>);
        static_assert(std::is_same_v<float&, decltype(d)>);
        
        std::array results{
            a == 5,
            b == 3,
            c == -3,
            d == 5,
        };

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "xme::Vector structring binding error\n";
            ++errros;
        }
    }

    {
        xme::vec4 v1{1, 2, 3, 4};
        const xme::vec4 v2{1, 2, 3, 4};
        static_assert(std::is_same_v<float*, decltype(begin(v1))>);
        static_assert(std::is_same_v<float*, decltype(end(v1))>);
        static_assert(std::is_same_v<const float*, decltype(begin(v2))>);
        static_assert(std::is_same_v<const float*, decltype(end(v2))>);

        std::vector<short> results;
        int r = 1;
        for(auto&& v : v1)
            results.emplace_back(v == r++);

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "begin(xme::Vector) && end(xme::Vector) error\n";
        }
    }
    return errros;
}

int main() {
    int errors = 0;
    errors += testAccess();
    return errors;
}