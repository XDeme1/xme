#include <xme/bit/popcount.hpp>

int main() {
    static_assert(xme::popcount(std::uint8_t(0b1100'1011)) == 5);
    static_assert(xme::popcount(std::uint16_t(0b1000'1001'1011'0111)) == 9);
    static_assert(xme::popcount(std::uint64_t(0b1000'1001'1011'0111'0011'0111'1010'1111)) == 20);
    return 0;
}