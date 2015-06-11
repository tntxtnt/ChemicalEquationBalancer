#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include <iostream>
#include <map>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <stack>

class FormulaParser
{
public:
    FormulaParser();
    void parse(const std::string&);
    const std::map<std::string, int>& getFormula()const;
private:
    static void appendElem(std::map<std::string, int>&, std::string&, int&);
    static int  appendInt(int, char);
    static bool isOpenParen(char);
    static bool isCloseParen(char);
    static char matchParen(char);
    static std::string strInvalidArgErr(const std::string&, size_t);
private:
    std::map<std::string, int> formula;
};

#endif