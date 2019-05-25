#include "smartpointers.h"


void smartpTestint()
{
    std::auto_ptr<int> p1 (new int);
    *p1.get()=10;
    std::auto_ptr<int> p2 (p1);
    // (p1 is now null-pointer auto_ptr)
    std::cout << "p2 points to " << *p2 << '\n';

    std::auto_ptr<A> pA1 (new A);
    pA1.reset (new A);
    auto pA2 = pA1.release(); //仅释放内存所属权，不释放内存
    std::cout << "Befor delete pA2" << '\n';
    delete pA2;
    std::cout << "After delete pA2" << '\n';
}

void smartpboostTest()
{
    //*p.get() = 100;
    //std::cout << "p points to " << *p.get() << '\n';
}

void smartpTest()
{
    smartpTestint();
    smartpboostTest();
}

