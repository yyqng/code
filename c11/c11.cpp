//Moving to C++ 11
//1. Type deduction
//Type deduction
int* getValue()
{
    return nullptr;
}
auto p1 = getValue();
auto *p2 = getValue();
auto x = 27;
auto y {27};
const auto cx = x;
const auto& rx = x;
auto&& uref1 = x;
auto&& uref2 = cx;
auto&& uref3 = 27;
//Question: What are the types of the above variables (i.e. p1, p2, x, y, ....)?
//Does "auto&&" mean a universal reference?

//decltype
vector<int> v;
const vector<int> &rv = v;
decltype(rv[0]) x = 0;     // does it crash? why?
auto x1 = 0;
decltype(v[0]) x2 = x1;
auto vx = rv[0];           // does it crash? why?
v.push_back(1);
auto vx1 = rv[0];
decltype(vx1) y = 0;
decltype((vx1)) z = x1;
//Question: What are the types of the above variables (i.e. x, x1, x2, vx, vx1, y, z)?
//Does line3 crash?  Why? How aoubt line6?

//2. Write code to verify std::forward's role: move rvalue and copy lvaue. 
//You can output some  information to verify.

//3. Know when to use std::move
/*You may already have known that std::move is just used to do static_cast, 
so you can directly use static_cast instead if you like.
However, comparing to static_cast, std::move is easy to use, 
besides, its name(i.e. move) can remind us that here move is expected 
(copy should be replaced, or resource is only allowed to be transferred like std::unique_ptr ).
So, if you want to use std::move, actually you want to use move to replace copy,
or to transfer resource, do you think so? 
But for replacing copy, in some cases, std::move may be misused because copy did not happen.
On the contrary, you added the run time cost for using std::move.
Can you give one or more examples? */

//4. Unserstand special member function generation
//special_member_func_gen
#include <iostream>
#include <utility>
#include <vector>
 
using namespace std;
class TestCtor
{
public:
    TestCtor() { cout << "TestCtor():" << this << endl;}
    TestCtor(const TestCtor &rhv) 
        { cout << "TestCtor(const TestCtor &):" << this << ", rhv=" << &rhv << endl;}
    TestCtor(TestCtor&& rhv) 
        { cout << "TestCtor(TestCtor&&):" << this << ", rhv=" << &rhv << endl;}
    TestCtor& operator=(const TestCtor &rhv) 
        { cout << "TestCtor& operator=(const TestCtor &):" << this << ", rhv " << &rhv << endl; return *this;}
    TestCtor& operator=(TestCtor &&rhv) 
        { cout << "TestCtor& operator=(TestCtor &&):" << this << ",rhv=" << &rhv << endl; return *this;}
    ~TestCtor() { cout << "~TestCtor():" << this << endl;}
};
 
class MyClass 
{
public:
    TestCtor tc_;
};
 
int main()
{
    vector<MyClass> mcs;
    MyClass mc;
    mcs.push_back(std::move(mc));//which constructor is callled
    return 0;
}
// Consider the above code, do you think which constructor is callled when executing line27, 
// "copy constructor" or "move constructor"?
// If we add some constructors like below, do you think how the result changes? 
//What can we learn from it?
//add_constructors
class MyClass 
{
public:
    MyClass() = default;
    MyClass(const MyClass &) = default;
    TestCtor tc_;
};

// 5. Is it possible that pass-by-value may be a good solution when moving is introduced?  
//verison1
class Widget {
public:
    void addName(const std::string& newName) // take lvalue;
    { 
        names.push_back(newName); // copy it
    }
 
    void addName(std::string&& newName) // take rvalue;
    { 
        names.push_back(std::move(newName)); // move it;
    }
private:
    std::vector<std::string> names;
};
//The above code named "version1" includes two functions that do essentially the same thing.
//Code smell: duplicate code. https://stackoverflow.com/questions/2298272/how-much-duplicated-code-do-you-tolerate

//verison2
class Widget {
public:
    template<typename T> // take lvalues
    void addName(T&& newName) // and rvalues;
    {    // copy lvalues, move rvalues;
        names.push_back(std::forward<T>(newName));
    }
private:
    std::vector<std::string> names;
};
//The above code named "version2" only defines one function, but as a function template,
//addName’s implementation must typically be in a header file.

//verison3
class Widget {
public:
    void addName(std::string newName)
    {
        //newName is a completely independent object, so changing newName won’t affect callers
        // besides, this is the final use of newName, so moving from it won’t have any impact on the rest of the function
        names.push_back(std::move(newName));
    }
private:
    std::vector<std::string> names;
};
//The above code named "version3"  also defines only one function, however, 
//it uses pass-by-value, which is not recommended(see Item20 of "Effective C++").
//Now we analyse the cost of the above versions. Consider the code below:
//User Code
Widget w;
//…
std::string name("Bart");
w.addName(name); // call addName with lvalue
//…
w.addName(name + "Jenne"); // call addName with rvalue
//The cost to call addName()
//version1 
//addName(name)
//one copy (i.e.names.push_back(name)) (note: for passing parameters to addName, 
//here newName is pass-by-reference-to-const, so no cost.
//if pass-by-value, the cost is one copy, we need to consider this cost if happened.)
//addName(name + "Jenne")
//one move (i.e. names.push_back(std::move()))
//(note: for passing parameters to addName, here we don't consider the cost of name + "Jenne")
//version2 ditto ditto
//Question: What is the cost of version3?  What conclusions can you draw?

//Bonus questions:
//6. Write a container to make "for(const auto && element: container) {}" run
//7. Write a class template, which can be used to check if a type is a pointer to a class derived from a certain base class.
//Take the code below for example, assumed the class template is "IsPointerToTypeDerivedFromMyBase" , and we can get the value in a similar way like this : IsPointerToTypeDerivedFromMyBase<T*>::Value.
//Question: How to implement "IsPointerToTypeDerivedFromMyBase" ?

//trait
class MyBase:{};
class MyDerived : public MyBase{};
class MyClass {};
template <typename T>
void f ()
{
    std::cout << IsPointerToTypeDerivedFromMyBase<T*>::Value << std::endl;
}
f<MyDerived>(); // output 1
f<MyClass>();   // output 0