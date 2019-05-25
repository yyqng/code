#include "Complex.h"

inline Complex &__doapl (Complex *ths, const Complex &r)
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}
/*
inline Complex&
Complex::operator += (const Complex &r)
{
    this->re += r.re;
    this->im += r.im;
    return *this;
}
*/
ostream&
operator << (ostream& os, const Complex &x)
{
    return os << "(" << x.real()<< ","<< x.imag() << ")";
}
void cpptest()
{
    Complex *c1 = new Complex ( 1, 1 );
    Complex c2( 1, 1);
    Complex c3( 1, 1);
    c3 += c2 += *c1;
    cout << *c1 << c2 << c3 << endl;
    delete c1;
}

