#include <dlfcn.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>

#include "a.h"

int a = 0;

int main() {
    char* error = NULL;

    foo_class::foo.m += 1000;
    printf("b.cpp: &foo_class::foo = 0x%llx, foo_class::foo.m = %d\n", &foo_class::foo, foo_class::foo.m);
    printf("b.cpp: a = 0x%llx, a = %d\n", &a, a);

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
