#pragma once
#include <stdio.h>
#include <iostream>
using namespace std;
class Complex
{
    public:
        Complex(double r = 0, double i = 0)
                :re(r),im(i)
        { }
        Complex &operator+=(const Complex &r)
        {
            this->re += r.re;
            this->im += r.im;
            return *this;
        }
        double real ()const { return re;}
        double imag ()const { return im;}
        int func ( const Complex &param )
        {
            return param.re + param.im;
        }
    private:
        double re, im;
        friend Complex &__doapl (Complex *, const Complex &);

};

inline Complex
operator + (const Complex &x, const Complex &y )
{
    Complex ret(x);
    ret += y;
    return ret;
    //return Complex (x.real() + y.real(), x.imag() + y.imag());
}

inline Complex
operator += (const Complex &x, double y)
{
    return Complex (x.real() + y, x.imag());
}

inline Complex
operator += (double x , const Complex &y)
{
    return Complex (x + y.real(), y.imag());
}

ostream&
operator << (ostream& os, const Complex &x);

void cpptest();
