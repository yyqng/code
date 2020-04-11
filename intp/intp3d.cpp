#include"intp3d.h"

double values_3d_1[9] = {
    11, 12, 13,
    14, 15, 16,
    17, 18, 19
};
double values_3d_2[9] = {
    21, 22, 23,
    24, 25, 26,
    27, 28, 29
};
double values_3d_3[9] = {
    31, 32, 33,
    34, 35, 36,
    37, 38, 39
};
    
double *values_3d[3] = {values_3d_1, values_3d_2, values_3d_3};

const int interpolation_3d_size = 8;
int interpolation_3d[interpolation_3d_size][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
};


const int TABLE_3d_SIZE = 3;
double T1D_3d[TABLE_3d_SIZE] = {11, 15, 18};
double T2D_3d[TABLE_3d_SIZE] = {21, 25, 28};
double T3D_3d[TABLE_3d_SIZE] = {31, 35, 38};

const int CASE_3d_SIZE = 7;
const double testdata_3d[interpolation_3d_size][CASE_3d_SIZE][4] = {
    {{13, 26.5, 36.5, 24}, //000
    {19, 26.5, 33, 16},
    {19, 26.5, 40, 36},
    {18, 29, 39, 39},
    {10, 20, 30, 0},
    {11, 21, 31, 11},
    {13, 23, 39, 31}},

    {{13, 26.5, 36.5, 29}, //001
    {19, 26.5, 33, 21},
    {19, 26.5, 40, 36},
    {18, 29, 39, 39},
    {10, 20, 30, 0},
    {11, 21, 31, 11},
    {13, 23, 39, 31}},

    {{13, 26.5, 36.5, 25.5}, //010
    {19, 26.5, 33, 17.5},
    {19, 26.5, 40, 37.5},
    {18, 29, 39, 39},
    {10, 20, 30, 0},
    {11, 21, 31, 11},
    {13, 23, 39, 32.5}},

    {{13, 26.5, 36.5, 30.5}, //011
    {19, 26.5, 33, 22.5},
    {19, 26.5, 40, 37.5},
    {18, 29, 39, 39},
    {10, 20, 30, 0},
    {11, 21, 31, 11},
    {13, 23, 39, 32.5}},

    {{13, 26.5, 36.5, 24.5}, //100
    {19, 26.5, 33, 16},
    {19, 26.5, 40, 36},
    {18, 29, 39, 39},
    {10, 20, 30, 0},
    {11, 21, 31, 11},
    {13, 23, 39, 31.5}},

    {{13, 26.5, 36.5, 29.5}, //101
    {19, 26.5, 33, 21},
    {19, 26.5, 40, 36},
    {18, 29, 39, 39},
    {10, 20, 30, 0},
    {11, 21, 31, 11},
    {13, 23, 39, 31.5}},

    {{13, 26.5, 36.5, 26}, //110
    {19, 26.5, 33, 17.5},
    {19, 26.5, 40, 37.5},
    {18, 29, 39, 39},
    {10, 20, 30, 0},
    {11, 21, 31, 11},
    {13, 23, 39, 33}},

    {{13, 26.5, 36.5, 31}, //111
    {19, 26.5, 33, 22.5},
    {19, 26.5, 40, 37.5},
    {18, 29, 39, 39},
    {10, 20, 30, 0},
    {11, 21, 31, 11},
    {13, 23, 39, 33}}
};

double tbxCalValue2D(
        double x, double y,
        int *doInterpolation,
        double *table2D[2], int len[2],
        double *valueTable
);

/******************************************************************
 * 
 * tbxCalValue3D
 *
 * Input(x, y, z) corresponding to table and serach result in double **value
 * 
 * Return searching result from double **value
 *******************************************************************/
double tbxCalValue3D(
        double x, double y, double z,
        int interpolation[3],
        double *table[3], int len[3],
        double **value
)
{
    if (!value || !table[1] || !table[0]) {
        return 0;
    }
    if (!table[2]) {
        return tbxCalValue2D(x, y, &interpolation[0], &table[0], &len[0], value[0]);
    }
    int i3 = tbxSearchTable(table[2], len[2], z, 0);
    if (i3 < 0) {
        return 0;
    } else if (0 == interpolation[2] || i3 >= len[2] -1 ) { /* no interpolation for table[2]*/
        return tbxCalValue2D(x, y, &interpolation[0], &table[0], &len[0], value[i3]);
    } else {
        double v[2] = {tbxCalValue2D(x, y, &interpolation[0], &table[0], &len[0], value[i3]),
                       tbxCalValue2D(x, y, &interpolation[0], &table[0], &len[0], value[i3 + 1])};
        return tbx1DInterpolation(&table[2][i3], v, z);
    }
    return 0;
}

int test_3D()
{
    int len[3] = {3, 3, 3};
    double *table3D[3] = {T1D_3d, T2D_3d, T3D_3d};
    for (int i = 0; i < CASE_3d_SIZE; ++i) {
        for (int j = 0; j < interpolation_3d_size; ++j) {
            double x = testdata_3d[j][i][0];
            double y = testdata_3d[j][i][1];
            double z = testdata_3d[j][i][2];
            double r = testdata_3d[j][i][3];
            double **biasTable = values_3d;
            double ret = tbxCalValue3D(x, y, z, interpolation_3d[j], table3D, len, biasTable);
            if (TBX_NE(ret, r)) {
                printf("error : (i, j) = (%d, %d), (x, y, z) = (%f, %f, %f) r = %f, ret = %f\n",
                        i, j, x, y, z, r, ret);
                return -1;
            } else {
                printf("right : (i, j) = (%d, %d), (x, y, z) = (%f, %f, %f) r = %f, ret = %f\n",
                        i, j, x, y, z, r, ret);
            }
        }
        printf("-----------------------\n");
    }
    printf("=======================\n");
    return 0;
}

