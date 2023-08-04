#include <xme/math/math.hpp>
#include <algorithm>
#include <iostream>

bool isError(bool b) { return b == false; }

template<std::size_t Size, std::size_t...Ints>
int testConstructors(std::index_sequence<Ints...>) {
    int errors = 0;
    {
        xme::Vector<double, Size> v1{Ints...};
        xme::Vector<double, Size> v2{5};

        std::array<bool, Size*2> results{};
        std::array expected{Ints...};
        for (std::size_t i = 0; i < Size; ++i) {
            results[i] = v1[i] == expected[i];
            results[Size+i] = v2[i] == 5;
        }
        auto error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector Construction Error\n"; 
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testConstructors<2>(std::make_index_sequence<2>{});
    errors += testConstructors<3>(std::make_index_sequence<3>{});
    errors += testConstructors<4>(std::make_index_sequence<4>{});
    errors += testConstructors<5>(std::make_index_sequence<5>{});
    return errors;
}