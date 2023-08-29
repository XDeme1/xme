#include "common.hpp"

int main() {
    int errors = 0;
    std::vector<float> v{8, 6, 5};
    xme::LinkedList<float> a{v};

    a.reverse();
    for (auto&& l: a) {
        std::cout << l << ' ';
    }
    return errors;
}