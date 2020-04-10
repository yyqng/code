#include<stdio.h>
#ifndef __TOOL_H_
#define __TOOL_H_

#define TBX_EPSILON (1e-4)
#define DT_MIN(a,b)        ((a) < (b) ? (a) : (b))
#define DT_MAX(a,b)        ((a) >= (b) ? (a) : (b))

#define TBX_MAX(x, y) DT_MAX(x, y)
#define TBX_MIN(x, y) DT_MIN(x, y)
#define TBX_LE( x, y ) (( (x) <= (y) + TBX_EPSILON) ? 1 : 0) 
#define TBX_GE( x, y ) (( (x) >= (y) - TBX_EPSILON ) ? 1 : 0) 
#define TBX_LT( x, y ) (( (x) < (y) - TBX_EPSILON) ? 1 : 0) 
#define TBX_GT( x, y ) (( (x) > (y) + TBX_EPSILON ) ? 1 : 0)
#define TBX_EQ( x, y ) (( (x) <= (y) + TBX_EPSILON && (x) >= (y) - TBX_EPSILON ) ? 1: 0)
#define TBX_NE( x, y ) (( (x) < (y) - TBX_EPSILON || (x) > (y) + TBX_EPSILON ) ? 1: 0)

double tbx1DInterpolation(double x[2], double v[2], double x0);
double tbx2DInterpolation(double x[2], double y[2], double v[2][2], double x0, double y0);
int tbxSearchTable(
        double *d,      /* input: table pointer */
        int nmemb,      /* input: # of entries in table */
        double key,     /* input: key to be compared */
        int if_ceil     /* input: if (!if_ceil) --> use ">" */
);
double tbxCalBias(
        double space,                /* IN: space        */
        double width,                /* IN: width        */
        int doInterpolation,    /* IN: 1:do interpolation */
        double *widthTable,          /* IN: widthTable */
        int nWidth,                  /* IN: widthTable width size */
        double *spaceTable,          /* IN: spaceTable */
        int nSpace,                  /* IN: spaceTable width size */
        double *biasTable            /* IN: biasTable */
);

#endif