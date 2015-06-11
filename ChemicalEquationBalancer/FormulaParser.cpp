#include "FormulaParser.h"

FormulaParser::FormulaParser() : formula()
{
}

void FormulaParser::parse(const std::string& s)
{
    formula.clear();
    std::string elem;
    int count = 0;
    std::stack<char> p;
    std::stack<std::map<std::string,int>> q;
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (isupper(s[i])) {
            if (!elem.empty())
                appendElem(q.empty() ? formula : q.top(), elem, count);
            elem += s[i];
        }
        else if (islower(s[i])) {
            if (elem.empty() || count)
                throw std::invalid_argument(strInvalidArgErr(s, i));
            elem += s[i];
        }
        else if (isdigit(s[i])) {
            if (elem.empty()) throw std::invalid_argument(strInvalidArgErr(s, i));
            count = appendInt(count, s[i]);
            if (!count) throw std::invalid_argument(strInvalidArgErr(s, i));
        }
        else if (isOpenParen(s[i])) {
            appendElem(q.empty() ? formula : q.top(), elem, count);
            p.push(s[i]);
            q.push(std::map<std::string,int>());
        }
        else if (isCloseParen(s[i])) {
            if (p.empty() || s[i] != matchParen(p.top()))
                throw std::invalid_argument("Mismatch parentheses");
            appendElem(q.top(), elem, count);
            for (++i; isdigit(s[i]); ++i) count = appendInt(count, s[i]);
            --i;
            std::map<std::string,int> f = q.top();
            q.pop();
            std::map<std::string,int>& dst = q.empty() ? formula : q.top();
            for (std::map<std::string,int>::iterator it = f.begin(); it != f.end(); ++it)
                dst[it->first] += it->second * count;
            count = 0;
            p.pop();
        }
        else throw std::invalid_argument(strInvalidArgErr(s, i));
    }
    if (!p.empty()) throw std::invalid_argument("Mismatch parentheses");
    appendElem(formula, elem, count);
}

const std::map<std::string,int>& FormulaParser::getFormula()const
{
    return formula;
}

void FormulaParser::appendElem(std::map<std::string,int>& formula, std::string& elem, int& count)
{
    if (elem.empty()) return;
    if (!count) ++count;
    formula[elem] += count;
    elem.clear();
    count = 0;
}

int FormulaParser::appendInt(int n, char c)
{
    return 10 * n + c - '0';
}

std::string FormulaParser::strInvalidArgErr(const std::string& s, size_t i)
{
    std::ostringstream oss;
    oss << "Invalid character '" << s[i] << "' at position " << i;
    return oss.str();
}

bool FormulaParser::isOpenParen(char c)
{
    return c == '(' || c == '[';
}

bool FormulaParser::isCloseParen(char c)
{
    return c == ')' || c == ']';
}

char FormulaParser::matchParen(char c)
{
    switch (c)
    {
    case '(': return ')';
    case '[': return ']';
    case ')': return '(';
    case ']': return '[';
    default: return '\0';
    }
}