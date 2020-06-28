#include "false_sharing.h"

/*
False Sharing
False sharing occurs when threads on different processors modify variables that reside on the same cache line. This invalidates the cache line and forces a memory update to maintain cache coherency.

Thread-local storage or local variables can be ruled out as sources of false sharing.

In following case, a and b will false sharing, tr1's i and tr2's i will false sharing.
*/

void printTime(struct timespec start, const char *info)
{
    struct timespec finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << info << " time cost :" << elapsed << endl;
}

int __false_sharing(int64_t &a, int64_t &b)
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
	auto fa = [](int64_t &c) { 
        const int64_t n = 1e8;
        for (int64_t i = 0; i < n; ++i) {
            c++;
        }
	};
	std::thread thread1(fa, std::ref(a));
    thread1.join();
    printTime(start, "Single thread change a 1e8 times, total time cost: ");

    clock_gettime(CLOCK_MONOTONIC, &start);
	std::thread thread2(fa, std::ref(b));
    thread2.join();
    printTime(start, "Single thread change b 1e8 times, total time cost: ");

    clock_gettime(CLOCK_MONOTONIC, &start);
	std::thread thread4(fa, std::ref(a));
	std::thread thread3(fa, std::ref(b));
    thread3.join();
    thread4.join();
    printTime(start, "Two threads change ab 1e8 times at the same time. Total time cost: ");
    return 0;
}

int false_sharing()
{
    int64_t a[2] = {0};
    cout << "Before fix false sharing problem:" << endl;
    __false_sharing(a[0], a[1]);
    cout << "After fix false sharing problem:" << endl;
    int64_t b[64] = {0};
    __false_sharing(b[0], b[63]);
    return 0;
}
//change  a. time cost :0.251094
//change  b. time cost :0.247693
//change ab. time cost :0.538793
//After fix
//change  a. time cost :0.249504
//change  b. time cost :0.249257
//change ab. time cost :0.256371
