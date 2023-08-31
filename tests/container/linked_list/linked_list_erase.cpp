#include "../common.hpp"

int main() {
    int errors = 0;
    std::vector<float> v{7, 3, 1, 8};
    {
        xme::LinkedList<float> a{v};
        a.eraseAfter(a.begin());
        std::vector<short> results;
        
        auto begin = a.begin();
        results.emplace_back(*(begin++) == 7);
        results.emplace_back(*(begin++) == 1);
        results.emplace_back(*(begin++) == 8);

        a.eraseAfter(a.cbeforeBegin(), a.cend());
        results.emplace_back(a.isEmpty());
        
        bool error = std::ranges::any_of(results, isError);
        if(error) {
            ++errors;
            std::cerr << "xme::LinkedList::eraseAfter Error";
        }
    }
    return errors;
}