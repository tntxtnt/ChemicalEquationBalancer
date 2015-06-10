#include <iostream>
#include <vector>

template <typename T>
Matrix<T>::Matrix(int rows, int cols) : m(rows, std::vector<T>(cols))
{
}

template <typename T>
void Matrix<T>::set(int r, int c, const T& f)
{
    m[r][c] = f;
}

template <typename T>
const T& Matrix<T>::get(int r, int c)const
{
    return m[r][c];
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& a)
{
    for (size_t r = 0; r < a.m.size(); ++r)
    {
        for (size_t c = 0; c < a.m[0].size(); ++c)
            out << a.m[r][c] << "\t";
        out << "\n";
    }
    return out;
}

template <typename T>
void Matrix<T>::rowInterchange(int r1, int r2)
{
    if (r1 != r2) m[r1].swap(m[r2]);
}

template <typename T>
void Matrix<T>::rowMultiply(int r, const T& f, int startCol)
{
    for (size_t c = startCol; c < m[0].size(); ++c)
        m[r][c] *= f;
}

template <typename T>
void Matrix<T>::rowAddMultiple(int r1, int r2, const T& f, int startCol)
{
    for (size_t c = startCol; c < m[0].size(); ++c)
        m[r1][c] += m[r2][c] * f;
}

template <typename T>
void Matrix<T>::convertToRRef()
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
        //clear all m[r++][c] entries (~ convert to REF first)
        for (i = r + 1; i < ROWS; ++i) rowAddMultiple(i, r, -m[i][c] / m[r][c], c);
        ++r;
    } //r-1 = index of the last non-zero row
    //now that m is REF, convert it to reduced REF  (RREF)
    for (--r; r > 0; --r)
    {
        for (j = 0; j < COLS; ++j) if (m[r][j]) break; //find first non-zero entry (m[r][j])
        for (i = 0; i < r; ++i)
        {
            if (m[i][j]) rowAddMultiple(i, r, -m[i][j] / m[r][j], j+1);
            m[i][j] = 0;
        }
        //normalize current row
        rowMultiply(r, T(1) / m[r][j], c);
        m[r][j] = 1;
    }
}