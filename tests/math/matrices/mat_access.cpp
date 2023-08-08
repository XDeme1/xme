#include "common.hpp"

int testAccess() {
    int errors = 0;
    xme::Matrix<float, 2, 3> m{xme::vec3(2, 1, 3), xme::vec3(8, 7, 6)};
    static_assert(std::is_same_v<decltype(m.row(0)), xme::vec2>);
    static_assert(std::is_same_v<decltype(m.column(0)), xme::vec3>);
    {
        std::array results = std::to_array({
            m.row(0) == xme::vec2(2, 8),
            m.row(1) == xme::vec2(1, 7),
            m.row(2) == xme::vec2(3, 6),
        });

        bool error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Matrix::row(std::size_t) Error\n";
            ++errors;
        }
    }

    {
        std::array results = std::to_array({
            m.column(0) == xme::vec3(2, 1, 3),
            m.column(1) == xme::vec3(8, 7, 6),
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Matrix::column(std::size_t) Error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testAccess();
    return errors;
}