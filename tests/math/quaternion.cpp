#include <iostream>
#include <xme/math/quaternion.hpp>

namespace math = xme::math;

int main() {
  int errors = 0;
  {
    math::Quaternion<float> q1{5, 3, 1, 6};
    math::Quaternion<float> q2{-3, 1, 2, 1};
    auto result = q1 + q2;
    bool error =
        result.w != 2 || result.x != 4 || result.y != 3 || result.z != 7;
    if (error) {
      std::cerr << "xme::math::Quaternion addition error\n";
      ++errors;
    }
  }
  {
    math::Quaternion<float> q1{1, 2, -1, -1};
    math::Quaternion<float> q2{-1, -2, 3, -5};
    auto result = q1 * q2;
    bool error =
        result.w != 1 || result.x != 4 || result.y != 16 || result.z != 0;
    if (error) {
      std::cerr << "xme::math::Quaternion multiplication error\n";
      ++errors;
    }
  }
  struct Foo {
    int a;
    int b;
  };

  return errors;
}
