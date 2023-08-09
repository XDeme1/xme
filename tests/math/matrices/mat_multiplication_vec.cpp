#include "common.hpp"

int testMatrixVector() {
    int errors = 0;
    static_assert(std::is_same_v<decltype(xme::mat2{}*xme::vec2{}), xme::vec2>);
    static_assert(std::is_same_v<decltype(xme::mat3{}*xme::vec3{}), xme::vec3>);
    static_assert(std::is_same_v<decltype(xme::mat4{}*xme::vec4{}), xme::vec4>);
    {
        xme::mat4 m{2};
        xme::vec4 v{5, 6, 7, 1};

        bool error = (m * v) != xme::vec4{10, 12, 14, 2};
        if(error) {
            std::cerr << "mat4 * vec4 multiplication Error\n";
            ++errors;
        }
    }

    static_assert(std::is_same_v<decltype(xme::Matrix<float, 4, 1>{}*xme::vec4{}), xme::Vector<float, 1>>);
    static_assert(std::is_same_v<decltype(xme::Matrix<float, 3, 2>{}*xme::vec3{}), xme::vec2>);
    {
        xme::Matrix<float, 4, 2> m{xme::vec2{1, 2}, xme::vec2{9, 9}, xme::vec2{1}, xme::vec2{5}};
        xme::vec4 v{2};

        bool error = (m * v) != xme::vec2{32, 34};
        if(error) {
            std::cerr << "mat4x2 * vec4 multiplication error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testMatrixVector();
    return errors;
}