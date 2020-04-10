#include"biasTable.h"
/*
Use function: F(x, y)=a*x+b to match
F(x[0])=v[0]
F(x[1])=v[1]

Return: F(x0)
*/
static double tbx1DInterpolation(double x[2], double v[2], double x0)
{
    if (TBX_EQ(v[0], v[1])) {
        return v[0];
    }
    if (TBX_EQ(x[0], x[1])) {
        printf("tbx1DInterpolation can not handle this case!\n");
    }
    double a = v[1] - v[0];
    double b = v[0] * x[1] - v[1] * x[0];
    double ret = a * x0 + b;
    ret /= (x[1] - x[0]);

    return ret;
}

/*
Use function: F(x, y)=a*x*y+b*x+c*y+d to match
F(x[0], y[0])=v[0][0]
F(x[0], y[1])=v[0][1]
F(x[1], y[0])=v[1][0]
F(x[1], y[1])=v[1][1]

Return: F(x0, y0)
*/
double tbx2DInterpolation(double x[2], double y[2], double v[2][2], double x0, double y0)
{
    if (TBX_EQ(x[0], x[1])) {
        if (TBX_EQ(v[0][0], v[1][0]) && TBX_EQ(v[0][1], v[1][1])) {
            double temp[2] = {v[0][0], v[0][1]};
            return tbx1DInterpolation(y, temp, y0);
        } else {
            printf("tbx2DInterpolation can not handle this case!\n");
        }
    }
    if (TBX_EQ(y[0], y[1])) {
        if (TBX_EQ(v[0][0], v[0][1]) && TBX_EQ(v[1][0], v[1][1])) {
            double temp[2] = {v[0][0], v[1][0]};
            return tbx1DInterpolation(x, temp, x0);
        }else{
            printf("tbx2DInterpolation can not handle this case!\n");
        }
    }

    if (TBX_EQ(x0, x[0]) && TBX_EQ(v[0][0], v[0][1])) {
        return v[0][0];
    }
    if (TBX_EQ(x0, x[1]) && TBX_EQ(v[1][0], v[1][1])) {
        return v[1][0];
    }
    if (TBX_EQ(y0, y[0]) && TBX_EQ(v[0][0], v[1][0])) {
        return v[0][0];
    }
    if (TBX_EQ(y0, y[1]) && TBX_EQ(v[0][1], v[1][1])) {
        return v[0][1];
    }

    double a = v[0][0] - v[0][1] - v[1][0] + v[1][1];
    double b = (v[1][0] - v[0][0]) * y[1] - (v[1][1] - v[0][1]) * y[0];
    double c = (v[0][1] - v[0][0]) * x[1]-(v[1][1] - v[1][0]) * x[0];
    double d = x[1] * (y[1] * v[0][0] - y[0] * v[0][1]) - x[0] * (y[1]*v[1][0] - y[0] * v[1][1]);
    double ret = (a * y0 + b) * x0 + c * y0 + d;
    ret /= ((x[1] - x[0]) * (y[1] - y[0]));

    return ret;
}

/********************************************************************
 *
 * tbxSearchTable
 *
 *  function:
 *      binary search a table content based on input key
 *                  
 *  return code:
 *      lower bound of table index
 *      -1: table is NULL
 *
 **********************************************************************/
int tbxSearchTable(
        double *d,      /* input: table pointer */
        int nmemb,      /* input: # of entries in table */
        double key,     /* input: key to be compared */
        int if_ceil     /* input: if (!if_ceil) --> use ">" */
)
{   
    int high = nmemb, low = -1;
    if (!d) {
        return low;
    }
    while(high - low > 1) {
        int probe = (high + low) / 2;
        if (!if_ceil) {
            if (d[probe] > key) {
                high = probe;
            } else {
                low = probe;
            }
        } else {
            if (d[probe] >= key) {
                high = probe;
            } else {
                low = probe;
            }
        }
    }
    return low;
}

/******************************************************************
 * 
 * tbxCalBias
 *
 * Compute bias from widthTable/spaceTable and biasTable
 * 
 * Return  bias value
 *******************************************************************/
double tbxCalBias(
        double space,                /* IN: space        */
        double width,                /* IN: width        */
        int doInterpolation,    /* IN: 1:do interpolation */
        double *widthTable,          /* IN: widthTable */
        int nWidth,                  /* IN: widthTable width size */
        double *spaceTable,          /* IN: spaceTable */
        int nSpace,                  /* IN: spaceTable width size */
        double *biasTable            /* IN: biasTable */
)
{
    double bias = 0;
    if (!biasTable || !spaceTable || !widthTable) {
        return bias;
    }
    if (2 == doInterpolation){
        int wi = tbxSearchTable(widthTable, nWidth, width, 0);
        int si = tbxSearchTable(spaceTable, nSpace, space, 0);
        if (wi < 0 || si < 0){
          bias = 0;
        } else {
          int nwi = TBX_MIN(wi + 1, nWidth - 1);
          int nsi = TBX_MIN(si + 1, nSpace - 1);
          double x[2] = {spaceTable[si], spaceTable[nsi]};
          double y[2] = {widthTable[wi], widthTable[nwi]};
          double v[2][2] = {{biasTable[si * nWidth + wi], biasTable[si * nWidth + nwi]}, 
                            {biasTable[nsi * nWidth + wi], biasTable[nsi * nWidth + nwi]}};
          bias = tbx2DInterpolation(x, y, v, space, width);
        }
    } else {
        int if_ceil = 0;
        int wi = tbxSearchTable(widthTable, nWidth, width, if_ceil);
        if (wi >= nWidth) { wi = nWidth-1; }
        int si = tbxSearchTable(spaceTable, nSpace, space, if_ceil);
        if (wi == -1) {
          bias = 0;
        } else if (si == -1) {
          bias = 0;
        } else if (si >= nSpace - 1) {  /* no interpolation */
          si = nSpace - 1;
          bias = biasTable[si * nWidth + wi];
        } else if (si >= 0 && si < nSpace-1) {
          if (doInterpolation == 1) {
            double bias1 = biasTable[si * nWidth + wi];
            double bias2 = biasTable[(si + 1) * nWidth + wi];
            double t = (space - spaceTable[si]) / (spaceTable[si + 1] - spaceTable[si]);
            bias = bias1 * (1 - t) + bias2 * t;
          } else {
            bias = biasTable[si * nWidth + wi];
          }
        }
    }
    return bias;
}

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

int main()
{
    int len[3] = {3, 3, 3};
    double *table3D[3];
    //for (int i = 0; i < TABLE_NUMBERS; ++i) {
    for (int i = 0; i < 1; ++i) {
        table3D[0] = T1D[i];
        table3D[1] = T2D[i];
        table3D[2] = T3D[i];
        for (int j = 0; j < CASE_SIZE; ++j) {
            double x = testdata[i][0][j][0];
            double y = testdata[i][0][j][1];
            double z = testdata[i][0][j][2];
            printf("(x, y, z) = (%f, %f, %f)\n", x, y, z);
            for (int k = 0; k < interpolation_size; ++k) {
                x = testdata[i][k][j][0];
                y = testdata[i][k][j][1];
                z = testdata[i][k][j][2];
                double r = testdata[i][k][j][3];
                double **biasTable = values;
                double ret = tbxCalValueBy3DTable(x, y, z, interpolation[i], table3D, len, biasTable);
                if (TBX_NE(ret, r)) {
                    printf("error : (i, j, k) = (%d, %d, %d), r = %f, ret = %f\n", i, j, k, r, ret);
                }
            }
            printf("-----------------------\n");
        }
        printf("=======================\n");
    }
}
