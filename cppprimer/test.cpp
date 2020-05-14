#include<iostream>
#include<vector>
#include<algorithm>
//g++ primer.cpp -g -std=c++11
using namespace std;
void algo()
{
    string ts = "o";//ooooooooooooooooooooooooooooooo";
    ts += ts;
    ts += ts;
    ts += ts;
    ts += ts;
    cout << ts << endl;
    string s1 = "Henno";
    cout << *find(s1.begin(), s1.end(), 'H') << endl;
    cout << count(s1.begin() + 3, s1.end(), 'n') << endl;
    sort(s1.begin(), s1.end());
    cout << s1 << endl;
    string s2 = "n";
    vector<int> v = {2, 3};
    cout << accumulate(v.cbegin(), v.cend(), 3) << endl;;
    vector<string> vs = {s1, s2};
    cout << accumulate(vs.cbegin(), vs.cend(), string("SS")) << endl;;
    cout << equal(s1.cbegin() + 2, s1.cbegin() + 3, s2.cbegin()) << endl;;
    cout << equal(ts.cbegin(), ts.cend(), s2.cbegin()) << endl;;
    fill(s2.begin(), s2.end(), 'N');;
    cout << s2 << endl;
    fill_n(ts.begin(), 4, 'N');;
    cout << ts << endl;
    auto it = back_inserter(ts);
    it = 'I';
    cout << ts << endl;
    int a1[] = {1, 2, 3, 4, 5};
    int a2[sizeof(a1) / sizeof(*a1)];
    int *a2_end = copy(begin(a1), end(a1), a2);
    //int *a2_end = copy(a1, a1 + sizeof(a1), a2);
    cout << a2[1] << " end : " << *(a2_end - 1)<< endl;

}
int main()
{
    algo();
}
