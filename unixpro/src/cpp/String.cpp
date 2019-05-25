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

// regex_replace example
#include <iostream>
#include <string>
#include <regex>
#include <iterator>

void regextest1()
{
  std::string s ("there is a subsequence in the string\n");
  std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

  // using string/c-string (3) version:
  std::cout << std::regex_replace (s,e,"sub-$2");

  // using range/c-string (6) version:
  std::string result;
  std::regex_replace (std::back_inserter(result), s.begin(), s.end(), e, "$2");
  std::cout << result;

  // with flags:
  std::cout << std::regex_replace (s,e,"$1 and $2",std::regex_constants::format_no_copy);
  std::cout << std::endl;

}

void regextest2()
{
  std::string s ("there is a subsequence \\u003Cp> \\u003Cp> in the string\n");
  cout << s << endl;
  //std::regex e ("\\\\u003Cp>");
  std::regex e ("\\\\u[0-9a-zA-Z]*>");

  // using string/c-string (3) version:
  std::cout << std::regex_replace (s, e, "$2");

  // with flags:
  //std::cout << std::regex_replace (s,e,"$1 and $2",std::regex_constants::format_no_copy);
  //std::cout << std::endl;

}
