#include <xme/container/heap.hpp>
#include <iostream>

int testPushPop() {
    int errors = 0;
    {
        xme::Heap<int> a; // Max heap
        for(std::size_t i = 0; i < 10; ++i)
            a.push(i);
        auto b = a.begin();
        bool error = a.size() != 10 || *(b++) != 9 || *(b++) != 8;
        error |= *(b++) != 5 || *(b++) != 6 || *(b++) != 7;
        error |= *(b++) != 1 || *(b++) != 4 || *(b++) != 0;
        error |= *(b++) != 3 || *(b++) != 2 || b != a.end();
        if(error) {
            std::cerr << "xme::Heap push error\n";
            ++errors;
        }
    }
    {
        xme::Heap<int> a; // Max heap
        for(std::size_t i = 0; i < 10; ++i)
            a.push(i);
        a.pop();
        auto b = a.begin();

        bool error = a.size() != 9 || *(b++) != 8 || *(b++) != 7;
        error |= *(b++) != 5 || *(b++) != 6 || *(b++) != 2;
        error |= *(b++) != 1 || *(b++) != 4 || *(b++) != 0;
        error |= *(b++) != 3 || b != a.end();
        if(error) {
            std::cerr << "xme::Heap pop error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testPushPop();
    return errors;
}