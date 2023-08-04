#include <algorithm>
#include <iostream>
#include <xme/math/math.hpp>

bool isError(bool b) { return b == false; }

int testVector3() {
    int errors = 0;
    {
        xme::vec3 v{xme::dvec2(1, 2), 5};
        auto results = std::to_array({
            v[0] == 1,
            v[1] == 2,
            v[2] == 5,
        });
        auto error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Vector(Vector<T, 2>, auto) error\n";
            ++errors;
        }
    }
    {
        xme::vec3 v{5, xme::dvec2(1, 2)};
        auto results = std::to_array({
            v[0] == 5,
            v[1] == 1,
            v[2] == 2,
        });
        auto error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Vector(auto, Vector<T, 2>) error\n";
            ++errors;
        }
    }
    return errors;
}

int testVector4() {
    int errors = 0;
    {
        xme::vec4 v{xme::dvec2(3, -3), 5, 7};
        auto results = std::to_array({
            v[0] == 3,
            v[1] == -3,
            v[2] == 5,
            v[3] == 7,
        });
        auto error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Vector(Vector<T, 2>, auto, auto) error\n";
            ++errors;
        }
    }

    {
        xme::vec4 v{5, xme::dvec2(3, -3), 7};
        auto results = std::to_array({
            v[0] == 5,
            v[1] == 3,
            v[2] == -3,
            v[3] == 7,
        });
        auto error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Vector(auto, Vector<T, 2>, auto) error\n";
            ++errors;
        }
    }

    {
        xme::vec4 v{5, 7, xme::dvec2(3, -3)};
        auto results = std::to_array({
            v[0] == 5,
            v[1] == 7,
            v[2] == 3,
            v[3] == -3,
        });
        auto error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Vector(auto, auto, Vector<T, 2>) error\n";
            ++errors;
        }
    }

    {
        xme::vec4 v{xme::dvec3(-5, -8, 2), 7};
        auto results = std::to_array({
            v[0] == -5,
            v[1] == -8,
            v[2] == 2,
            v[3] == 7,
        });
        auto error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Vector(Vector<T, 3>, auto) error\n";
            ++errors;
        }
    }

    {
        xme::vec4 v{7, xme::dvec3(-5, -8, 2)};
        auto results = std::to_array({
            v[0] == 7,
            v[1] == -5,
            v[2] == -8,
            v[3] == 2,
        });
        auto error = std::ranges::any_of(results, isError);
        if (error) {
            std::cerr << "Vector(auto, Vector<T, 3>) error\n";
            ++errors;
        }
    }
    return errors;
}
int main() {
    int errors = 0;
    errors += testVector3();
    errors += testVector4();
    return errors;
}