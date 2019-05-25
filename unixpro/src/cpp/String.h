#pragma once
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
class String
{
    public:
        String( )
        {
            m_data = new char[1]; 
            m_data[0] = '\0';
        }
        String( const char *s = 0)
        {
            if( s )
            {
                m_data = new char[ strlen( s ) + 1]; 
                strcpy( this->m_data, s );
            }
            else
            {
                m_data = new char[ 1 ]; 
                m_data[ 0 ] = '\0'; 
            }
        }
        String& operator = (const String &r);
        char *c_str()const { return m_data ;};
    private:
        char *m_data;

};
/*
inline String
operator + (const String &x, const String &y )
{
    String ret(x);
    ret += y;
    return ret;
    //return String (x.real() + y.real(), x.imag() + y.imag());
}

inline String
operator += (const String &x, double y)
{
    return String (x.real() + y, x.imag());
}

inline String
operator += (double x , const String &y)
{
    return String (x + y.real(), y.imag());
}
*/
ostream&
operator << (ostream& os, const String &x);

void stringtest();
void regextest2();
void regextest1();
