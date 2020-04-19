#include <iostream>
#include <utility>
#include <vector>
#include <stdio.h>
using namespace std;
//Moving to C++ 11
//1. Type deduction
//Type deduction
int* getValue()
{
    return nullptr;
}

/*
template<typename T>
void func(T& param) {
    cout << "传入的是左值" << endl;
}*/

template<typename T>
void func(T&& param) {
    cout << "传入的是右值" << endl;
}

void test11()
{
    double *df;
    auto p1 = getValue();    //p1: int *
    auto *p2 = getValue();   //p2: int
    auto x = 27;             //x:  int
    auto y {27};             //y:  std::initializer_list<int>
    const auto cx = x;       //cx: const int
    const auto& rx = x;      //rx: const int&
    auto&& uref1 = x;        //uref1: int
    auto&& uref2 = cx;       //uref1: int
    auto&& uref3 = 27;       //uref1: int

    func(x);
    func(uref2);
    func(uref3);
    //printf("&x = %0x  &uref1 = %0x \n", &x,  &uref1);
    //printf("&cx = %0x &uref2 = %0x \n", &cx, &uref2);
    //printf("          &uref3 = %0x \n",      &uref3);
}
//Question: What are the types of the above variables (i.e. p1, p2, x, y, ....)?
//Does "auto&&" mean a universal reference?
//Yes

//decltype
void test12()
{
    double *df = NULL;
    vector<int> v = {1, 2, 3};
    const vector<int> &rv = v;
    decltype(rv[0]) x = 0;     //x:   Const int.
    auto x1 = 0;               //x1:  int
    decltype(v[0]) x2 = x1;    //x2:  int
    auto vx = rv[0];           //vx:  int. Crash if v is empty.
    v.push_back(1);
    auto vx1 = rv[0];          //vx1: int.
    decltype(vx1) y = 0;       //y:   int.
    decltype((vx1)) z = x1;    //z:   int.
}
//Question: What are the types of the above variables (i.e. x, x1, x2, vx, vx1, y, z)?
//Does line3 crash?  Why? How aoubt line6?
//line3 crash if v is empty. Same as line3.

//2. Write code to verify std::forward's role: move rvalue and copy lvaue. 
//You can output some  information to verify.
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <memory>
using namespace std;

struct A
{
    A(int&& n) { cout << "rvalue overload, n=" << n << endl; }
    A(int& n) { cout << "lvalue overload, n=" << n << endl; }
};

class B
{
public:
    template<class T1, class T2, class T3>
    B(T1 && t1, T2 && t2, T3 && t3) : 
        a1_(std::forward<T1>(t1)), a2_(std::forward<T2>(t2)), a3_(std::forward<T3>(t3)) {}
private:
    A a1_, a2_, a3_;
};

template <class T, class U> std::unique_ptr<T> make_unique1(U&& u) {
    //return std::unique_ptr<T>(new T(std::forward<U>(u)));
    return std::unique_ptr<T>(new T(std::move(u)));
}

template <class T, class... U> std::unique_ptr<T> make_unique(U&&... u) {
    //return std::unique_ptr<T>(new T(std::forward<U>(u)...));
    return std::unique_ptr<T>(new T(std::move(u)...));
}

int test2()
{
    auto p1 = make_unique1<A>(2);
    int i = 10;
    auto p2 = make_unique1<A>(i);
    int j = 100;
    auto p3 = make_unique<B>(i, 2, j);
    return 0;
}


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
int test3()
{
    string s0 = "the content";
    string s1 = s0;         //cpoy
    string s2 = move(s0);  //s is empty and should not be used any more.
}

//4. Unserstand special member function generation
//special_member_func_gen
 
using namespace std;
class TestCtor
{
public:
    TestCtor() { cout << "TestCtor():" << this << endl; }
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
 
class MyClass1 
{
public:
    TestCtor tc_;
};
 
int test41()
{
    vector<MyClass1> mcs;
    MyClass1 mc;                  //TestCtor() is called
    mcs.push_back(std::move(mc)); //TestCtor(TestCtor&&) is callled
    return 0;
}
// Consider the above code, do you think which constructor is callled when executing line27, 
// "copy constructor" or "move constructor"?
// If we add some constructors like below, do you think how the result changes? 
//What can we learn from it?
//add_constructors
class MyClass2 
{
public:
    MyClass2() = default;
    MyClass2(const MyClass2 &) = default;
    TestCtor tc_;
};
 
int test42()
{
    vector<MyClass2> mcs;
    MyClass2 mc;                   //TestCtor() is called
    mcs.push_back(std::move(mc)); //TestCtor(const TestCtor &) is callled
    return 0;
}

// 5. Is it possible that pass-by-value may be a good solution when moving is introduced?  
//verison1
class Widget1 {
public:
    void addName(const std::string& newName) // take lvalue;
    { 
        names.push_back(newName); // copy it
        cout << "Widget1 addName(const std::string& newName). names = " << names[names.size() - 1] << endl;
    }
 
    void addName(std::string&& newName) // take rvalue;
    { 
        names.push_back(std::move(newName)); // move it;
        cout << "Widget1 addName(std::string&& newName). names = " << names[names.size() - 1] << endl;
    }
private:
    std::vector<std::string> names;
};
//The above code named "version1" includes two functions that do essentially the same thing.
//Code smell: duplicate code. https://stackoverflow.com/questions/2298272/how-much-duplicated-code-do-you-tolerate

//verison2
class Widget2 {
public:
    template<typename T> // take lvalues
    void addName(T&& newName) // and rvalues;
    {    // copy lvalues, move rvalues;
        names.push_back(std::forward<T>(newName));
        cout << "Widget2: addName(T&& newName) names = " << names[names.size() - 1] << endl;
    }
private:
    std::vector<std::string> names;
};
//The above code named "version2" only defines one function, but as a function template,
//addName’s implementation must typically be in a header file.

//verison3
class Widget3 {
public:
    void addName(std::string newName)
    {
        //newName is a completely independent object, so changing newName won’t affect callers
        // besides, this is the final use of newName, so moving from it won’t have any impact on the rest of the function
        names.push_back(std::move(newName));
        cout << "Widget3: addName(std::string newName) names = " << names[names.size() - 1] << endl;
    }
private:
    std::vector<std::string> names;
};
//The above code named "version3"  also defines only one function, however, 
//it uses pass-by-value, which is not recommended(see Item20 of "Effective C++").
//Now we analyse the cost of the above versions. Consider the code below:
//User Code
int test5()
{
    Widget1 w1;
    //…
    std::string name1("Bart1");
    w1.addName(name1);           // call addName with lvalue
    //…
    w1.addName(name1 + "Jenne1"); // call addName with rvalue

    Widget2 w2;
    //…
    std::string name2("Bart2");
    w2.addName(name2);           // call addName with lvalue
    //…
    w2.addName(name2 + "Jenne2"); // call addName with rvalue

    Widget3 w3;
    //…
    std::string name3("Bart3");
    w3.addName(name3);           // call addName with lvalue
    //…
    w3.addName(name1 + "Jenne3"); // call addName with rvalue
}
//The cost to call addName()
//version1 
// addName(name)
//  one copy (i.e.names.push_back(name)) (note: for passing parameters to addName, 
//  here newName is pass-by-reference-to-const, so no cost.
//  if pass-by-value, the cost is one copy, we need to consider this cost if happened.)
// addName(name + "Jenne")
//  one move (i.e. names.push_back(std::move()))
//  (note: for passing parameters to addName, here we don't consider the cost of name + "Jenne")
//version2 ditto ditto
//Question: What is the cost of version3?  What conclusions can you draw?

//Bonus questions:
//6. Write a container to make "for(const auto && element: container) {}" run
//7. Write a class template, which can be used to check if a type is a pointer
//  to a class derived from a certain base class.
//  Take the code below for example, assumed the class template is "IsPointerToTypeDerivedFromMyBase" , 
//  and we can get the value in a similar way like this : IsPointerToTypeDerivedFromMyBase<T*>::Value.
//  Question: How to implement "IsPointerToTypeDerivedFromMyBase" ?

//trait
class MyBase{};
class MyDerived : public MyBase{};
class MyClass3 {};
template <typename T>
void f ()
{
    //std::cout << IsPointerToTypeDerivedFromMyBase<T*>::Value << std::endl;
}
int test7()
{
    f<MyDerived>(); // output 1
    f<MyClass3>();   // output 0
}
int main()
{
    //test11();
    //test12();
    //test2();
    //test3();
    //test41();
    //test42();
    test5();
    return 0;
}

