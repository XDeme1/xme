#include <xme/utility/forward_like.hpp>

int main() {
    int a{1};
    static_assert(std::is_same_v<decltype(xme::forwardLike<int&>(a)), int&>);
    static_assert(std::is_same_v<decltype(xme::forwardLike<int&&>(a)), int&&>);
    static_assert(std::is_same_v<decltype(xme::forwardLike<const int&>(a)), const int&>);
    static_assert(std::is_same_v<decltype(xme::forwardLike<const int&&>(a)), const int&&>);
}