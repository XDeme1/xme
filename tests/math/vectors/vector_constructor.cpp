#include "common.hpp"

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

void testDeductionGuide() {
    {
        xme::Vector v1{1, 2, 3};
        xme::Vector v2{1.f, 2, 3, 4};
        xme::Vector v3{2, 1.0, 3, 4, 5};
        static_assert(std::is_same_v<decltype(v1), xme::Vector<int, 3>>);
        static_assert(std::is_same_v<decltype(v2), xme::Vector<float, 4>>);
        static_assert(std::is_same_v<decltype(v3), xme::Vector<double, 5>>);
    }
}

int main() {
    int errors = 0;
    errors += testConstructors<2>(std::make_index_sequence<2>{});
    errors += testConstructors<3>(std::make_index_sequence<3>{});
    errors += testConstructors<4>(std::make_index_sequence<4>{});
    errors += testConstructors<5>(std::make_index_sequence<5>{});
    testDeductionGuide();
    return errors;
}