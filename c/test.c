#include <stdio.h>  
#include <stdint.h>  
#include <stdlib.h>  
#include <math.h>  
#include <limits.h>  
#include "gsl_cdf.h"
//c99 -xc - -lm -g -Wall -include stdio.h -O3 << '---' 
//int main(){printf("Hello from the command line.\n");} 
//---
//./a.out

//cat txt |c99 -xc - -lm -g -Wall -include stdio.h -O3
//./a.out

double erf_test()
{
    double r = 0;
    double bottom_tail = 0;
    int count = 1E7;
    while(count > 0) {
        --count;
        r = erf(1.96*sqrt(1/2.));
        bottom_tail = gsl_cdf_gaussian_P(-1.96, 1);
    }
    printf("Area between [-1.96, 1.96]: %g\n", 1-2*bottom_tail);
    double ret = r + 1.0;
    int *p = (int*)malloc(sizeof(int));
    return ret;
    free(p);
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
    double ret = erf_test();
    int *p = (int*)malloc(sizeof(int));
    return ret;
    free(p);
//   print_env();
}
