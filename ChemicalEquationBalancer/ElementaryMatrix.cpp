#include "ElementaryMatrix.h"

ElementaryMatrix::ElementaryMatrix(int rows, int cols) : m(rows, std::vector<Fraction>(cols))
{
}

void ElementaryMatrix::set(int r, int c, const Fraction& f)
{
    m[r][c] = f;
}

const Fraction& ElementaryMatrix::get(int r, int c)const
{
    return m[r][c];
}

std::ostream& operator<<(std::ostream& out, const ElementaryMatrix& a)
{
    for (size_t r = 0; r < a.m.size(); ++r)
    {
        for (size_t c = 0; c < a.m[0].size(); ++c)
            out << a.m[r][c] << "\t";
        out << "\n";
    }
    return out;
}

void ElementaryMatrix::rowInterchange(int r1, int r2)
{
    if (r1 != r2) m[r1].swap(m[r2]);
}

void ElementaryMatrix::rowMultiply(int r, const Fraction& f, int startCol)
{
    for (size_t c = startCol; c < m[0].size(); ++c)
        m[r][c] *= f;
}

void ElementaryMatrix::rowAddMultiple(int r1, int r2, const Fraction& f, int startCol)
{
    for (size_t c = startCol; c < m[0].size(); ++c)
        m[r1][c] += m[r2][c] * f;
}

void ElementaryMatrix::convertToRRef()
{
    size_t ROWS = m.size(), COLS = m[0].size();
    size_t r, c, i, j;
    for (r = 0, c = 0; r < ROWS && c < COLS; ++c)
    {
        //find first row which has non-zero entry at column c
        for (i = r; i < ROWS; ++i) if (m[i][c]) break;
        if (i == ROWS) continue; //cannot find such row
        //swap with current working row
        rowInterchange(r, i);
        //normalize that row
        rowMultiply(r, Fraction(1) / m[r][c], c);
        //clear all m[r++][c] entries (~ convert to REF first)
        for (i = r + 1; i < ROWS; ++i) rowAddMultiple(i, r, -m[i][c], c);
        ++r;
    } //r-1 = index of the last non-zero row
    //convert to RREF 
    for (--r; r > 0; --r)
    {
        for (j = 0; j < COLS; ++j) if (m[r][j]) break;
        for (i = 0; i < r; ++i)
        {
            if (m[i][j]) rowAddMultiple(i, r, -m[i][j], j+1);
            m[i][j] = 0;
        }
    }
}