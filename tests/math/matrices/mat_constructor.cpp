#include "common.hpp"

namespace math = xme::math;
template<std::size_t Size, typename...Args>
constexpr int test_matrix(const math::Vector<Args, Size>&...args) {
    int errors = 0;
    
    constexpr std::size_t cols = sizeof...(Args);
    constexpr std::size_t rows = Size;

    static_assert(std::is_same_v<decltype(math::Matrix{args...}), math::Matrix<std::common_type_t<Args...>, cols, rows>>);
    {
        math::Matrix m{args...};
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
    errors += test_matrix(math::vec3{2, 1, 5}, math::vec3{5}); // Matrix<T, 2, 3>
    errors += test_matrix(math::vec4{2}, math::vec4{8}); // Matrix<T, 2, 4>
    errors += test_matrix(math::vec2{5, 3}, math::vec2{6}, math::vec2{1}); // Matrix<T, 3, 2>
    errors += test_matrix(math::vec4{5}, math::vec4{6}, math::vec4{1}); // Matrix<T, 3, 4>
    errors += test_matrix(math::vec2{5}, math::vec2{6}, math::vec2{1}, math::vec2{-6}); // Matrix<T, 4, 2>
    errors += test_matrix(math::vec3{5}, math::vec3{6}, math::vec3{1}, math::vec3{-8}); // Matrix<T, 4, 3>
    return errors;
}