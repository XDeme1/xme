#include <xme/math/math.hpp>
#include <algorithm>
#include <iostream>

bool isError(bool b) { return b == false; }

template<std::size_t Size>
int testSquareMatrix() {
    int errors = 0;
    {
        xme::Matrix<float, Size, Size> m;

        std::array<bool, Size*Size> results{};
        for (auto i = 0; i < Size; ++i) {
            for (auto j = 0; j < Size; ++j) {
                if(i == j)
                    results[i*Size+j] = m[j][i] == 1;
                else
                    results[i*Size+j] = m[j][i] == 0;
            }
        }

        auto error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "matrix error\n";
            ++errors;
        }
    }

    {
        xme::Matrix<float, Size, Size> m{5};

        std::array<bool, Size*Size> results{};
        for (auto i = 0; i < Size; ++i) {
            for (auto j = 0; j < Size; ++j) {
                if(i == j)
                    results[i*Size+j] = m[j][i] == 5;
                else
                    results[i*Size+j] = m[j][i] == 0;
            }
        }

        auto error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "matrix error\n";
            ++errors;
        }
    }
    return errors;
}

int testMatrix2x3() {
    int errors = 0;
    {
        xme::Matrix<float, 2, 3> m;
        std::array results = std::to_array({
            m[0] == xme::vec3{1, 0, 0},
            m[1] == xme::vec3(0, 1, 0),
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat2x3 constructor error\n";
            ++errors;
        } 
    }

    {
        xme::Matrix<float, 2, 3> m{xme::vec3{1, 2, 3}, xme::vec3{9, 8, 7}};
        std::array results = std::to_array({
            m[0] == xme::vec3{1, 2, 3},
            m[1] == xme::vec3{9, 8, 7},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat2x3 constructor error\n";
            ++errors;
        }
    }
    return errors;
}

int testMatrix2x4() {
    int errors = 0;
    {
        xme::Matrix<float, 2, 4> m;
        std::array results = std::to_array({
            m[0] == xme::vec4{1, 0, 0, 0},
            m[1] == xme::vec4{0, 1, 0, 0},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat2x4 constructor error\n";
            ++errors;
        } 
    }

    {
        xme::Matrix<float, 2, 4> m{xme::vec4(1, 2, 3, 4), xme::vec4(5, 4, 3, 2)};
        std::array results = std::to_array({
            m[0] == xme::vec4{1, 2, 3, 4},
            m[1] == xme::vec4{5, 4, 3, 2},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat2x4 constructor error\n";
            ++errors;
        } 
    }
    return errors;
}

int testMatrix3x2() {
    int errors = 0;
    {
        xme::Matrix<float, 3, 2> m;
        std::array results = std::to_array({
            m[0] == xme::vec2{1, 0},
            m[1] == xme::vec2{0, 1},
            m[2] == xme::vec2{0},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat3x2 constructor error\n";
            ++errors;
        } 
    }

    {
        xme::Matrix<float, 3, 2> m{xme::vec2(1, 2), xme::vec2(5, 1), xme::vec2(9, 1)};
        std::array results = std::to_array({
            m[0] == xme::vec2{1, 2},
            m[1] == xme::vec2{5, 1},
            m[2] == xme::vec2{9, 1},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat3x2 constructor error\n";
            ++errors;
        } 
    }
    return errors;
}

int testMatrix4x2() {
    int errors = 0;
    {
        xme::Matrix<float, 4, 2> m;
        std::array results = std::to_array({
            m[0] == xme::vec2{1, 0},
            m[1] == xme::vec2{0, 1},
            m[2] == xme::vec2{0},
            m[3] == xme::vec2{0},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat4x2 constructor error\n";
            ++errors;
        } 
    }

    {
        xme::Matrix<float, 4, 2> m{xme::vec2(2), xme::vec2(5), xme::vec2(1), xme::vec2(9)};
        std::array results = std::to_array({
            m[0] == xme::vec2{2},
            m[1] == xme::vec2{5},
            m[2] == xme::vec2{1},
            m[3] == xme::vec2{9},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat4x2 constructor error\n";
            ++errors;
        } 
    }
    return errors;
}

int testMatrix3x4() {
    int errors = 0;
    {
        xme::Matrix<float, 3, 4> m;
        std::array results = std::to_array({
            m[0] == xme::vec4{1, 0, 0, 0},
            m[1] == xme::vec4{0, 1, 0, 0},
            m[2] == xme::vec4{0, 0, 1, 0},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat3x4 constructor error\n";
            ++errors;
        } 
    }

    {
        xme::Matrix<float, 3, 4> m{xme::vec4(2), xme::vec4(9), xme::vec4(-3)};
        std::array results = std::to_array({
            m[0] == xme::vec4{2},
            m[1] == xme::vec4{9},
            m[2] == xme::vec4{-3},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat3x4 constructor error\n";
            ++errors;
        } 
    }
    return errors = 0;
}

int testMatrix4x3() {
    int errors = 0;
    {
        xme::Matrix<float, 4, 3> m;
        std::array results = std::to_array({
            m[0] == xme::vec3{1, 0, 0},
            m[1] == xme::vec3{0, 1, 0},
            m[2] == xme::vec3{0, 0, 1},
            m[3] == xme::vec3{0},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat4x3 constructor error\n";
            ++errors;
        } 
    }

    {
        xme::Matrix<float, 4, 3> m{xme::vec3(0), xme::vec3(2), xme::vec3(-5), xme::vec3(-1)};
        auto results = std::to_array({
            m[0] == xme::vec3{0},
            m[1] == xme::vec3{2},
            m[2] == xme::vec3{-5},
            m[3] == xme::vec3{-1},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "mat4x3 constructor error\n";
            ++errors;
        } 
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testSquareMatrix<2>(); 
    errors += testSquareMatrix<3>(); 
    errors += testSquareMatrix<4>(); 
    errors += testSquareMatrix<5>(); 
    errors += testMatrix2x3();
    errors += testMatrix2x4();
    errors += testMatrix3x2();
    errors += testMatrix4x2();
    errors += testMatrix3x4();
    errors += testMatrix4x3();
    return errors;
}