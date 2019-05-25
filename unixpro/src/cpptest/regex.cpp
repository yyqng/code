/*
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <regex>
using namespace std;

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
*/
/*
void regextest2()
{
  std::string s ("there is a subsequence \\u003Cp> \\u003Cp> in the string\n");
  cout << s << endl;
  //std::regex e ("\\\\u003Cp>");
  std::regex e ("\\\\u[0-9a-zA-Z]*>");

  // using string/c-string (3) version:
  //std::cout << std::regex_replace (s, e, "$2");
  std::string result;
  std::regex_replace (std::back_inserter(result), s.begin(), s.end(), e, "$2");
  std::cout << result;

  // with flags:
  //std::cout << std::regex_replace (s,e,"$1 and $2",std::regex_constants::format_no_copy);
  //std::cout << std::endl;

}
*/

// regex_match example
#include <iostream>
#include <string>
#include <regex>
//#include <boost.hpp>

int regextest3 ()
{

  if (std::regex_match ("subject", std::regex("(sub)(.*)") ))
    std::cout << "string literal matched\n";

  const char cstr[] = "subject";
  std::string s ("subject");
  std::regex e ("(sub)(.*)");

  if (std::regex_match (s,e))
    std::cout << "string object matched\n";

  if ( std::regex_match ( s.begin(), s.end(), e ) )
    std::cout << "range matched\n";

  std::cmatch cm;    // same as std::match_results<const char*> cm;
  std::regex_match (cstr,cm,e);
  std::cout << "string literal with " << cm.size() << " matches\n";

  std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
  std::regex_match (s,sm,e);
  std::cout << "string object with " << sm.size() << " matches\n";

  std::regex_match ( s.cbegin(), s.cend(), sm, e);
  std::cout << "range with " << sm.size() << " matches\n";

  // using explicit flags:
  std::regex_match ( cstr, cm, e, std::regex_constants::match_default );

  std::cout << "the matches were: ";
  for (unsigned i=0; i<cm.size(); ++i) {
    std::cout << "[" << cm[i] << "] ";
  }

  std::cout << std::endl;

  return 0;
}



int regextest4 ()
{
  std::regex e (".*[a-z][0-9].*");
  //std::string s ("subject");
  //std::regex e ("(sub)(.*)");

/*
  std::string s ("there is a subsequence \\u003Cp> \\u003Cp> in the string");
  std::cout << s << std::endl;
  //std::regex e ("\\\\u[0-9a-zA-Z]*>");
  std::regex e (".*[a-z][0-9].*");

  std::cmatch cm;    // same as std::match_results<const char*> cm;
  // using explicit flags:
  std::regex_match ( s.c_str(), cm, e, std::regex_constants::match_default );

  std::cout << "the matches were: ";
  for (unsigned i=0; i<cm.size(); ++i) {
    std::cout << cm[i] << std::endl;
  }
  std::cout << std::endl;
  */
  return 0;
}



int
main(int argc, char *argv[])
{
    //regextest1();
    //regextest2();
    //regextest3();
    regextest4();
}
