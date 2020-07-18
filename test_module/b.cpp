#include <dlfcn.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>

#include "a.h"

Test tt;

typedef struct __t {
    const int a = 5;
    const int b = 3;
}T;

int main() {
    *(float *) 0x7fffe910609c = 1;
    printf("b.cpp: *(float *) 0x7fffe910609c = %f\n", *(float *) 0x7fffe910609c);
    T tt1;
    printf("b.cpp: tt1.a = %d, tt1.b = %d\n", tt1.a, tt1.b);
    char* error = NULL;

    foo_class::foo.m += 1000;
    tt.a = 22;
    printf("b.cpp: tt.a = 0x%llx, tt.a = %d\n", &tt.a, tt.a);
    printf("b.cpp: &foo_class::foo = 0x%llx, foo_class::foo.m = %d\n", &foo_class::foo, foo_class::foo.m);

    void* handle = dlopen("lib_c.so", RTLD_LAZY);
    if (!handle) {
        fprintf( stderr, "[%s](%d) dlopen get error: %s\n", __FILE__, __LINE__, dlerror() );
        exit( EXIT_FAILURE );
    }
    dlerror();
    void (*dll_func)() = NULL;
    *(void **) (&dll_func) = dlsym(handle, "dll_func");
    if ((error = dlerror()) != NULL)  {
        dlclose(handle);
        fprintf(stderr, "%s\n", error);
        return -2;
    }

    (*dll_func)();

    dlclose(handle);

    return 0;
}
