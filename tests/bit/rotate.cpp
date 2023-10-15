#include <xme/bit/rotate.hpp>

void rotateRight() {
    static_assert(xme::rotr(0b101u, 1) == 0b10000000'00000000'00000000'00000010);
    static_assert(xme::rotr(0b101u, 2) == 0b01000000'00000000'00000000'00000001);
    static_assert(xme::rotr(0b101u, 3) == 0b10100000'00000000'00000000'00000000);
    static_assert(xme::rotr(0b101u, 32) == 0b00000000'00000000'00000000'00000101);
    static_assert(xme::rotr(0b100u, -1) == 0b00000000'00000000'00000000'00001000);
    static_assert(xme::rotr(0b100u, -32) == 0b00000000'00000000'00000000'00000100);
    static_assert(xme::rotr(0b100u, -30) == 0b00000000'00000000'00000000'00000001);
}

void rotateLeft() {
    static_assert(xme::rotl(0b101u, 28) == 0b01010000'00000000'00000000'00000000);
    static_assert(xme::rotl(0b101u, 29) == 0b10100000'00000000'00000000'00000000);
    static_assert(xme::rotl(0b101u, 30) == 0b01000000'00000000'00000000'00000001);
    static_assert(xme::rotl(0b101u, 31) == 0b10000000'00000000'00000000'00000010);
    static_assert(xme::rotl(0b101u, 32) == 0b00000000'00000000'00000000'00000101);
    static_assert(xme::rotl(0b100u, -1) == 0b00000000'00000000'00000000'00000010);
    static_assert(xme::rotl(0b100u, -3) == 0b10000000'00000000'00000000'00000000);
    static_assert(xme::rotl(0b100u, -32) == 0b00000000'00000000'00000000'00000100);
}

int main() {
    rotateRight();
    rotateLeft();
    return 0;
}