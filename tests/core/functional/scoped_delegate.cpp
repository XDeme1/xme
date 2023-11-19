#include <xme/core/functional/scoped_delegate.hpp>
#include <xme/core/functional/bind.hpp>
#include <cassert>

constinit int scope_count{0};
xme::ScopedDelegate global_scope{[]() mutable { assert(scope_count == 0); }};

void test(int, int) {
    scope_count -= 1;
}

struct T {
    T() {
        scope_count += 1;
        xme::ScopedDelegate a{[this]() {
            scope_count -= 1;
            b = 2;
        }};
    }
    ~T() { assert(b == 2); }

    int b = 0;
};

int main() {
    T c;

    scope_count += 1;
    xme::ScopedDelegate s1{xme::bind_front(&test, 1, 1)};
    return 0;
}
