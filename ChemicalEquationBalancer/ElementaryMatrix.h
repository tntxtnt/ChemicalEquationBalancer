#ifndef ELEMENTARY_ElementaryMatrix_H
#define ELEMENTARY_ElementaryMatrix_H

#include <iostream>
#include <vector>
#include "Fraction.h"

class ElementaryMatrix
{
    friend std::ostream& operator<<(std::ostream&, const ElementaryMatrix&);
public:
    ElementaryMatrix(int, int);
    void set(int, int, const Fraction&);
    const Fraction& get(int, int)const;
    void convertToRRef();
private:
    void rowInterchange(int, int);
    void rowMultiply(int, const Fraction&, int = 0);
    void rowAddMultiple(int, int, const Fraction&, int = 0);
private:
    std::vector< std::vector<Fraction> > m;
};

#endif