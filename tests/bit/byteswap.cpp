#include <xme/bit/byteswap.hpp>
#include <cstdint>

int main() {
    static_assert(xme::byteswap(short(5)) == short(0x05'00));
    static_assert(xme::byteswap(short(-2)) == short(0xfe'ff));

    static_assert(xme::byteswap(5) == int(0x05'00'00'00));
    static_assert(xme::byteswap(-2) == int(0xfe'ff'ff'ff));

    static_assert(xme::byteswap(std::int64_t(5)) == std::int64_t(0x05'00'00'00'00'00'00'00));
    static_assert(xme::byteswap(std::int64_t(-2)) == std::int64_t(0xfe'ff'ff'ff'ff'ff'ff'ff));
    return 0;
}