#include<stdio.h>
#include"tool.h"
#ifndef __INTP3D_H_
#define __INTP3D_H_


static double tbxCalValueBy3DTable(
        double x, double y, double z,
        int interpolation[3],
        double *table3D[3], int len[3],
        double **valueTable
);
int test_3D();

#endif