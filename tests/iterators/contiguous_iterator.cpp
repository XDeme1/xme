#include <xme/iterators/contiguous_iterator.hpp>

int main() {
    static_assert(std::contiguous_iterator<xme::ContiguousIterator<float>>);
}