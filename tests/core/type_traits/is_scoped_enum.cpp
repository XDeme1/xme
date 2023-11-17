#include <xme/core/type_traits/is_scoped_enum.hpp>

enum E1 {

};

enum class E2 {

};

int main() {
    static_assert(!xme::is_scoped_enum<int>);
    static_assert(!xme::is_scoped_enum<E1>);
    static_assert(xme::is_scoped_enum<E2>);
    return 0;
}
