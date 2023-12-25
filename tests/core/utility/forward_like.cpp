#include <xme/core/utility/forward_like.hpp>
#include <xme/core/concepts/same_as.hpp>

int main() {
    int a{1};
    int& b  = a;
    int&& c = 2;
    static_assert(requires {
        { xme::forward_like<int&&>(1) } -> xme::same_as_c<int&&>;
        { xme::forward_like<int&>(b) } -> xme::same_as_c<int&>;
        { xme::forward_like<int&&>(b) } -> xme::same_as_c<int&&>;
        { xme::forward_like<const int&>(c) } -> xme::same_as_c<const int&>;
    });
}
