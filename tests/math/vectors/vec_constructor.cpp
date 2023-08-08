#include "common.hpp"

template<std::size_t Size, int...Ints>
int testConstructors() {
    int errors = 0;
    {
        std::array numbers{Ints...};
        xme::Vector<double, Size> v1{Ints...};
        xme::Vector<double, Size> v2{5};
        xme::Vector<double, Size> v3{v1};

        std::vector<short> errorList;
        for(auto t : std::views::zip(numbers, v1, v3))
            errorList.emplace_back(std::get<0>(t) == std::get<1>(t) && std::get<0>(t) == std::get<2>(t));
        
        errorList.emplace_back(std::ranges::any_of(v2, [](double n){ return n != 5; }));
        
        bool error = std::ranges::all_of(errorList, isError);
        if(error) {
            std::cerr << "vec" << Size << " constructor error\n"; 
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testConstructors<2, 5, 2>();
    errors += testConstructors<3, -7, -2, 3>();
    errors += testConstructors<4, 1, 2, 5, 7>();
    errors += testConstructors<5, 2, 1, -5, 3, -8>();
    return errors;
}