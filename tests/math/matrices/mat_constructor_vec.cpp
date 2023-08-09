#include "common.hpp"

template<typename...Args, std::size_t Size>
int testMatVec(const xme::Vector<Args, Size>&...v) {
    int errors = 0;
    constexpr std::size_t rows = Size;
    constexpr std::size_t cols = sizeof...(Args);
    using type = std::common_type_t<Args...>;

    static_assert(std::is_same_v<decltype(xme::Matrix{v...}), xme::Matrix<type, cols, rows>>);
    {
        xme::Matrix m{v...};
        std::array<xme::Vector<type, rows>, cols> arr{v...};

        std::vector<short> errorList;
        for(auto i = 0u; i < cols; ++i)
            errorList.emplace_back(m[i] == arr[i]);

        bool error = std::ranges::any_of(errorList, isError);
        if(error) {
            std::cerr << "Matrix::Matrix(Vector<T, Size>...) constructor error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testMatVec(xme::vec2{1, 2}, xme::dvec2{5, 4});
    errors += testMatVec(xme::vec3{3}, xme::vec3{-5}, xme::vec3{9});
    errors += testMatVec(xme::vec4{0}, xme::vec4{2}, xme::vec4{4}, xme::vec4{2});
    errors += testMatVec(xme::Vector<float, 5>{1}, xme::Vector<float, 5>{7});
    errors += testMatVec(xme::Vector<float, 7>{2});
    return errors;
}