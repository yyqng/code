#include <stdio.h>  
#include <stdint.h>  
#include <stdlib.h>  
#include <math.h>  
#include "gsl_cdf.h"

double erf_test()
{
    double r = erf(1.96*sqrt(1/2.));
    double bottom_tail = gsl_cdf_gaussian_P(-1.96, 1);
    printf("Area between [-1.96, 1.96]: %g\n", 1-2*bottom_tail);
    double ret = r + 1.0;
    return ret;
}

//reps=10 msg="Ha" ./test
void print_env()
{
    char *repstext = getenv("reps");
    int reps = repstext ? atoi(repstext) : 2;

    char *msg = getenv("msg");
    if (!msg) {
        msg = "Hello.";
    }

    for (int i=0; i < reps; i++)
        printf("%s\n", msg);
}

int main()
{
    erf_test();
//   print_env();
}
