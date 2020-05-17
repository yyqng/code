#include"test.h"

bool isShorter(string const &s1, string const &s2)
{
    return s1.size() < s2.size();
}

bool check_n(int const&i, int top)
{
    return i > top;
}

void algo()
{
    ostream_iterator<int> out_iter(cout, " ");
    //ifstream inf("a.txt");
    //istream_iterator<string> init_str(inf);
    vector<int> vec2{1, 5, 3, 7};
    copy(vec2.begin(), vec2.end(), out_iter);
    cout << endl;
    char a[] = {'\0', '\0', '\0'};
    cout << sizeof(a) <<  endl;
    cout << strlen(a) <<  endl;
}

int main()
{
    algo();
    otst();
}
