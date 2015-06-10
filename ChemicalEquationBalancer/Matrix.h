#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

template <typename T>
class Matrix
{
    template <typename H>
    friend std::ostream& operator<<(std::ostream&, const Matrix<H>&);
public:
    Matrix(int, int);
    void set(int, int, const T&);
    const T& get(int, int)const;
    void convertToRRef();
private:
    void rowInterchange(int, int);
    void rowMultiply(int, const T&, int = 0);
    void rowAddMultiple(int, int, const T&, int = 0);
private:
    std::vector< std::vector<T> > m;
};

#include "Matrix.tpp"

#endif