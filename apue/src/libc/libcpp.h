#include <iostream>
using namespace std;

template <class T> void myswap (T& a, T& b)
{
    T c(std::move(a)); a=std::move(b); b=std::move(c);
}

template <class T, size_t N> void myswap (T a[N], T b[N])
{
    for (size_t i = 0; i<N; ++i) myswap (a[i],b[i]);
}

void libcpptest();
