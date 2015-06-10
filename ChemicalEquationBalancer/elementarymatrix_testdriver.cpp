#include <iostream>
#include "Matrix.h"
#include "Fraction.h"

int main()
{
    // 1 0 2 3 5
    // 0 0 0 0 7
    // 4 5 2 3 3
    // 5 1 4 0 0
    Matrix<Fraction> m(4, 5);
    m.set(0, 0, 1); m.set(0, 1, 0); m.set(0, 2, 2); m.set(0, 3, 3); m.set(0, 4, 5);
    m.set(1, 0, 0); m.set(1, 1, 0); m.set(1, 2, 0); m.set(1, 3, 0); m.set(1, 4, 7);
    m.set(2, 0, 4); m.set(2, 1, 5); m.set(2, 2, 2); m.set(2, 3, 3); m.set(2, 4, 3);
    m.set(3, 0, 5); m.set(3, 1, 1); m.set(3, 2, 4); m.set(3, 3, 0); m.set(3, 4, 0);

    std::cout << m << "\n";

    m.convertToRRef();
    std::cout << m << "\n";
}