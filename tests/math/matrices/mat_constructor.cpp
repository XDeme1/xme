#include "common.hpp"

template<std::size_t Size, typename...Args>
constexpr int testMatrix(const xme::Vector<Args, Size>&...args) {
    int errors = 0;
    
    constexpr std::size_t cols = sizeof...(Args);
    constexpr std::size_t rows = Size;

    static_assert(std::is_same_v<decltype(xme::Matrix{args...}), xme::Matrix<std::common_type_t<Args...>, cols, rows>>);
    {
        xme::Matrix m{args...};
        std::array arr{args...};
        
        std::vector<short> errorList;
        for(std::size_t i = 0; i < cols; ++i)  
            errorList.emplace_back(m[i] == arr[i]);
            
        bool error = std::ranges::any_of(errorList, isError);
        if(error) {
            std::cerr << "Matrix<T, " << cols << ", " << rows << ">::Matrix(Vector<Args, Size>...) error\n";
            ++errors;
        }
    }
    return errors;
};

int main() {
    int errors = 0;
    errors += testMatrix(xme::vec3{2, 1, 5}, xme::vec3{5}); // Matrix<T, 2, 3>
    errors += testMatrix(xme::vec4{2}, xme::vec4{8}); // Matrix<T, 2, 4>
    errors += testMatrix(xme::vec2{5, 3}, xme::vec2{6}, xme::vec2{1}); // Matrix<T, 3, 2>
    errors += testMatrix(xme::vec4{5}, xme::vec4{6}, xme::vec4{1}); // Matrix<T, 3, 4>
    errors += testMatrix(xme::vec2{5}, xme::vec2{6}, xme::vec2{1}, xme::vec2{-6}); // Matrix<T, 4, 2>
    errors += testMatrix(xme::vec3{5}, xme::vec3{6}, xme::vec3{1}, xme::vec3{-8}); // Matrix<T, 4, 3>
    return errors;
}