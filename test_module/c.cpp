#include <cstdio>
#include "a.h"

Test tt;
extern "C" {

void dll_func()
{
    foo_class::foo.m += 100;
    tt.a = 33;
    printf("c.cpp: tt.a = 0x%llx, tt.a = %d\n", &tt.a, tt.a);
    printf("c.cpp: &foo_class::foo = 0x%llx, foo_class::foo.m = %d\n", &foo_class::foo, foo_class::foo.m);
}

}
