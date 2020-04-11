#include"intp2d.h"

double values_2d_1[9] = {
    11, 12, 13,
    14, 15, 16,
    17, 18, 19
};
double values_2d_2[9] = {
    21, 22, 23,
    24, 25, 26,
    27, 28, 29
};
double values_2d_3[9] = {
    31, 32, 43,
    34, 35, 46,
    37, 38, 49
};
double *values_2d[3] = {values_2d_1, values_2d_2, values_2d_3};

const int interpolation_2d_size = 4;
int interpolation_2d[interpolation_2d_size][2] = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1}
};

const int TABLE_2d_SIZE = 3;
double T1D_2d[TABLE_2d_SIZE] = { 11, 15, 18};
double T2D_2d[TABLE_2d_SIZE] = {21, 25, 28};

const int CASE_2d_SIZE = 5;
const double testdata_2d[interpolation_2d_size][CASE_2d_SIZE][3] = {
    ////////////////////TABLE_NUMBERS 0
    {{13, 26.5, 14}, //00
    {16.5, 29, 18},
    {19, 26.5, 16},
    {19, 28, 19},
    {11, 20, 0}},

    {{13, 26.5, 15.5}, //01
    {16.5, 29, 18},
    {19, 26.5, 17.5},
    {19, 28, 19},
    {11, 20, 0}},

    {{13, 26.5, 14.5}, //10
    {16.5, 29, 18.5},
    {19, 26.5, 16},
    {19, 28, 19},
    {11, 20, 0}},

    {{13, 26.5, 16}, //11
    {16.5, 29, 18.5},
    {19, 26.5, 17.5},
    {19, 28, 19},
    {11, 20, 0}}
};

/******************************************************************
 * 
 * tbxCalValue2D
 *
 * Input(x, y) corresponding to table and serach result in double *value
 * 
 * Return searching result from double *value
 *******************************************************************/
double tbxCalValue2D(
        double x, double y,
        int *doInterpolation,
        double *table[2], int len[2],
        double *value
)
{
    if (!value || !table[1] || !table[0]) {
        return 0;
    }
    int i1 = tbxSearchTable(table[0], len[0], x, 0);
    int i2 = tbxSearchTable(table[1], len[1], y, 0);
    if (i1 < 0 || i2 < 0) {
        return 0;
    }
    if (1 == doInterpolation[0] && 1 == doInterpolation[1]) {
        int n1 = TBX_MIN(i1 + 1, len[0] - 1);
        int n2 = TBX_MIN(i2 + 1, len[1] - 1);
        double x_temp[2] = {table[1][i2], table[1][n2]};
        double y_temp[2] = {table[0][i1], table[0][n1]};
        double v[2][2] = {{value[i2 * len[0] + i1], value[i2 * len[0] + n1]}, 
                          {value[n2 * len[0] + i1], value[n2 * len[0] + n1]}};
        return tbx2DInterpolation(x_temp, y_temp, v, y, x);
    } else if (doInterpolation[0] == 1 && i1 < len[0] - 1) {
        double v[2] = {value[i2 * len[0] + i1], value[i2 * len[0] + i1 + 1]};
        return tbx1DInterpolation(&table[0][i1], v, x);
    } else if (doInterpolation[1] == 1 && i2 < len[1] - 1) {
        double v[2] = {value[i2 * len[0] + i1], value[(i2 + 1) * len[0] + i1]};
        return tbx1DInterpolation(&table[1][i2], v, y);
    } else {
        return value[i2 * len[0] + i1];
    }
    return 0;
}

int test_2D()
{
    int len[2] = {3, 3};
    double *table2D[2] = {T1D_2d, T2D_2d};
    for (int i = 0; i < CASE_2d_SIZE; ++i) {
        for (int j = 0; j < interpolation_2d_size; ++j) {
            double x = testdata_2d[j][i][0];
            double y = testdata_2d[j][i][1];
            double r = testdata_2d[j][i][2];
            double *biasTable = values_2d[0];
            double ret = tbxCalValue2D(x, y, interpolation_2d[j], table2D, len, biasTable);
            if (TBX_NE(ret, r)) {
                printf("error : (i, j) = (%d, %d), (x, y) = (%f, %f), r = %f, ret = %f\n",
                        i, j, x, y, r, ret);
                return -1;
            } else {
                printf("right : (i, j) = (%d, %d), (x, y) = (%f, %f), r = %f, ret = %f\n",
                        i, j, x, y, r, ret);
            }
        }
        printf("-----------------------\n");
    }
    printf("=======================\n");
    return 0;
}

