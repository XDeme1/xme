#include "common.hpp"

template<std::size_t Size>
int testMat() {
    int errors = 0;
    {
        xme::Matrix<float, Size> m1;
        xme::Matrix<float, Size> m2{6};

        std::vector<short> errorList;
        for (auto i = 0uz; i < Size; ++i) {
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
    errors += testMat<2>();
    errors += testMat<3>();
    errors += testMat<4>();
    errors += testMat<5>();
    return errors;
}