#include "../common.hpp"

struct Test {
    Test() { std::cerr << "Ctr "; }
};

int main() {
    xme::SPSCQueue<int, 4> a;
}