#include <iostream>
#include <xme/iterators/contiguous_iterator.hpp>
#include <xme/iterators/reverse_iterator.hpp>

template<typename T>
using iterator = xme::ContiguousIterator<T>;

static_assert(std::contiguous_iterator<iterator<float>>);

int testIncrement() {
    int errors = 0;
    int arr[3]{4, 1, -2};
    iterator<int> begin{arr};
    iterator<const int> end{arr + 3};
    {
        bool error = (begin + 3) != end || (3 + begin) != end;
        iterator<int> it1{begin};
        error |= it1++ != begin;
        error |= ++it1 != begin + 2;
        if (error) {
            std::cerr << "xme::ContiguousIterator increment 1 error\n";
            ++errors;
        }
    }
    {
        iterator<const int> it1{begin};
        it1 += 2;
        bool error = it1 != begin+2;
        it1 += -2;
        error |= it1 != begin;
        if(error) {
            std::cerr << "xme::ContiguousIterator increment 2 error\n";
            ++errors;
        }
    }
    return errors;
}

int testDecrement() {
    int errors = 0;
    int arr[3]{4, 1, -2};
    iterator<int> begin{arr};
    iterator<const int> end{arr + 3};
    {
        bool error = (end - 3) != begin || (end - begin) != 3;
        iterator<const int> it1{end};
        error |= it1-- != end;
        error |= --it1 != end - 2;
        if (error) {
            std::cerr << "xme::ContiguousIterator decrement 1 error";
            ++errors;
        }
    }
    {
        iterator<const int> it1{end};
        it1 -= 2;
        bool error = it1 != begin+1;
        it1 -= -2;
        error |= it1 != end;
        if(error) {
            std::cerr << "xme::ContiguousIterator decrement 2 error\n";
            ++errors;
        }
    }
    return errors;
}

int testAccess() {
    int errors = 0;
    int arr[3]{4, 1, -2};
    iterator<int> begin{arr};
    iterator<const int> end{arr + 3};
    {
        bool error = begin[0] != 4 || begin[1] != 1 || begin[2] != -2;
        error |= end[-1] != -2 || end[-2] != 1 || end[-3] != 4;
        error |= *begin != 4 || *(begin + 1) != 1 || *(begin + 2) != -2;
        error |= *(begin.operator->()) != 4 || *(begin.operator->() + 1) != 1;
        error |= *(begin.operator->() + 2) != -2;
        if (error) {
            std::cerr << "xme::ContiguousIterator access error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testIncrement();
    errors += testDecrement();
    errors += testAccess();
    return errors;
}