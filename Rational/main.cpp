#include <iostream>

#include "Rational.hpp"

int main() {
    try {
        Rational r1(3, 4);
        Rational r2(5, 8);

        std::cout << "r1 = ";
        r1.displayFraction();
        std::cout << "r2 = ";
        r2.displayFraction();

        std::cout << "r1 as decimal = ";
        r1.displayDecimalFraction();
        std::cout << "r2 as decimal = ";
        r2.displayDecimalFraction();

        auto comparison = r1 <=> r2;

        if (comparison == std::strong_ordering::less) {
            std::cout << "r1 is less than r2" << std::endl;
        } else if (comparison == std::strong_ordering::equal) {
            std::cout << "r1 is equal to r2" << std::endl;
        } else if (comparison == std::strong_ordering::greater) {
            std::cout << "r1 is greater than r2" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;

}