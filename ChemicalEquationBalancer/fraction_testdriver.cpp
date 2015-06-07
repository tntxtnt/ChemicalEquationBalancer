#include <iostream>
#include "Fraction.h"

int main()
{
    Fraction a;
    Fraction b = 5;
    Fraction c(3, 7);
    Fraction d(-1, 5);
    Fraction e(21, -9);
    Fraction f(-6, -5);
    Fraction g(6, -9);

    std::cout << "Test constructors:\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";
    std::cout << "d = " << d << "\n";
    std::cout << "e = " << e << "\n";
    std::cout << "f = " << f << "\n";
    std::cout << "g = " << g << "\n";
    try {
        Fraction invalid(1, 0);
    } catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << "\n";
    }

    std::cout << "\nTest operator+:\n";
    std::cout << "a + b = " << a + b << "\n";
    std::cout << "b + d = " << b + d << "\n";
    std::cout << "c + d = " << c + d << "\n";
    try {
        Fraction x(1, 65536);
        Fraction y = x + x;
        std::cout << "y = " << y << "\n";

        Fraction w(1, 65537);
        Fraction z(1, 65539);
        std::cout << "w + z = " << w + z << "\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << "\n";
    }

    std::cout << "\nTest operator-:\n";
    std::cout << "a - b = " << a - b << "\n";
    std::cout << "b - d = " << b - d << "\n";
    std::cout << "c - d = " << c - d << "\n";
    try {
        Fraction x(1, 65536);
        Fraction y = x - x;
        std::cout << "y = " << y << "\n";

        Fraction w(1, 65537);
        Fraction z(1, 65539);
        std::cout << "w - z = " << w - z << "\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << "\n";
    }

    std::cout << "\nTest operator*:\n";
    std::cout << "a * b = " << a * b << "\n";
    std::cout << "b * d = " << b * d << "\n";
    std::cout << "c * d = " << c * d << "\n";
    try {
        Fraction x(1, 65536);
        Fraction y = x * x;
        std::cout << "y = " << y << "\n";

        Fraction w(1, 65537);
        Fraction z(1, 65539);
        std::cout << "w * z = " << w * z << "\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << "\n";
    }

    std::cout << "\nTest operator/:\n";
    std::cout << "a / b = " << a / b << "\n";
    std::cout << "b / d = " << b / d << "\n";
    std::cout << "c / d = " << c / d << "\n";
    try {
        Fraction x(1, 65536);
        Fraction y = x / x;
        std::cout << "y = " << y << "\n";

        Fraction w(1, 65537);
        Fraction z(1, 65539);
        std::cout << "w / z = " << w / z << "\n";

        std::cout << "w / a = " << w / a << "\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << "\n";
    }
}