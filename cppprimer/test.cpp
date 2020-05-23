#include"test.h"
#include<bitset>

bool isShorter(string const &s1, string const &s2)
{
    return s1.size() < s2.size();
}

bool check_n(int const&i, int top)
{
    return i > top;
}

void print()
{
}

void test(int a)
{
    cout << "int" << endl;
}

void test(void *a)
{
    cout << "void*" << endl;
}

template<typename T, typename...Type>
void print(const T &arg1, const Type&...args)
{
    cout << arg1 << endl;
    print(args...);
}

void algo()
{
    vector<int> vec2{1, 5, 3, 7};
    bitset<16>b(377);
    int i1 = 75;
    int i2 = 25;
    print(i1, b, i2);
    test(0);
    //test(NULL);
    test(nullptr);
}

int main()
{
//    algo();
//    otst();
    A oa1(2, 3);
    A oa(oa1);
    cout << oa.a << oa.b << endl;
}
