#include <gtest/gtest.h>
#include <xme/math/math.hpp>
#include <xme/math/glsl_mapping.hpp>

namespace {
using namespace xme::math;

class MatrixTests : public testing::Test {};

TEST_F(MatrixTests, Matrix) {
    mat2 mat{
        vec2{1, 6},
        vec2{8, 1}
    };
    mat2 expected{};

    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[0][1], 6);
    EXPECT_EQ(mat[1][0], 8);
    EXPECT_EQ(mat[1][1], 1);

    {
        mat2 tmp{};
        mat2 expected{
            vec2{3,  8},
            vec2{10, 3},
        };
        EXPECT_EQ(mat + 2, expected);

        tmp = {
            vec2{1, 4},
            vec2{7, 4},
        };
        expected = {
            vec2{2,  10},
            vec2{15, 5 },
        };
        EXPECT_EQ(mat + tmp, expected);

        expected = {
            vec2{-1, 4 },
            vec2{6,  -1},
        };
        EXPECT_EQ(mat - 2, expected);

        expected = {
            vec2{0, 2 },
            vec2{1, -3},
        };
        EXPECT_EQ(mat - tmp, expected);

        expected = {
            vec2{2,  12},
            vec2{16, 2 },
        };
        EXPECT_EQ(mat * 2, expected);

        tmp = {
            vec2{2, -1},
            vec2{6, 2 },
        };
        expected = {
            vec2{-6, 11},
            vec2{22, 38},
        };
        EXPECT_EQ(mat * tmp, expected);

        expected = {
            vec2{0.5, 3  },
            vec2{4,   0.5},
        };
        EXPECT_EQ(mat / 2, expected);
    }

    mat += 2;
    expected = {
        vec2{3,  8},
        vec2{10, 3},
    };
    EXPECT_EQ(mat, expected);

    mat += mat2{
        vec2{5, 3},
        vec2{1, 0},
    };
    expected = {
        vec2{8,  11},
        vec2{11, 3 },
    };
    EXPECT_EQ(mat, expected);

    mat -= 3;
    expected = {
        vec2{5, 8},
        vec2{8, 0},
    };
    EXPECT_EQ(mat, expected);

    mat -= mat2{
        vec2{5, 3 },
        vec2{3, -2},
    };
    expected = {
        vec2{0, 5},
        vec2{5, 2},
    };
    EXPECT_EQ(mat, expected);

    mat *= 2;
    expected = {
        vec2{0,  10},
        vec2{10, 4 },
    };
    EXPECT_EQ(mat, expected);

    mat /= 2;
    expected = {
        vec2{0, 5},
        vec2{5, 2},
    };
    EXPECT_EQ(mat, expected);
}

TEST_F(MatrixTests, Matrix4x4) {
    mat4 mat{
        vec4{5, 3, 1, 6},
        vec4{1, 0, 3, 1},
        vec4{7, 6, 0, 3},
        vec4{1, 0, 0, 5},
    };
    mat4 expected{};

    {
        mat4 tmp;
        mat4 expected{};

        expected = {
            vec4{7, 5, 3, 8},
            vec4{3, 2, 5, 3},
            vec4{9, 8, 2, 5},
            vec4{3, 2, 2, 7},
        };
        EXPECT_EQ(mat + 2, expected);

        tmp = {
            vec4{2},
            vec4{1},
            vec4{3},
            vec4{4},
        };
        expected = {
            vec4{7,  5, 3, 8},
            vec4{2,  1, 4, 2},
            vec4{10, 9, 3, 6},
            vec4{5,  4, 4, 9},
        };
        EXPECT_EQ(mat + tmp, expected);

        expected = {
            vec4{3,  1,  -1, 4 },
            vec4{-1, -2, 1,  -1},
            vec4{5,  4,  -2, 1 },
            vec4{-1, -2, -2, 3 },
        };
        EXPECT_EQ(mat - 2, expected);

        tmp = dmat4{
            dvec4{0},
            dvec4{-2},
            dvec4{3},
            dvec4{1},
        };
        expected = {
            vec4{5, 3,  1,  6},
            vec4{3, 2,  5,  3},
            vec4{4, 3,  -3, 0},
            vec4{0, -1, -1, 4},
        };
        EXPECT_EQ(mat - tmp, expected);

        expected = {
            vec4{10, 6,  2, 12},
            vec4{2,  0,  6, 2 },
            vec4{14, 12, 0, 6 },
            vec4{2,  0,  0, 10},
        };
        EXPECT_EQ(mat * 2, expected);

        expected = {
            vec4{2.5, 1.5, 0.5, 3  },
            vec4{0.5, 0,   1.5, 0.5},
            vec4{3.5, 3,   0,   1.5},
            vec4{0.5, 0,   0,   2.5},
        };
        EXPECT_EQ(mat / 2, expected);
    }

    mat += 2;
    expected = {
        vec4{7, 5, 3, 8},
        vec4{3, 2, 5, 3},
        vec4{9, 8, 2, 5},
        vec4{3, 2, 2, 7},
    };
    EXPECT_EQ(mat, expected);

    mat += mat4{
        vec4{2},
        vec4{1},
        vec4{0},
        vec4{-2},
    };
    expected = {
        vec4{9, 7, 5, 10},
        vec4{4, 3, 6, 4 },
        vec4{9, 8, 2, 5 },
        vec4{1, 0, 0, 5 },
    };
    EXPECT_EQ(mat, expected);

    mat -= 2;
    expected = {
        vec4{7,  5,  3,  8},
        vec4{2,  1,  4,  2},
        vec4{7,  6,  0,  3},
        vec4{-1, -2, -2, 3},
    };
    EXPECT_EQ(mat, expected);

    mat -= mat4{
        vec4{0},
        vec4{-2},
        vec4{0},
        vec4{1},
    };
    expected = {
        vec4{7,  5,  3,  8},
        vec4{4,  3,  6,  4},
        vec4{7,  6,  0,  3},
        vec4{-2, -3, -3, 2},
    };
    EXPECT_EQ(mat, expected);

    mat *= 2;
    expected = {
        vec4{14, 10, 6,  16},
        vec4{8,  6,  12, 8 },
        vec4{14, 12, 0,  6 },
        vec4{-4, -6, -6, 4 },
    };
    EXPECT_EQ(mat, expected);

    mat /= 2;
    expected = {
        vec4{7,  5,  3,  8},
        vec4{4,  3,  6,  4},
        vec4{7,  6,  0,  3},
        vec4{-2, -3, -3, 2},
    };
    EXPECT_EQ(mat, expected);
}

TEST_F(MatrixTests, Functions) {
    mat2 expected2{
        vec2{3, 4},
        vec2{1, 2}
    };
    EXPECT_EQ(determinant(expected2), 2);

    mat3 expected3{
        vec3{5, 3, 1},
        vec3{7, 3, 4},
        vec3{9, 7, 8}
    };
    EXPECT_EQ(determinant(expected3), -58);

    mat4 expected4{
        vec4{5, 3,  1,  2},
        vec4{6, 7,  3,  4},
        vec4{9, 7,  -3, 8},
        vec4{9, -8, -3, 1}
    };
    EXPECT_EQ(determinant(expected4), -498);

    {
        mat2x3 expected{
            vec3{5, 25, 10},
            vec3{3, 15, 6 },
        };
        EXPECT_EQ(outer_product(vec3{1, 5, 2}, vec2{5, 3}), expected);
    }
    {
        mat2 mat{
            vec2{1, 5},
            vec2{5, 3}
        };
        mat2 expected{
            vec2{1,  25},
            vec2{25, 9 }
        };
        EXPECT_EQ(hadamard_product(mat, mat), expected);
    }
}

TEST_F(MatrixTests, Transformations) {
    mat4 mat{2};
    mat4 expected{
        vec4{2, 0,  0, 0},
        vec4{0, 2,  0, 0},
        vec4{0, 0,  2, 0},
        vec4{2, 10, 6, 2},
    };
    EXPECT_EQ(translate(mat, vec3{1, 5, 3}), expected);

    expected = {
        vec4{4, 0, 0, 0},
        vec4{0, 2, 0, 0},
        vec4{0, 0, 6, 0},
        vec4{0, 0, 0, 2},
    };
    EXPECT_EQ(scale(mat, vec3{2, 1, 3}), expected);

    auto result = rotate(mat4{}, xme::math::pi_v<float> / 2, vec3{0, 1, 0});
    EXPECT_NEAR(result[0][0], 0, std::numeric_limits<float>::epsilon());
    EXPECT_FLOAT_EQ(result[0][1], 0);
    EXPECT_FLOAT_EQ(result[0][2], -1);
    EXPECT_FLOAT_EQ(result[0][3], 0);

    EXPECT_FLOAT_EQ(result[1][0], 0);
    EXPECT_FLOAT_EQ(result[1][1], 1);
    EXPECT_FLOAT_EQ(result[1][2], 0);
    EXPECT_FLOAT_EQ(result[1][3], 0);

    EXPECT_FLOAT_EQ(result[2][0], 1);
    EXPECT_FLOAT_EQ(result[2][1], 0);
    EXPECT_NEAR(result[2][2], 0, std::numeric_limits<float>::epsilon());
    EXPECT_FLOAT_EQ(result[2][3], 0);

    EXPECT_FLOAT_EQ(result[3][0], 0);
    EXPECT_FLOAT_EQ(result[3][1], 0);
    EXPECT_FLOAT_EQ(result[3][2], 0);
    EXPECT_FLOAT_EQ(result[3][3], 1);
}
}  // namespace
