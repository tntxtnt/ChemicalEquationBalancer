#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <stdexcept>

class Fraction
{
private:
    static long long gcd(long long, long long);
public:
    Fraction(int = 0, int = 1);
    Fraction& operator+=(const Fraction&);
    Fraction& operator-=(const Fraction&);
    Fraction& operator*=(const Fraction&);
    Fraction& operator/=(const Fraction&);
    Fraction operator+(const Fraction&)const;
    Fraction operator-(const Fraction&)const;
    Fraction operator*(const Fraction&)const;
    Fraction operator/(const Fraction&)const;
    operator bool()const;
    bool operator==(const Fraction&)const;
    bool operator<(const Fraction&)const;
public:
    friend std::ostream& operator<<(std::ostream&, const Fraction&);
private:
    void standardize();
    void assign(long long&, long long&);
private:
    int nu;
    int de;
};

#endif