#include <xme/core/utility/forward_like.hpp>

int main() {
    int a{1};
    int& b  = a;
    int&& c = 2;
    static_assert(requires {
        { xme::forward_like<int&&>(1) } -> std::same_as<int&&>;
        { xme::forward_like<int&>(b) } -> std::same_as<int&>;
        { xme::forward_like<int&&>(b) } -> std::same_as<int&&>;
        { xme::forward_like<const int&>(c) } -> std::same_as<const int&>;
    });
}
