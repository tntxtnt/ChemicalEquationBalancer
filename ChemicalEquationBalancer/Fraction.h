#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <stdexcept>

class Fraction
{
    friend std::ostream& operator<<(std::ostream&, const Fraction&);
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
    Fraction operator-()const;
    operator bool()const;
    bool operator==(const Fraction&)const;
    bool operator<(const Fraction&)const;
public:
    int numerator()const;
    int denominator()const;
public:
    static long long gcd(long long, long long);
    static long long lcf(long long, long long);
private:
    void standardize();
    void assign(long long&, long long&);
private:
    int nu;
    int de;
};

#endif