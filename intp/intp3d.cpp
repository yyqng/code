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
    31, 32, 43,
    34, 35, 46,
    37, 38, 49
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


const int TABLE_3d_NUMBERS = 2;
const int TABLE_3d_SIZE = 3;
double T1D_3d[TABLE_3d_NUMBERS][TABLE_3d_SIZE] = {
    {11, 15, 18},
    {12, 16, 19}
};
double T2D_3d[TABLE_3d_NUMBERS][TABLE_3d_SIZE] = {
    {21, 25, 28},
    {22, 26, 29}
};
double T3D_3d[TABLE_3d_NUMBERS][TABLE_3d_SIZE] = {
    {31, 35, 38},
    {32, 36, 39}
};

const int CASE_3d_SIZE = 2;
const double testdata_3d[TABLE_3d_NUMBERS][interpolation_3d_size][CASE_3d_SIZE][4] = {
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
 * tbxCalValueBy3DTable
 *
 * Input(x, y, z) corresponding to table3D and serach value in valueTable
 * 
 * Return searching result from valueTable
 *******************************************************************/
static double tbxCalValueBy3DTable(
        double x, double y, double z,
        int interpolation[3],
        double *table3D[3], int len[3],
        double **valueTable
)
{
    double ret = 0;
    if (!valueTable || !table3D[1] || !table3D[0]) {
        return ret;
    }
    if (!table3D[2]) {
        ret = tbxCalBias(y, z, interpolation[1], table3D[0], len[2], table3D[1], len[1], valueTable[0]);
        return ret;
    }
    int li = tbxSearchTable(table3D[2], len[0], x, 0);
    if (li < 0) {
        return 0;
    } else if (0 == interpolation[0] || li >= len[0] -1 ) { /* no interpolation for lengthTable*/
        ret = tbxCalBias(y, z, interpolation[1], table3D[0], len[2], table3D[1], len[1], valueTable[li]);
        return ret;
    } else {
        double bias1 = tbxCalBias(y, z, interpolation[1], table3D[0], len[2], table3D[1], len[1], valueTable[li]);
        double bias2 = tbxCalBias(y, z, interpolation[1], table3D[0], len[2], table3D[1], len[1], valueTable[li + 1]);
        double slope = (x - table3D[2][li]) / (table3D[2][li + 1] - table3D[2][li]);
        ret = bias1 + (bias2 - bias1) * slope;
    }
    return ret;
}

int test_3D()
{
    int len[3] = {3, 3, 3};
    double *table3D[3];
    //for (int i = 0; i < TABLE_NUMBERS; ++i) {
    for (int i = 0; i < 1; ++i) {
        table3D[0] = T1D_3d[i];
        table3D[1] = T2D_3d[i];
        table3D[2] = T3D_3d[i];
        for (int j = 0; j < CASE_3d_SIZE; ++j) {
            double x = testdata_3d[i][0][j][0];
            double y = testdata_3d[i][0][j][1];
            double z = testdata_3d[i][0][j][2];
            printf("(x, y, z) = (%f, %f, %f)\n", x, y, z);
            for (int k = 0; k < interpolation_3d_size; ++k) {
                x = testdata_3d[i][k][j][0];
                y = testdata_3d[i][k][j][1];
                z = testdata_3d[i][k][j][2];
                double r = testdata_3d[i][k][j][3];
                double **biasTable = values_3d;
                double ret = tbxCalValueBy3DTable(x, y, z, interpolation_3d[i], table3D, len, biasTable);
                if (TBX_NE(ret, r)) {
                    printf("error : (i, j, k) = (%d, %d, %d), r = %f, ret = %f\n", i, j, k, r, ret);
                }
            }
            printf("-----------------------\n");
        }
        printf("=======================\n");
    }
}

