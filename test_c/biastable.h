#include<stdio.h>
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

double values1[9] = {
    11, 12, 13,
    14, 15, 16,
    17, 18, 19
};
double values2[9] = {
    21, 22, 23,
    24, 25, 26,
    27, 28, 29
};
double values3[9] = {
    31, 32, 43,
    34, 35, 46,
    37, 38, 49
};
    
double *values[3] = {values1, values2, values3};

const int interpolation_size = 8;
int interpolation[interpolation_size][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
};


const int TABLE_NUMBERS = 2;
const int TABLE_SIZE = 3;
double T1D[TABLE_NUMBERS][TABLE_SIZE] = {
    {11, 15, 18},
    {12, 16, 19}
};
double T2D[TABLE_NUMBERS][TABLE_SIZE] = {
    {21, 25, 28},
    {22, 26, 29}
};
double T3D[TABLE_NUMBERS][TABLE_SIZE] = {
    {31, 35, 38},
    {32, 36, 39}
};

const int CASE_SIZE = 2;
const double testdata[TABLE_NUMBERS][interpolation_size][CASE_SIZE][4] = {
    ////////////////////TABLE_NUMBERS 0
    {
    {{13, 26.5, 36.5, 24}, //000
    {00, 00, 00, 00}},

    {{13, 26.5, 36.5, 29}, //001
    {00, 00, 00, 00}},

    {{13, 26.5, 36.5, 24.5}, //010
    {00, 00, 00, 00}},

    {{13, 26.5, 36.5, 26}, //011
    {00, 00, 00, 00}},

    {{13, 26.5, 36.5, 25.5}, //100
    {00, 00, 00, 00}},

    {{13, 26.5, 36.5, 30.5}, //101
    {00, 00, 00, 00}},

    {{13, 26.5, 36.5, 29.5}, //110
    {00, 00, 00, 00}},

    {{13, 26.5, 36.5, 31}, //111
    {00, 00, 00, 00}},
    },
    ////////////////////TABLE_NUMBERS 1
    {
    {{15, 25, 36, 20}, //000
    {15, 25, 36, 20}},
    
    {{15, 25, 36, 20}, //001
    {15, 25, 36, 20}},
    
    {{15, 25, 36, 20}, //010
    {15, 25, 36, 20}},
    
    {{15, 25, 36, 20}, //011
    {15, 25, 36, 20}},
    
    {{15, 25, 36, 20}, //100
    {15, 25, 36, 20}},
    
    {{15, 25, 36, 20}, //101
    {15, 25, 36, 20}},
    
    {{15, 25, 36, 20}, //110
    {15, 25, 36, 20}},
    
    {{15, 25, 36, 20}, //111
    {15, 25, 36, 20}}
    }
};

