#include "malloc_test.h"
#include "jemalloc_test.h"
#include "queue.h"
#include "false_sharing.h"
#include "ring_buffer.h"

int main()
{
    false_sharing();
    malloc_test();
    jemalloc_test();
    queue_test();
}
