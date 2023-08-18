#include <immintrin.h>
#include <iostream>
#include <xme/platform/architecture.hpp>
#include <xme/container/aligned_data.hpp>
int main() {
    __m128 vec1 = _mm_set_ps(4.0, 3, 2, 1);
}