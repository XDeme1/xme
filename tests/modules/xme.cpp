import xme;
#include <iostream>

int main() {
    xme::vec3 v{1, 5, 3};
    std::cout << v[0] << v[1] << v[2];
    xme::Array<int> arr;
    arr.emplaceBack(5);
    return 0;
}