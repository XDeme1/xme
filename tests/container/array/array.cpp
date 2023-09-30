#include "../common.hpp"
#include <xme/container/array.hpp>

int testAccess() {
    int errors = 0;
    {
        xme::Array<float> arr{5, 3, 2.5};
        bool error = arr[0] != 5 || arr[1] != 3 || arr[2] != 2.5f;
        if(error) {
            std::cerr << "xme::Array::operator[] error\n";
            ++errors;
        }
    }
    {
        xme::Array<float> arr{5, 0.5};
        auto b = arr.cbegin();
        bool error = (*(b++) != 5);
        error |= (*(b++) != 0.5f);
        if(error) {
            std::cerr << "xme::Array iterator error\n";
            ++errors;
        }
    }
    return errors;
}

int testInsertion() {
    int errors = 0;
    {
        xme::Array<float> arr(2, 0.5);
        arr.pushBacK(0.25);
        bool error = arr[0] != 0.5f || arr[1] != 0.5f || arr[2] != 0.25f;
        error |= arr.capacity() != 4 || arr.size() != 3;
        if(error) {
            std::cerr << "xme::Array::pushBack error\n";
            ++errors;
        }
    }
    {
        xme::Array<float> arr;
        arr.emplaceBack(0.125);
        bool error = arr[0] != 0.125f;
        error |= arr.capacity() != 1 || arr.size() != 1;
        if(error) {
            std::cerr << "xme::Array::emplaceBack error\n";
            ++errors;
        }
    }
    return errors;
}

int testDelete() {
    int errors = 0;
    {
        xme::Array<float> arr{0.5, 0.25};
        arr.popBack();
        bool error = arr[0] != 0.5f || arr.size() != 1 || arr.capacity() != 2;
        arr.popBack();
        error |= arr.size() != 0 || arr.capacity() != 2;
        if(error) {
            std::cerr << "xme::Array::popBack error\n";
            ++errors;
        }
    }
    return errors;
}

int testResize() {
    int errors = 0;
    {
        xme::Array<float> arr{1, 2.5};
        bool error = arr.size() != 2 || arr.capacity() != 2;
        arr.reserve(3);
        error |= arr.size() != 2 || arr.capacity() != 3;
        arr.reserve(1);
        error |= arr.size() != 2 || arr.capacity() != 3 || arr[0] != 1;

        if(error) {
            std::cerr << "xme::Array::reserve error\n";
            ++errors;
        }
    }
    {
        xme::Array<float> arr{1, 2.5};
        bool error = arr.size() != 2 || arr.capacity() != 2;
        arr.resize(3);
        error |= arr.size() != 2 || arr.capacity() != 3;
        arr.resize(1);
        error |= arr.size() != 1 || arr.capacity() != 1 || arr[0] != 1;

        if(error) {
            std::cerr << "xme::Array::resize error\n";
            ++errors;
        }
    }

    {
        xme::Array<float> arr{5, 3};
        arr.clear();
        bool error = arr.size() != 0 || arr.capacity() != 2;
        if(error) {
            std::cerr << "xme::Array::clear error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testAccess();
    errors += testInsertion();
    errors += testDelete();
    errors += testResize();
    std::vector<int> a;
    a.insert(a.begin(), 2);
    return errors;
}