#include "malloc_test.h"
#include "jemalloc_test.h"
#include "myqueue.h"
#include "false_sharing.h"

int main()
{
    false_sharing();
    malloc_test();
    jemalloc_test();
    queue_test();
}
