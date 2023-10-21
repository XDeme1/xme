#include "common.hpp"

namespace math = xme::math;

template<typename...Args, std::size_t Size>
int test_mat_vec(const math::Vector<Args, Size>&...v) {
    int errors = 0;
    constexpr std::size_t rows = Size;
    constexpr std::size_t cols = sizeof...(Args);
    using type = std::common_type_t<Args...>;

    static_assert(std::is_same_v<decltype(math::Matrix{v...}), math::Matrix<type, cols, rows>>);
    {
        math::Matrix m{v...};
        std::array<math::Vector<type, rows>, cols> arr{v...};

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
    errors += test_mat_vec(math::vec2{1, 2}, math::dvec2{5, 4});
    errors += test_mat_vec(math::vec3{3}, math::vec3{-5}, math::vec3{9});
    errors += test_mat_vec(math::vec4{0}, math::vec4{2}, math::vec4{4}, math::vec4{2});
    errors += test_mat_vec(math::Vector<float, 5>{1}, math::Vector<float, 5>{7});
    errors += test_mat_vec(math::Vector<float, 7>{2});
    return errors;
}