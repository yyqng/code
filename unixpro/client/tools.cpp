#include "tools.h"
void printTime(struct timespec start, const char *info)
{
    struct timespec finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << info << " time cost :" << elapsed << endl;
}
