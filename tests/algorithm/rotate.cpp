#include <xme/algorithm/rotate.hpp>
void rotateRight() {
    static_assert(xme::rotr(0b101, 1) == 0b10000000'00000000'00000000'00000010);
    static_assert(xme::rotr(0b101, 2) == 0b01000000'00000000'00000000'00000001);
    static_assert(xme::rotr(0b101, 3) == 0b10100000'00000000'00000000'00000000);
    static_assert(xme::rotr(0b101, 32) == 0b00000000'00000000'00000000'00000101);
}

void rotateLeft() {
    static_assert(xme::rotl(0b101, 28) == 0b01010000'00000000'00000000'00000000);
    static_assert(xme::rotl(0b101, 29) == 0b10100000'00000000'00000000'00000000);
    static_assert(xme::rotl(0b101, 30) == 0b01000000'00000000'00000000'00000001);
    static_assert(xme::rotl(0b101, 31) == 0b10000000'00000000'00000000'00000010);
    static_assert(xme::rotl(0b101, 32) == 0b00000000'00000000'00000000'00000101);
}

int main() {
    rotateRight();
    rotateLeft();
    return 0;
}