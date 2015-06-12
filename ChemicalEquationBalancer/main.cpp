#include "Fraction.h"
#include "Matrix.h"
#include "FormulaParser.h"
#include <set>
#include <algorithm>

typedef std::vector<int>           IntVect;
typedef std::vector<std::string>   StrVect;
typedef std::map<std::string, int> StrToIntMap;
typedef std::set<std::string>      StrSet;

IntVect equationCoefficients(const StrVect&, const StrVect&);
void printEquation(const StrVect&, const IntVect&, size_t = 0);

int main()
{
    StrVect lhsReactants, rhsReactants;
    
    /*lhsReactants.push_back("H2O");
    lhsReactants.push_back("CO2");
    rhsReactants.push_back("H2CO3");*/

    /*lhsReactants.push_back("K2Cr2O7");
    lhsReactants.push_back("H2SO3");
    lhsReactants.push_back("HCl");
    rhsReactants.push_back("KCl");
    rhsReactants.push_back("Cr2(SO4)3");
    rhsReactants.push_back("H2O");*/

    /*lhsReactants.push_back("Fe2(SO4)3");
    lhsReactants.push_back("H2SO4");
    rhsReactants.push_back("Fe(HSO4)2");*/

    lhsReactants.push_back("K4Fe(CN)6");
    lhsReactants.push_back("KMnO4");
    lhsReactants.push_back("H2SO4");
    rhsReactants.push_back("KHSO4");
    rhsReactants.push_back("Fe2(SO4)3");
    rhsReactants.push_back("MnSO4");
    rhsReactants.push_back("HNO3");
    rhsReactants.push_back("CO2");
    rhsReactants.push_back("H2O");

    try {
        IntVect coefs = equationCoefficients(lhsReactants, rhsReactants);
        printEquation(lhsReactants, coefs);
        printEquation(rhsReactants, coefs, lhsReactants.size());
    } catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << "\n";
    }
}


void printEquation(const StrVect& reactants, const IntVect& coefs, size_t k)
{
    if (coefs[k] != 1) std::cout << coefs[k] << ' ';
    std::cout << reactants[0];
    for (size_t i = 1; i < reactants.size(); ++i)
    {
        std::cout << " + ";
        if (coefs[i+k] != 1) std::cout << coefs[i+k] << ' ';
        std::cout << reactants[i];
    }
    std::cout << (k ? "\n" : " = ");
}

std::vector<StrToIntMap> parseReactants(const StrVect& reactants)
{
    std::vector<StrToIntMap> result;
    FormulaParser parser;
    for (size_t i = 0; i < reactants.size(); ++i)
    {
        parser.parse(reactants[i]);
        result.push_back(parser.getFormula());
    }
    return result;
}

StrSet getElements(const std::vector<StrToIntMap>& p)
{
    StrToIntMap::const_iterator it;
    StrSet result;
    for (size_t i = 0; i < p.size(); ++i)
        for (it = p[i].begin(); it != p[i].end(); ++it)
            result.insert(it->first);
    return result;
}

Matrix<Fraction> buildMatrix(const std::vector<StrToIntMap>& lhs,
                             const std::vector<StrToIntMap>& rhs,
                             const StrSet& elemSet)
{
    Matrix<Fraction> m(elemSet.size(), lhs.size() + rhs.size());
    StrSet::const_iterator      pElem;
    StrToIntMap::const_iterator it;
    size_t row = 0, col = 0;
    for (pElem = elemSet.begin(); pElem != elemSet.end(); ++pElem, ++row)
    {
        for (col = 0; col < lhs.size(); ++col)
        {
            it = lhs[col].find(*pElem);
            if (it != lhs[col].end())
                m.set(row, col, it->second);
        }
        for (col = 0; col < rhs.size(); ++col)
        {
            it = rhs[col].find(*pElem);
            if (it != rhs[col].end())
                m.set(row, lhs.size() + col, -it->second);
        }
    }
    return m;
}

bool isPositive(const Fraction& f)
{
    return f.numerator() > 0;
}

IntVect equationCoefficients(const StrVect& lhsReactants, const StrVect& rhsReactants)
{
    IntVect result;

    // parse lhsReactants, rhsReactants
    std::vector<StrToIntMap> lhs = parseReactants(lhsReactants),
                             rhs = parseReactants(rhsReactants);

    // check if elements on lhs and elements on rhs are the same set
    StrSet elemSet;
    if ( (elemSet=getElements(lhs)) != getElements(rhs) )
        throw std::invalid_argument("Elements on lhs and elements on rhs are different");

    // check unique solution
    int nElems = elemSet.size(), nReactants = lhs.size() + rhs.size();
    int k = nElems - nReactants;
    if (k < -1) throw std::invalid_argument("There are 2 or more free variables"
                                            " => no unique solution");

    // build matrix and convert to RREF
    Matrix<Fraction> mat = buildMatrix(lhs, rhs, elemSet);
    mat.convertToRRef();

    // get coefs
    std::vector<Fraction> coefs;
    for (int i = 0; i < nReactants - 1; ++i)
        coefs.push_back(-mat.get(i, nReactants - 1));
    coefs.push_back(1);

    // check if all coefs are positive
    if (std::count_if(coefs.begin(), coefs.end(), isPositive) != nReactants)
        throw std::invalid_argument("There are zero or negative coef(s)"
                                    " => no solution");

    // find least common factor of denominators
    long long dLcf = 1;
    for (size_t i = 0; i < coefs.size(); ++i)
        dLcf = Fraction::lcf(dLcf, coefs[i].denominator());

    // convert coefs to integers by multiplying with dLcf
    // and push to result
    for (size_t i = 0; i < coefs.size(); ++i)
        result.push_back((coefs[i] *= static_cast<int>(dLcf)).numerator());

    return result;
}