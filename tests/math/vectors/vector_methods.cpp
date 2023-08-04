#include "common.hpp"

int testMethods() {
    int errors = 0;
    {
        xme::vec3 v1{3, 0, 0};
        if(v1.lenght() != 3) {
            std::cerr << "Vector::lenght() Error\n";
            ++errors;
        }

        xme::vec3 v2{4, 3, 0};
        if(v2.lenght() != 5) {
            std::cerr << "Vector::lenght() Error\n";
            ++errors;
        }
    }

    {
        xme::vec3 v1{5, 0, 0};
        xme::vec3 v2{0, 5, 0};
        if(v1.dot(v2) != 0) {
            std::cerr << "Vector::dot(Vector<U, Size>) Error\n";
            ++errors;
        }

        xme::vec3 v3{5, 0, 0};
        xme::vec3 v4{5, 0, 0};
        if(v3.dot(v4) != 25) {
            std::cerr << "Vector::dot(Vector<U, Size>) Error\n";
            ++errors;
        }
        //6 + 24 + 1 == 31
        xme::vec3 v5{3, 3, 1};
        xme::vec3 v6{2, 8, 1};
        if(v5.dot(v6) != 31) {
            std::cerr << "Vector::dot(Vector<U, Size>) Error\n";
            ++errors;
        }
    }

    {
        xme::vec3 v1{1, 0, 0};
        xme::vec3 v2{0, 5, 0};
        if(auto v3 = v1.cross(v2); v3[0] != 0 || v3[1] != 0 || v3[2] != 5) {
            std::cerr << "Vector::cross(Vector<U, Size>) Error\n";
            ++errors;
        }

        xme::vec3 v3{-3, 7, 0};
        xme::vec3 v4{2, 5, 0};
        auto v5 = v3.cross(v4);
        if(auto v5 = v3.cross(v4); v5[0] != 0 || v5[1] != 0 || v5[2] != -29) {
            std::cerr << "Vector::cross(Vector<U, Size>) Error\n";
            ++errors;
        }
    }

    {
        xme::vec3 v1{};
        xme::vec3 v2{4, 3, 0};
        auto v3 = v1.distance(v2);
        auto v4 = v2.distance(v1); 
        if(v3 != 5 || v4 != 5) {
            std::cerr << "Vector::distance(Vector<U, Size>) Error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testMethods();
    return errors;
}