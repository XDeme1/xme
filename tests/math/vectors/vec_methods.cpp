#include "common.hpp"

int testLenght() {
    int errors = 0;
    {
        std::array results{
            xme::vec3{3, 0, 0}.lenght() == 3,
            xme::vec3{4, 3, 0}.lenght() == 5,
            xme::vec4{5, 1, 3, 1}.lenght() == 6,
        };

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector::lenght() error\n";
            ++errors;
        }
    }

    return errors;
}

int testDot() {
    int errors = 0;
    {
        std::array results{
            xme::vec3{5, 0, 0}.dot(xme::vec3{0, 5, 0}) == 0,
            xme::vec3{5, 0, 0}.dot(xme::vec3{5, 0, 0}) == 25,
            xme::vec3{3, 3, 1}.dot(xme::vec3{2, 8, 1}) == 31
        };
    
        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector::dot(Vector<U, Size>) Error\n";
            ++errors;
        }
    }
    return errors;
}

int testCross() {
    int errors = 0;
    {
        std::array results{
            xme::vec3{1, 0, 0}.cross(xme::vec3{0, 5, 0}) == xme::vec3{0, 0, 5},
            xme::vec3{-3, 7, 0}.cross(xme::vec3{2, 5, 0}) == xme::vec3{0, 0, -29},
        };

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector::cross(Vector<U, Size>) Error\n";
            ++errors;
        }
    }
    return errors;
}

int testDistance() {
    int errors = 0;
    {
        std::array results{
            xme::vec3{}.distance(xme::vec3{4, 3, 0}) == 5,
            xme::vec3{4, 3, 0}.distance(xme::vec3{}) == 5,
        };

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector::distance(Vector<U, Size>) Error\n";
            ++errors;
        }
    }
    return errors;
}

int testReflect() {
    int errors = 0;
    {
        xme::vec3 v1{1, 1, 1};
        auto results = std::to_array({
            v1.reflect(xme::vec3{0, 1, 0}) == xme::vec3{1, -1, 1},
            v1.reflect(xme::vec3{1, 0, 0}) == xme::vec3{-1, 1, 1},
            v1.reflect(xme::vec3{0, 0, 1}) == xme::vec3{1, 1, -1},
        });

        bool error = std::ranges::any_of(results, isError);
        if(error) {
            std::cerr << "Vector::reflect(Vector<U, Size>&) Error\n";
            ++errors;
        }
    }
    return errors;
}

int main() {
    int errors = 0;
    errors += testLenght();
    errors += testDot();
    errors += testCross();
    errors += testDistance();
    errors += testReflect();
    return errors;
}