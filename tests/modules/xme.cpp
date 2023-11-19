import xme;
#include <iostream>

int main() {
    xme::math::vec3 v{1, 5, 3};
    std::cout << v[0] << v[1] << v[2];
    xme::Array<int> arr;
    arr.emplace_back(5);
    return 0;
}
