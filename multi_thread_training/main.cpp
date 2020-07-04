#include "allocate_test.h"
#include "queue.h"
#include "false_sharing.h"
#include "ring_buffer.h"

int main()
{
    false_sharing();
    printf("\n\n");
    allocate_test();
    printf("\n\n");
    queue_test();
}

