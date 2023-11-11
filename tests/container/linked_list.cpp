#include <xme/container/linked_list.hpp>
#include <iostream>
#include <vector>
#include <forward_list>

int test_access() {
    int errors = 0;
    {
        xme::LinkedList<int> l{2, 5};
        auto begin = l.begin();
        bool error = *(begin++) != 2;
        error |= *(begin++) != 5;
        error |= begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::(begin|end) error";
            ++errors;
        }
    }
    {
        xme::LinkedList<int> l{3, 5};
        bool error = l.front() != 3;
        if(error) {
            std::cerr << "xme::LinkedList::front error\n";
            ++errors;
        }
    }
    return errors;
}

int test_insertion() {
    int errors = 0;
    {
        xme::LinkedList<int> l(2);
        l.push_front(3);
        auto begin = l.cbegin();
        bool error = *(begin++) != 3 || *(begin++) != 0 || *(begin++) != 0;
        error |= begin != l.cend();
        if(error) {
            std::cerr << "xme::LinkedList::pushFront error\n";
            ++errors;
        }
    }
    {
        xme::LinkedList<int> l(2, 1);
        l.emplace_front(5);
        auto begin = l.cbegin();
        bool error = *(begin++) != 5 || *(begin++) != 1 || *(begin++) != 1;
        error |= begin != l.cend();
        if(error) {
            std::cerr << "xme::LinkedList::emplaceFront error\n";
            ++errors;
        }
    }
    {
        std::vector<int> a{5, 3};
        xme::LinkedList<int> l{a.begin(), a.end()};
        l.emplace_after(l.cbegin(), -6);
        auto begin = l.begin();
        bool error = *(begin++) != 5 || *(begin++) != -6 || *(begin++) != 3;
        error |= begin != l.cend();
        if(error) {
            std::cerr << "xme::LinkedList::emplaceAfter error\n";
            ++errors;
        }
    }
    {
        std::vector<int> a{7, 1};
        xme::LinkedList<int> l{a};
        l.insert_after(l.begin(), 5);
        auto begin = l.begin();
        bool error = *(begin++) != 7 || *(begin++) != 5 || *(begin++) != 1;
        error |= begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::insertAfter error\n";
            ++errors;
        }
    }
    std::forward_list<int> a;
    return errors;
}

int test_erase() {
    int errors = 0;
    {
        xme::LinkedList<int> l{5, 3, 1, 4};
        l.erase_after(l.before_begin());
        bool error = l.front() != 3;
        auto begin = l.begin();
        l.erase_after(l.begin());
        error |= *(begin++) != 3 || *(begin++) != 4 || begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::eraseAfter 1 error\n";
            ++errors;
        }
    }
    {
        xme::LinkedList<int> l{5, 3, 1, 7};
        auto begin = l.begin();
        auto end   = ++(++(++l.begin()));
        l.erase_after(begin, end);
        bool error = *(begin++) != 5 || *(begin++) != 7 || begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::eraseAfter 2 error\n";
            ++errors;
        }
    }
    {
        xme::LinkedList<int> l{9, 3, 1};
        l.pop_front();
        auto begin = l.begin();
        bool error = *(begin++) != 3 || *(begin++) != 1 || begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::popFront error\n";
            ++errors;
        }
    }
    {
        xme::LinkedList<int> l{5, 3, 1};
        l.clear();
        bool error = !l.is_empty() || l.begin() != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::clear error\n";
            ++errors;
        }
    }
    return errors;
}

int test_copy_move() {
    int errors = 0;
    {
        xme::LinkedList<int> tmp{1, 5};
        xme::LinkedList<int> l{std::move(tmp)};
        auto begin = l.begin();
        bool error = !tmp.is_empty() || *(begin++) != 1 || *(begin++) != 5;
        error |= begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList move constructor error\n";
            ++errors;
        }
    }
    {
        xme::LinkedList<int> tmp{5, 3};
        xme::LinkedList<int> l{1};
        l          = std::move(tmp);
        auto begin = l.begin();
        bool error = !tmp.is_empty() || *(begin++) != 5 || *(begin++) != 3;
        error |= begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList move assignment error\n";
            ++errors;
        }
    }
    {
        const xme::LinkedList<int> l1{5, 3};
        xme::LinkedList<int> l2{l1};
        auto begin1 = l1.begin();
        auto begin2 = l2.begin();
        bool error  = *(begin2++) != 5 || *(begin2++) != 3 || begin2 != l2.end();
        error |= *(begin1++) != 5 || *(begin1++) != 3 || begin1 != l1.end();
        error |= l1.begin() == l2.end();
        if(error) {
            std::cerr << "xme::LinkedList copy constructor error\n";
            ++errors;
        }
    }
    {
        const xme::LinkedList<int> l1{2, 7};
        xme::LinkedList<int> l2{5, 8, 1, -3, 2};
        l2          = l1;
        auto begin1 = l1.begin();
        auto begin2 = l2.begin();
        bool error  = *(begin2++) != 2 || *(begin2++) != 7 || begin2 != l2.end();
        error |= *(begin1++) != 2 || *(begin1++) != 7 || begin1 != l1.end();
        error |= l1.begin() == l2.end();
        if(error) {
            std::cerr << "xme::LinkedList copy assignment error\n";
            ++errors;
        }
    }
    {
        xme::LinkedList<int> l{5, 1, 5};
        l          = {7, 3};
        auto begin = l.begin();
        bool error = *(begin++) != 7 || *(begin++) != 3 || begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList initializer_list assignment error\n";
            ++errors;
        }
    }
    {
        std::vector<int> v{5, 3};
        xme::LinkedList<int> l;
        l.assign(v.begin(), v.end());
        auto begin = l.begin();
        bool error = *(begin++) != 5 || *(begin++) != 3 || begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::assign 1 error\n";
            ++errors;
        }
    }
    {
        std::vector<int> v{1, -3};
        xme::LinkedList<int> l{5, 3, 1, 6};
        l.assign(v);
        auto begin = l.begin();
        bool error = *(begin++) != 1 || *(begin++) != -3 || begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::assign 2 error\n";
            ++errors;
        }
    }
    {
        xme::LinkedList<int> l{5, 3, 1, 6};
        l.assign({3, 2});
        auto begin = l.begin();
        bool error = *(begin++) != 3 || *(begin++) != 2 || begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::assign 3 error\n";
            ++errors;
        }
    }
    return errors;
}

int test_operations() {
    int errors = 0;
    {
        xme::LinkedList<int> l{2, 5, 1};
        l.reverse();
        auto begin = l.begin();
        bool error = *(begin++) != 1 || *(begin++) != 5 || *(begin++) != 2;
        error |= begin != l.end();
        if(error) {
            std::cerr << "xme::LinkedList::reverse error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += test_access();
    errors += test_insertion();
    errors += test_erase();
    errors += test_copy_move();
    errors += test_operations();
    return errors;
}
