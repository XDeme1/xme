#include <xme/algorithm/min_max.hpp>
#include <iostream>

int main() {
    int errors = 0;
    {
        int a = 10;
        int b = 11;
        bool error = xme::min(a, b) != 10 || xme::min(a, b, std::less{}) != 10;
        error |= xme::min(a, b, std::greater{}) != 11;
        if(error) {
            std::cerr << "xme::min error\n";
            ++errors;
        }
    }
    {
        int a = 10;
        int b = 11;
        bool error = xme::max(a, b) != 11 || xme::max(a, b, std::less{}) != 11;
        error |= xme::max(a, b, std::greater{}) != 10;
        if(error) {
            std::cerr << "xme::max error\n";
            ++errors;
        }
    }
    {
        int a = 10;
        int b = 11;
        auto p1 = xme::minmax(a, b);
        auto p2 = xme::minmax(a, b, std::less{});
        auto p3 = xme::minmax(a, b, std::greater{});
        bool error = p1.first != 10 || p1.second != 11;
        error |= p2.first != 10 || p2.second != 11;
        error |= p3.first != 11 || p3.second != 10;
        if(error) {
            std::cerr << "xme::minmax error\n";
            ++errors;
        }
    }
    return errors;
}