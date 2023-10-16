#include <xme/utility/forward_like.hpp>

int main() {
    int a{1};
    static_assert(std::is_same_v<decltype(xme::forward_like<int&>(a)), int&>);
    static_assert(std::is_same_v<decltype(xme::forward_like<int&&>(a)), int&&>);
    static_assert(std::is_same_v<decltype(xme::forward_like<const int&>(a)), const int&>);
    static_assert(std::is_same_v<decltype(xme::forward_like<const int&&>(a)), const int&&>);
}