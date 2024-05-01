#include <array>
#include <iostream>
#include <list>
#include <vector>
#include <xme/container/array.hpp>

int test_access() {
    int errors = 0;
    {
        xme::Array<float> arr{5.f, 3.f, 2.5f};
        bool error = arr[0] != 5 || arr[1] != 3 || arr[2] != 2.5f;
        if(error) {
            std::cerr << "xme::Array::operator[] error\n";
            ++errors;
        }
    }
    {
        std::array<float, 2> a{5, 0.5};
        xme::Array<float> arr{a.begin(), a.end()};
        auto b     = ranges::cbegin(arr);
        bool error = (*(b++) != 5);
        error |= (*(b++) != 0.5f);
        error |= b != ranges::cend(arr);
        if(error) {
            std::cerr << "xme::Array iterator error\n";
            ++errors;
        }
    }
    {
        const xme::Array<float> a{5, 0.5};
        xme::Array<float> arr{a};
        auto b     = ranges::rbegin(arr);
        bool error = (*(b++) != 0.5);
        error |= (*(b++) != 5);
        error |= b != ranges::rend(arr);
        if(error) {
            std::cerr << "xme::Array reverse_iterator error\n";
            ++errors;
        }
    }
    {
        std::array<float, 2> a{0.25, 0.125};
        xme::Array<float> arr{a};
        bool error = arr.front() != 0.25 || arr.back() != 0.125;
        if(error) {
            std::cerr << "xme::Array::front and xme::Array::back error\n";
            ++errors;
        }
    }
    return errors;
}

int test_move_copy() {
    int errors = 0;
    {
        xme::Array<int> arr1{5, 3};
        arr1.reserve(5);
        xme::Array<int> arr2{arr1};

        bool error = arr2[0] != arr1[0] || arr2[1] != arr1[1];
        error |= arr2.capacity() != 2 || arr2.size() != 2;
        error |= arr1.capacity() != 5 || arr1.size() != 2;
        if(error) {
            std::cerr << "xme::Array *copy* Constructor error\n";
            ++errors;
        }
    }
    {
        const xme::Array<int> arr1{5, 3};
        xme::Array<int> arr2{arr1};

        bool error = arr2[0] != arr1[0] || arr2[1] != arr1[1];
        error |= arr2.capacity() != 2 || arr2.size() != 2;
        if(error) {
            std::cerr << "xme::Array copy Constructor error\n";
            ++errors;
        }
    }
    {
        xme::Array<int> arr1{3, 1};
        arr1.reserve(3);
        xme::Array<int> arr2{std::move(arr1)};
        bool error = !arr1.empty() || arr2.capacity() != 3 || arr2.size() != 2;
        error |= arr2[0] != 3 || arr2[1] != 1;
        if(error) {
            std::cerr << "xme::Array move constructor error\n";
            ++errors;
        }
    }
    {
        xme::Array<int> arr1{8, 1};
        arr1.reserve(3);
        xme::Array<int> arr2{5};
        arr2       = arr1;
        bool error = arr1.size() != 2 || arr1.capacity() != 3;
        error |= arr2.size() != 2 || arr2.capacity() != 2;
        error |= arr2[0] != 8 || arr2[1] != 1;
        if(error) {
            std::cerr << "xme::Array copy assignment error\n";
            ++errors;
        }
    }
    {
        xme::Array<int> arr1{5, 3};
        arr1.reserve(3);
        xme::Array<int> arr2{1};
        arr2       = std::move(arr1);
        bool error = !arr1.empty() || arr2.size() != 2 || arr2.capacity() != 3;
        error |= arr2[0] != 5 || arr2[1] != 3;
        if(error) {
            std::cerr << "xme::Array move assignment error\n";
            ++errors;
        }
    }
    return errors;
}

int test_insertion() {
    int errors = 0;
    {
        xme::Array<float> arr(2, 0.5);
        arr.push_back(0.25);
        bool error = arr[0] != 0.5f || arr[1] != 0.5f || arr[2] != 0.25f;
        error |= arr.capacity() != 4 || arr.size() != 3;
        if(error) {
            std::cerr << "xme::Array::pushBack error\n";
            ++errors;
        }
    }
    {
        std::array<int, 3> ar{1, 5, 3};
        xme::Array<float> arr;
        arr.push_back(ar.begin(), ar.end());
        bool error = arr[0] != 1 || arr[1] != 5 || arr[2] != 3;
        if(error) {
            std::cerr << "xme::Array::pushBack iterators error\n";
            ++errors;
        }
    }
    {
        std::array<float, 2> ar{-0.5, 9.25};
        xme::Array<float> arr;
        arr.push_back(ar);
        bool error = arr[0] != -0.5 || arr[1] != 9.25;
        if(error) {
            std::cerr << "xme::Array::pushBack range error\n";
            ++errors;
        }
    }
    {
        xme::Array<float> arr;
        arr.emplace_back(0.125);
        bool error = arr[0] != 0.125f;
        error |= arr.capacity() != 1 || arr.size() != 1;
        if(error) {
            std::cerr << "xme::Array::emplaceBack error\n";
            ++errors;
        }
    }
    {
        xme::Array<float> arr(3);
        arr.insert(arr.begin(), 0.25);
        arr.insert(arr.end(), 0.5f);
        arr.insert(arr.begin() + 1, 1);
        bool error = arr[0] != 0.25 || arr[1] != 1 || arr[2] != 0.5;
        arr.insert(arr.begin() + 1, 2.5);
        error |= arr[0] != 0.25 || arr[1] != 2.5 || arr[2] != 1 || arr[3] != 0.5;
        error |= arr.size() != 4 || arr.capacity() != 6;
        if(error) {
            std::cerr << "xme::Array::insert 1 error\n";
            ++errors;
        }
    }
    {
        std::vector<int> v{5, 3};
        std::vector<int> v2{7, 1};
        xme::Array<float> arr(3);
        auto it1   = arr.insert(arr.begin(), v.begin(), v.end());
        bool error = arr[0] != 5 || arr[1] != 3 || it1 != arr.begin();
        arr.insert(arr.begin() + 1, v2.begin(), v2.end());
        error |= arr[0] != 5 || arr[1] != 7 || arr[2] != 1 || arr[3] != 3;
        if(error) {
            std::cerr << "xme::Array::insert 2 error\n";
            ++errors;
        }
    }
    {
        std::vector<int> v{5, 3};
        std::list<int> v2{7, 1};
        xme::Array<float> arr(3);
        auto it1   = arr.insert(arr.begin(), v);
        bool error = arr[0] != 5 || arr[1] != 3 || it1 != arr.begin();
        arr.insert(arr.end(), v2);
        error |= arr[0] != 5 || arr[1] != 3 || arr[2] != 7 || arr[3] != 1;
        if(error) {
            std::cerr << "xme::Array::insert 3 error\n";
            ++errors;
        }
    }
    return errors;
}

int test_delete() {
    int errors = 0;
    {
        xme::Array<float> arr{0.5, 0.25};
        arr.pop_back();
        bool error = arr[0] != 0.5f || arr.size() != 1 || arr.capacity() != 2;
        arr.pop_back();
        error |= arr.size() != 0 || arr.capacity() != 2;
        if(error) {
            std::cerr << "xme::Array::popBack error\n";
            ++errors;
        }
    }
    {
        xme::Array<int> arr{2, 3, 1};
        auto it    = arr.erase(arr.begin());
        bool error = *(it++) != 3 || *(it++) != 1;
        if(error) {
            std::cerr << "xme::Array::erase 1 error\n";
            ++errors;
        }
    }
    {
        xme::Array<int> arr{2, 3, 1};
        auto it    = arr.erase(arr.begin(), arr.end() - 1);
        bool error = *(it++) != 1 || it != arr.end();
        if(error) {
            std::cerr << "xme::Array::erase 2 error\n";
            ++errors;
        }
    }
    return errors;
}

int test_resize() {
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

int test_insert_iterators() {
    int errors = 0;
    {
        xme::Array<int> arr(2);
        std::back_insert_iterator<xme::Array<int>> it{arr};
        it         = 10;
        it         = -3;
        it         = 5;
        bool error = arr.size() != 3 || arr.capacity() != 4;
        error |= arr[0] != 10 || arr[1] != -3 || arr[2] != 5;
        if(error) {
            std::cerr << "xme::Array back_insert_iterator error\n";
            ++errors;
        }
    }
    {
        xme::Array<int> arr;
        std::insert_iterator<xme::Array<int>> it{arr, arr.begin()};
        it         = -3;
        it         = 2;
        it         = 7;
        bool error = arr.size() != 3 || arr.capacity() != 4;
        error |= arr[0] != -3 || arr[1] != 2 || arr[2] != 7;
        if(error) {
            std::cerr << "xme::Array insert_iterator error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_access();
    errors += test_move_copy();
    errors += test_insertion();
    errors += test_delete();
    errors += test_resize();
    errors += test_insert_iterators();
    return errors;
}
