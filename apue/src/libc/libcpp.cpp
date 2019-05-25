#include "libcpp.h"
#include <vector>
#include <utility>      // std::move
#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>       // std::string
// move example
void fortest()
{
    vector<int>veci{0, 1, 2, 3, 4};
    for(auto &ele : veci)
    {
        ele *=2;
        cout<<ele<<endl;
    }
}

// move example
int movetest () 
{
    std::string foo = "foo-string";
    std::string bar = "bar-string";
    std::vector<std::string> myvector;
  
    myvector.push_back (foo);                    // copies
    myvector.push_back (std::move(bar));         // moves
  
    std::cout << "myvector contains:";
    for (std::string& x:myvector) 
		std::cout << ' ' << x;
    std::cout << endl << "left string:" << foo << bar << '\n';
  
    return 0;
}
void libcpptest()
{
    //fortest();
	movetest ();

}
