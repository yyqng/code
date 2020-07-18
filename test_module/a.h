#include <cstdio>

typedef struct {
    int a;
    int b;
}Test;
extern Test tt;

struct foo_class {
    int m;

    foo_class();
    ~foo_class();

    static foo_class foo;
};
