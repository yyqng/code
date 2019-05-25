#include "String.h"

/*
inline String&
String::operator += (const String &r)
{
    this->re += r.re;
    this->im += r.im;
    return *this;
}
*/

String& String::operator = (const String &r)
{
    if( this == &r)
        return *this;
    delete []this->m_data;
    m_data = new char[ strlen( r.m_data ) + 1]; 
    strcpy( this->m_data, r.m_data );
    return *this;
}
ostream&
operator << (ostream& os, const String &s)
{
    return os << s.c_str();
}
void stringtest()
{
    //String *s1 = new String ( "s1" );
    //String *s2 = new String ( "s2" );
    String s1 ( "s1" );
    String s2 ( "s2" );
    String s3( s1 );
    String s5( s2 );
    String s6( s2 );
    cout << s6 << s5 << s3 << endl;
    //s6 = s5 = s3;                          //error??
    //cout << s6 << s5 << s3 << endl;
    //s2 = (*s1);
    //cout<<( s2 = s1 );
    //cout << *s1 << *s2 << s3 << endl;
    //delete s1;
    //delete s2;
}

