#include<stdio.h>
#include"tool.h"
#ifndef __INTP2D_H_
#define __INTP2D_H_

double tbxCalValueBy2DTable(
        double x, double y,
        int *doInterpolation,
        double *table2D[2], int len[2],
        double *valueTable
);
int test_2D();

#endif
