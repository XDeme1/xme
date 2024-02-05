#include <gtest/gtest.h>
#include <xme/math/glsl_mapping.hpp>
#include <xme/math/math.hpp>

namespace {
using namespace xme::math;

class VectorTests : public testing::Test {
public:
    vec2 v2{5, 3};
    vec3 v3{3, 1, 7};
    vec4 v4{2, 1, 0, 4};
    Vector<float, 5> v5{2, 1, 0, 4, 8};
};

TEST_F(VectorTests, Vector2) {
    EXPECT_TRUE(std::is_trivial_v<decltype(v2)>);

    EXPECT_EQ(v2.x, 5);
    EXPECT_EQ(v2.y, 3);

    {
        vec2 tmp = -v2;
        EXPECT_EQ(tmp[0], -5);
        EXPECT_EQ(tmp[1], -3);

        tmp = v2 + 1;
        EXPECT_EQ(tmp[0], 6);
        EXPECT_EQ(tmp[1], 4);

        tmp = v2 + vec2{1, 2};
        EXPECT_EQ(tmp[0], 6);
        EXPECT_EQ(tmp[1], 5);

        tmp = v2 - 1;
        EXPECT_EQ(tmp[0], 4);
        EXPECT_EQ(tmp[1], 2);

        tmp = v2 - vec2{2, 3};
        EXPECT_EQ(tmp[0], 3);
        EXPECT_EQ(tmp[1], 0);

        tmp = v2 * 2;
        EXPECT_EQ(tmp[0], 10);
        EXPECT_EQ(tmp[1], 6);

        tmp = v2 * vec2{2, 5};
        EXPECT_EQ(tmp[0], 10);
        EXPECT_EQ(tmp[1], 15);

        tmp = v2 / 2;
        EXPECT_FLOAT_EQ(tmp[0], 2.5);
        EXPECT_FLOAT_EQ(tmp[1], 1.5);

        tmp = v2 / vec2{2, 1};
        EXPECT_FLOAT_EQ(tmp[0], 2.5);
        EXPECT_FLOAT_EQ(tmp[1], 3);
    }

    v2 += 2;
    EXPECT_EQ(v2[0], 7);
    EXPECT_EQ(v2[1], 5);

    v2 += vec2{5, 3};
    EXPECT_EQ(v2[0], 12);
    EXPECT_EQ(v2[1], 8);

    v2 -= 2;
    EXPECT_EQ(v2[0], 10);
    EXPECT_EQ(v2[1], 6);

    v2 -= vec2{1, 2};
    EXPECT_EQ(v2[0], 9);
    EXPECT_EQ(v2[1], 4);

    v2 *= 2;
    EXPECT_EQ(v2[0], 18);
    EXPECT_EQ(v2[1], 8);

    v2 *= vec2{0.5, 2};
    EXPECT_EQ(v2[0], 9);
    EXPECT_EQ(v2[1], 16);

    v2 /= 2;
    EXPECT_EQ(v2[0], 4.5);
    EXPECT_EQ(v2[1], 8);

    v2 /= vec2{2, 4};
    EXPECT_EQ(v2[0], 2.25);
    EXPECT_EQ(v2[1], 2);

    v2 = dvec2{2, 7};
    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 7);

    const float len = std::sqrt(53.f);
    EXPECT_FLOAT_EQ(v2.length(), len);

    const auto norm = v2.normalize();
    EXPECT_FLOAT_EQ(norm[0], 2 / len);
    EXPECT_FLOAT_EQ(norm[1], 7 / len);
}

TEST_F(VectorTests, Vector3) {
    EXPECT_TRUE(std::is_trivial_v<decltype(v3)>);

    vec3 expected{};

    EXPECT_EQ(v3.x, 3);
    EXPECT_EQ(v3.y, 1);
    EXPECT_EQ(v3.z, 7);

    {
        vec3 tmp      = -v3;
        vec3 expected = {-3, -1, -7};
        EXPECT_EQ(tmp, expected);

        tmp      = v3 + 1;
        expected = {4, 2, 8};
        EXPECT_EQ(tmp, expected);

        tmp      = v3 + vec3{1, 2, 1};
        expected = {4, 3, 8};
        EXPECT_EQ(tmp, expected);

        tmp      = v3 - 1;
        expected = {2, 0, 6};
        EXPECT_EQ(tmp, expected);

        tmp      = v3 - vec3{2, 3, 1};
        expected = {1, -2, 6};
        EXPECT_EQ(tmp, expected);

        tmp      = v3 * 2;
        expected = {6, 2, 14};
        EXPECT_EQ(tmp, expected);

        tmp      = v3 * vec3{2, 5, 2};
        expected = {6, 5, 14};
        EXPECT_EQ(tmp, expected);

        tmp      = v3 / 2;
        expected = {1.5, 0.5, 3.5};
        EXPECT_EQ(tmp, expected);

        tmp      = v3 / vec3{2, 1, 2};
        expected = {1.5, 1, 3.5};
        EXPECT_EQ(tmp, expected);
    }

    v3 += 2;
    expected = {5, 3, 9};
    EXPECT_EQ(v3, expected);

    v3 += vec3{2, 1, 1};
    expected = {7, 4, 10};
    EXPECT_EQ(v3, expected);

    v3 -= 2;
    expected = {5, 2, 8};
    EXPECT_EQ(v3, expected);

    v3 -= vec3{5, 3, 4};
    expected = {0, -1, 4};
    EXPECT_EQ(v3, expected);

    v3 *= 2;
    expected = {0, -2, 8};
    EXPECT_EQ(v3, expected);

    v3 *= vec3{1, 3, 2};
    expected = {0, -6, 16};
    EXPECT_EQ(v3, expected);

    v3 /= 2;
    expected = {0, -3, 8};
    EXPECT_EQ(v3, expected);

    v3 /= vec3{1, 2, 4};
    expected = {0, -1.5, 2};
    EXPECT_EQ(v3, expected);

    v3       = dvec3{2, 7, 4};
    expected = {2, 7, 4};
    EXPECT_EQ(v3, expected);

    const float len = std::sqrt(69.f);
    EXPECT_FLOAT_EQ(v3.length(), len);

    const auto norm = v3.normalize();
    EXPECT_FLOAT_EQ(norm[0], 2 / len);
    EXPECT_FLOAT_EQ(norm[1], 7 / len);
    EXPECT_FLOAT_EQ(norm[2], 4 / len);
}

TEST_F(VectorTests, Vector4) {
    EXPECT_TRUE(std::is_trivial_v<decltype(v4)>);

    vec4 expected{};

    EXPECT_EQ(v4.x, 2);
    EXPECT_EQ(v4.y, 1);
    EXPECT_EQ(v4.z, 0);
    EXPECT_EQ(v4.w, 4);

    {
        vec4 tmp = -v4;
        vec4 expected{-2, -1, 0, -4};
        EXPECT_EQ(tmp, expected);

        tmp      = v4 + 1;
        expected = {3, 2, 1, 5};
        EXPECT_EQ(tmp, expected);

        tmp      = v4 + vec4{1, 2, 3, 0};
        expected = {3, 3, 3, 4};
        EXPECT_EQ(tmp, expected);

        tmp      = v4 - 1;
        expected = {1, 0, -1, 3};
        EXPECT_EQ(tmp, expected);

        tmp      = v4 - vec4{2, 3, 1, 2};
        expected = {0, -2, -1, 2};
        EXPECT_EQ(tmp, expected);

        tmp      = v4 * 2;
        expected = {4, 2, 0, 8};
        EXPECT_EQ(tmp, expected);

        tmp      = v4 * vec4{2, 5, 2, 1};
        expected = {4, 5, 0, 4};
        EXPECT_EQ(tmp, expected);

        tmp      = v4 / 2;
        expected = {1, 0.5, 0, 2};
        EXPECT_EQ(tmp, expected);

        tmp      = v4 / vec4{2, 1, 2, 1};
        expected = {1, 1, 0, 4};
        EXPECT_EQ(tmp, expected);
    }

    v4 += 2;
    expected = {4, 3, 2, 6};
    EXPECT_EQ(v4, expected);

    v4 += vec4{2, 1, 4, 1};
    expected = {6, 4, 6, 7};
    EXPECT_EQ(v4, expected);

    v4 -= 2;
    expected = {4, 2, 4, 5};
    EXPECT_EQ(v4, expected);

    v4 -= vec4{5, 3, 3, 1};
    expected = {-1, -1, 1, 4};
    EXPECT_EQ(v4, expected);

    v4 *= 2;
    expected = {-2, -2, 2, 8};
    EXPECT_EQ(v4, expected);

    v4 *= vec4{1, 3, 2, 0.5};
    expected = {-2, -6, 4, 4};
    EXPECT_EQ(v4, expected);

    v4 /= 2;
    expected = {-1, -3, 2, 2};
    EXPECT_EQ(v4, expected);

    v4 /= vec4{-2, 3, 1, 2};
    expected = {0.5, -1, 2, 1};
    EXPECT_EQ(v4, expected);

    v4       = dvec4{2, 7, 4, 1};
    expected = {2, 7, 4, 1};
    EXPECT_EQ(v4, expected);

    const float len = std::sqrt(70.f);
    EXPECT_FLOAT_EQ(v4.length(), len);

    const auto norm = v4.normalize();
    EXPECT_FLOAT_EQ(norm[0], 2 / len);
    EXPECT_FLOAT_EQ(norm[1], 7 / len);
    EXPECT_FLOAT_EQ(norm[2], 4 / len);
    EXPECT_FLOAT_EQ(norm[3], 1 / len);
}

TEST_F(VectorTests, Vector5) {
#if !defined(__clang__)  // Clang concepts needs to implement DR1496 for this pass in clang
    EXPECT_TRUE(std::is_trivial_v<decltype(v5)>);
#endif
    using vec5  = Vector<float, 5>;
    using dvec5 = Vector<double, 5>;
    vec5 expected{};

    {
        vec5 tmp = -v5;
        vec5 expected{-2, -1, 0, -4, -8};
        EXPECT_EQ(tmp, expected);

        tmp      = v5 + 1;
        expected = {3, 2, 1, 5, 9};
        EXPECT_EQ(tmp, expected);

        tmp      = v5 + vec5{1, 2, 3, 0, 5};
        expected = {3, 3, 3, 4, 13};
        EXPECT_EQ(tmp, expected);

        tmp      = v5 - 1;
        expected = {1, 0, -1, 3, 7};
        EXPECT_EQ(tmp, expected);

        tmp      = v5 - vec5{2, 3, 1, 2, 3};
        expected = {0, -2, -1, 2, 5};
        EXPECT_EQ(tmp, expected);

        tmp      = v5 * 2;
        expected = {4, 2, 0, 8, 16};
        EXPECT_EQ(tmp, expected);

        tmp      = v5 * vec5{2, 5, 2, 1, 1.5};
        expected = {4, 5, 0, 4, 12};
        EXPECT_EQ(tmp, expected);

        tmp      = v5 / 2;
        expected = {1, 0.5, 0, 2, 4};
        EXPECT_EQ(tmp, expected);

        tmp      = v5 / vec5{2, 1, 2, 1, 4};
        expected = {1, 1, 0, 4, 2};
        EXPECT_EQ(tmp, expected);
    }

    v5 += 2;
    expected = {4, 3, 2, 6, 10};
    EXPECT_EQ(v5, expected);

    v5 += vec5{2, 1, 4, 1, 4};
    expected = {6, 4, 6, 7, 14};
    EXPECT_EQ(v5, expected);

    v5 -= 2;
    expected = {4, 2, 4, 5, 12};
    EXPECT_EQ(v5, expected);

    v5 -= vec5{5, 3, 3, 1, 5};
    expected = {-1, -1, 1, 4, 7};
    EXPECT_EQ(v5, expected);

    v5 *= 2;
    expected = {-2, -2, 2, 8, 14};
    EXPECT_EQ(v5, expected);

    v5 *= vec5{1, 3, 2, 0.5, 0.25};
    expected = {-2, -6, 4, 4, 3.5};
    EXPECT_EQ(v5, expected);

    v5 /= 2;
    expected = {-1, -3, 2, 2, 1.75};
    EXPECT_EQ(v5, expected);

    v5 /= vec5{-2, 3, 1, 2, 0.5};
    expected = {0.5, -1, 2, 1, 3.5};
    EXPECT_EQ(v5, expected);

    v5       = dvec5{2, 7, 4, 1, 3};
    expected = {2, 7, 4, 1, 3};
    EXPECT_EQ(v5, expected);

    const float len = std::sqrt(79.f);
    EXPECT_FLOAT_EQ(v5.length(), len);

    const auto norm = v5.normalize();
    EXPECT_FLOAT_EQ(norm[0], 2 / len);
    EXPECT_FLOAT_EQ(norm[1], 7 / len);
    EXPECT_FLOAT_EQ(norm[2], 4 / len);
    EXPECT_FLOAT_EQ(norm[3], 1 / len);
    EXPECT_FLOAT_EQ(norm[4], 3 / len);
}

TEST_F(VectorTests, Functions) {
    vec3 v1{1, 5, 2};
    vec3 v2{5, 3, 1};
    vec3 expected{};
    EXPECT_EQ(dot(v1, v2), 22);

    expected = {-1, 9, -22};
    EXPECT_EQ(cross(v1, v2), expected);

    expected = vec3{3, 4, 1.5};
    EXPECT_EQ(lerp(v1, v2, 0.5), expected);
    EXPECT_EQ(lerp(v1, v2, 0), v1);
    EXPECT_EQ(lerp(v1, v2, 1), v2);

    expected = vec3{5, 5, 1.5};
    EXPECT_EQ(lerp(v1, v2, vec3{1, 0, 0.5}), expected);

    EXPECT_FLOAT_EQ(distance(v1, v1), 0);
    EXPECT_FLOAT_EQ(distance(v1, v2), std::sqrt(21));

    expected = {1, 5, 2};
    EXPECT_EQ(faceforward(v1, {1, -1, 0}, {0, 1, 0}), expected);
    EXPECT_EQ(faceforward(v1, {1, 1, 0}, {0, 1, 0}), -expected);

    expected = {-1, 1, 1};
    EXPECT_EQ(reflect(vec3{1, 1, 1}, vec3{1, 0, 0}), expected);
}
}  // namespace
