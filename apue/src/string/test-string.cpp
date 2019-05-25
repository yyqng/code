#include <iostream>
#include <stdio.h>
#include <string.h>

//************************************
// Method:    string_replace
// FullName:  string_replace
// Access:    public 
// Returns:   void
// Qualifier: 把字符串的strsrc替换成strdst
// Parameter: std::string & strBig
// Parameter: const std::string & strsrc
// Parameter: const std::string & strdst
//************************************
void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst)
{
    size_t pos = 0;
    size_t srclen = strsrc.length();
    size_t dstlen = strdst.length();

    while( (pos=strBig.find(strsrc, pos)) != std::string::npos )
    {
        strBig.replace( pos, srclen, strdst );
        pos += dstlen;
    }   
} 


int main(int argc, char* argv[])
{
    std::string strContent = "This is a Test";
    std::string strsrc = "is";
    std::string strdst = "demo";

    string_replace(strContent, strsrc, strdst);

    std::cout << strContent << std::endl;


    return 0;
}

