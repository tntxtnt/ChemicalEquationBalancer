#include "Fraction.h"

Fraction::Fraction(int nu, int de) : nu(nu), de(de)
{
    if (de == 0) throw std::invalid_argument("0 denominator");
    standardize();
}

long long Fraction::gcd(long long q, long long r)
{
    return q%r ? gcd(r, q%r) : r;
}

long long Fraction::lcf(long long a, long long b)
{
    return a / gcd(a, b) * b;
}

void Fraction::standardize()
{
    if (de < 0) { nu = -nu; de = -de; }
    int g = static_cast<int>( gcd(nu > 0 ? nu : -nu, de) );
    nu /= g;
    de /= g;
}

std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
    out << f.nu;
    if (f.de != 1) out << '/' << f.de;
    return out;
}

void Fraction::assign(long long& newNu, long long& newDe)
{
    long long g = gcd(newNu > 0 ? newNu : -newNu, newDe);
    newNu /= g;
    newDe /= g;
    nu = static_cast<int>(newNu);
    de = static_cast<int>(newDe);
}

Fraction& Fraction::operator+=(const Fraction& rhs)
{
    long long newDe = static_cast<long long>(de) * rhs.de;
    long long newNu = static_cast<long long>(nu) * rhs.de + static_cast<long long>(rhs.nu) * de;
    assign(newNu, newDe);
    if (nu != newNu || de != newDe) throw std::overflow_error("operator+ overflows");
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& rhs)
{
    long long newDe = static_cast<long long>(de) * rhs.de;
    long long newNu = static_cast<long long>(nu) * rhs.de - static_cast<long long>(rhs.nu) * de;
    assign(newNu, newDe);
    if (nu != newNu || de != newDe) throw std::overflow_error("operator- overflows");
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& rhs)
{
    long long newDe = static_cast<long long>(de) * rhs.de;
    long long newNu = static_cast<long long>(nu) * rhs.nu;
    assign(newNu, newDe);
    if (nu != newNu || de != newDe) throw std::overflow_error("operator* overflows");
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& rhs)
{
    if (rhs.nu == 0) throw std::invalid_argument("Divide by 0");
    long long newDe = static_cast<long long>(de) * rhs.nu;
    long long newNu = static_cast<long long>(nu) * rhs.de;
    if (newDe < 0) { newDe = -newDe; newNu = -newNu; }
    assign(newNu, newDe);
    if (nu != newNu || de != newDe) throw std::overflow_error("operator* overflows");
    return *this;
}

Fraction Fraction::operator+(const Fraction& rhs)const
{
    Fraction lhs = *this;
    return lhs += rhs;
}

Fraction Fraction::operator-(const Fraction& rhs)const
{
    Fraction lhs = *this;
    return lhs -= rhs;
}

Fraction Fraction::operator*(const Fraction& rhs)const
{
    Fraction lhs = *this;
    return lhs *= rhs;
}

Fraction Fraction::operator/(const Fraction& rhs)const
{
    Fraction lhs = *this;
    return lhs /= rhs;
}

Fraction::operator bool()const
{
    return nu != 0;
}

bool Fraction::operator==(const Fraction& rhs)const
{
    return nu == rhs.nu && de == rhs.de;
}

bool Fraction::operator<(const Fraction& rhs)const
{
    return static_cast<long long>(nu) * rhs.de < static_cast<long long>(de) * rhs.nu;
}

Fraction Fraction::operator - ()const
{
    Fraction f = *this;
    f.nu = -f.nu;
    return f;
}

int Fraction::numerator()const
{
    return nu;
}

int Fraction::denominator()const
{
    return de;
}