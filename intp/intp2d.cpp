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

const int interpolation_2d_size = 8;
int interpolation_2d[interpolation_2d_size][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
};


const int TABLE_2d_NUMBERS = 2;
const int TABLE_2d_SIZE = 3;
double T1D_2d[TABLE_2d_NUMBERS][TABLE_2d_SIZE] = {
    {11, 15, 18},
    {12, 16, 19}
};
double T2D_2d[TABLE_2d_NUMBERS][TABLE_2d_SIZE] = {
    {21, 25, 28},
    {22, 26, 29}
};
double T3D_2d[TABLE_2d_NUMBERS][TABLE_2d_SIZE] = {
    {31, 35, 38},
    {32, 36, 39}
};

const int CASE_2d_SIZE = 2;
const double testdata_2d[TABLE_2d_NUMBERS][interpolation_2d_size][CASE_2d_SIZE][4] = {
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

/******************************************************************
 * 
 * tbxCalValueBy2DTable
 *
 * Compute value from table2D and valueTable
 * 
 * Return value
 *******************************************************************/
double tbxCalValueBy2DTable(
        double x, double y,
        int *doInterpolation,
        double *table2D[2], int len[2],
        double *valueTable
)
{
    double bias = 0;
    if (!valueTable || !table2D[1] || !table2D[0]) {
        return bias;
    }
    int wi = tbxSearchTable(table2D[0], len[0], x, 0);
    if (wi < 0) {
        return bias;
    }
    int si = tbxSearchTable(table2D[1], len[1], y, 0);
    if (si < 0) {
        return bias;
    }
    if (1 == doInterpolation[0] && 1 == doInterpolation[1]) {
        int nwi = TBX_MIN(wi + 1, len[0] - 1);
        int nsi = TBX_MIN(si + 1, len[1] - 1);
        double x_temp[2] = {table2D[1][si], table2D[1][nsi]};
        double y_temp[2] = {table2D[0][wi], table2D[0][nwi]};
        double v[2][2] = {{valueTable[si * len[0] + wi], valueTable[si * len[0] + nwi]}, 
                          {valueTable[nsi * len[0] + wi], valueTable[nsi * len[0] + nwi]}};
        bias = tbx2DInterpolation(x_temp, y_temp, v, y, x);
    } else if (doInterpolation[0] == 1 && wi < len[0] - 1) {
        double bias1 = valueTable[si * len[0] + wi];
        double bias2 = valueTable[si * len[0] + wi + 1];
        double v[2] = {valueTable[si * len[0] + wi], valueTable[si * len[0] + wi + 1]};
        double ret = tbx1DInterpolation(&table2D[0][wi], v, x);
        double t = (y - table2D[1][si]) / (table2D[1][si + 1] - table2D[1][si]);
        bias = bias1 * (1 - t) + bias2 * t;
        if(TBX_NE(ret, bias)) {
            printf("ret and bias is not equal.");
        }
    } else if (doInterpolation[1] == 1 && si < len[1] - 1) {
        double bias1 = valueTable[si * len[0] + wi];
        double bias2 = valueTable[(si + 1) * len[0] + wi];
        double t = (y - table2D[1][si]) / (table2D[1][si + 1] - table2D[1][si]);
        bias = bias1 * (1 - t) + bias2 * t;
        double v[2] = {valueTable[si * len[0] + wi], valueTable[(si + 1) * len[0] + wi]};
        double ret = tbx1DInterpolation(&table2D[1][si], v, y);
        if(TBX_NE(ret, bias)) {
            printf("ret and bias is not equal.");
        }
    } else {
        bias = valueTable[si * len[0] + wi];
    }
    return bias;
}

int test_2D()
{
    int len[3] = {3, 3, 3};
    double *table3D[3];
    //for (int i = 0; i < TABLE_NUMBERS; ++i) {
    for (int i = 0; i < 1; ++i) {
        table3D[0] = T1D_2d[i];
        table3D[1] = T2D_2d[i];
        table3D[2] = T3D_2d[i];
        for (int j = 0; j < CASE_2d_SIZE; ++j) {
            double x = testdata_2d[i][0][j][0];
            double y = testdata_2d[i][0][j][1];
            double z = testdata_2d[i][0][j][2];
            printf("(x, y, z) = (%f, %f, %f)\n", x, y, z);
            for (int k = 0; k < interpolation_2d_size; ++k) {
                x = testdata_2d[i][k][j][0];
                y = testdata_2d[i][k][j][1];
                z = testdata_2d[i][k][j][2];
                double r = testdata_2d[i][k][j][3];
                double **biasTable = values_2d;
                double ret = 0;//tbxCalValueBy2DTable(x, y, z, interpolation_2d[i], table3D, len, biasTable);
                if (TBX_NE(ret, r)) {
                    printf("error : (i, j, k) = (%d, %d, %d), r = %f, ret = %f\n", i, j, k, r, ret);
                }
            }
            printf("-----------------------\n");
        }
        printf("=======================\n");
    }
}

