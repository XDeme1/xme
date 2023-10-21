#include "common.hpp"

namespace math = xme::math;

template<std::size_t Size>
int test_mat() {
    int errors = 0;
    {
        math::Matrix<float, Size> m1;
        math::Matrix<float, Size> m2{6};

        std::vector<short> errorList;
        for (std::size_t i = 0; i < Size; ++i) {
            for(auto j = 0u; j < Size; ++j) {
                errorList.emplace_back(m1[i][j] == ((i == j) ? 1 : 0));
                errorList.emplace_back(m2[i][j] == ((i == j) ? 6 : 0));
            }
        }

        bool error = std::ranges::any_of(errorList, isError);
        if(error) {
            std::cerr << "mat" << Size << " constructor error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_mat<2>();
    errors += test_mat<3>();
    errors += test_mat<4>();
    errors += test_mat<5>();
    return errors;
}