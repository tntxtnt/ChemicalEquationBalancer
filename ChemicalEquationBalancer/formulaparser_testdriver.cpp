#include <iostream>
#include "FormulaParser.h"

std::ostream& operator<<(std::ostream& out, const std::map<std::string, int>& f)
{
    std::map<std::string, int>::const_iterator it = f.begin();
    for (; it != f.end(); ++it)
        out << it->first << ": " << it->second << "\n";
    return out;
}

int main()
{
    FormulaParser parser;
    try {
        parser.parse("Fe0O3");
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }

    std::cout << "\n";
    try {
        parser.parse("c");
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }

    std::cout << "\n";
    try {
        parser.parse("Fe3o4");
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }

    std::cout << "\n";
    try {
        parser.parse("Fe3O4");
        std::cout << parser.getFormula() << "\n";
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }

    std::cout << "\n";
    try {
        parser.parse("Fe2(SO4)3");
        std::cout << parser.getFormula() << "\n";
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }

    std::cout << "\n";
    try {
        parser.parse("Fe2SO4)3");
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }


    std::cout << "\n";
    try {
        parser.parse("Fe2(3SO4)3");
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }

    std::cout << "\n";
    try {
        parser.parse("Fe2(S(O4)3");
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }

    std::cout << "\n";
    try {
        parser.parse("Pb(H(TiO3)2)2U[(H2O)3]2");
        std::cout << parser.getFormula() << "\n";
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
    }
}
