#include "a.h"

foo_class foo_class::foo;

foo_class::foo_class() {
    m = 10;
    printf("a.cpp: foo_class::foo_class(), this-> 0x%llx\n", this);
}

foo_class::~foo_class() {
    printf("a.cpp: foo_class::~foo_class(), this-> 0x%llx\n", this);
}
