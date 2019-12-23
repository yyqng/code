#include <stdio.h>  
#include <stdint.h>  
#include <math.h>  
//#include <string>
//#include <vector>
#define _Conn_(x,y)  (x##y)
#define Conn(x,y)  _Conn_(x,y)
//#define _Conn_(x,y)  (x##e##y)
//#define Conn(x,y)  _Conn_(x,y)
//#define ToChar(x)  #@x ----------wrong 
#define ToString(x) #x
//using namespace std;
//
//gcc test.c -std=c99 -lm -g

void int64_print_test()
{
    int64_t x = 888;
    int64_t y = 999;
    printf("x=%d, y=%d\n", x, y);
}

void _lrint(int in, int grid)
{
    double i = (double)in / grid;
    double r = (double)lrint(i);
    printf("lrint(%f) = %f\n", i, r);
    //printf("lrint(%f) * grid = %f\n\n", i, r * grid);
}

void _lrint_d(double in, double grid)
{
    double i = in / grid;
    double r = (double)lrint(i);
    printf("lrint(%f) = %f\n", i, r);
    //printf("lrint(%f) * grid = %f\n\n", i, r * grid);
}

void _floor(double in)
{
    double r = (double)floor(in);
    printf("floor(%f) = %f\n", in, r);
}

void lrint_test()
{
    int grid = 20;
    int in = 70;
    _lrint(in, grid);
    in = 10;
    _lrint(in, grid);

    double dgrid = 20;
    double din = 70;
    const double E_10 = 0.0000000001;
    din = 10 + E_10;
    _lrint_d(din, dgrid);
    din = 10 + E_10;
    _lrint_d(din, dgrid);
}

double rint_lrint(double x)
{
    double ret = (double)lrint(x);
    return ret;
}

double rint_nolrint(double x)
{
    double ret = floor(x + 0.5);
    return ret;
}

typedef double (*FunType)(double);
void SNAP(FunType f)
{
//    _floor(63353.500000 + 0.500000);
//    _floor(63600.500000 + 0.500000);

#define VV_SNAP_DOWNSCALE (0.10)
#define VV_SNAP_UPSCALE (10.0)
// int OPC5556 = 1;
#define VV_SNAPC_SP(x, g) ((g)*f((x) / (g)))  
// int OPC5556 = 0;
#define VV_SNAPC_DP(x, g) ((g)*f(VV_SNAP_DOWNSCALE * f(VV_SNAP_UPSCALE * (x) / (g))))
    double q;
    double p = 10;
    int grid = 20;
    q = VV_SNAPC_SP(p, grid);
    printf("OPC5556 = 1, VV_SNAPC_SP(%f, %d) = %f\n", p, q, grid);
    q = VV_SNAPC_DP(p, grid);
    printf("OPC5556 = 0, VV_SNAPC_DP(%f, %d) = %f\n", p, q, grid);

    p = 29;
    q = VV_SNAPC_SP(p, grid);
    printf("OPC5556 = 1, VV_SNAPC_SP(%f, %d) = %f\n", p, q, grid);
    q = VV_SNAPC_DP(p, grid);
    printf("OPC5556 = 0, VV_SNAPC_DP(%f, %d) = %f\n", p, q, grid);

    p = 30;
    q = VV_SNAPC_SP(p, grid);
    printf("OPC5556 = 1, VV_SNAPC_SP(%f, %d) = %f\n", p, q, grid);
    q = VV_SNAPC_DP(p, grid);
    printf("OPC5556 = 0, VV_SNAPC_DP(%f, %d) = %f\n", p, q, grid);

//    p = 14.51;
//    q = f(p);
//    printf("f(%f) = %f\n", p, q);
//    p = 14.5;
//    q = f(p);
//    printf("f(%f) = %f\n", p, q);
}
void SNAP_TEST()
{
    printf("rint_lrint\n");
    SNAP(rint_lrint);
    printf("rint_nolrint\n");
    SNAP(rint_nolrint);
}

int main()
{
//    int64_print_test();
//    lrint_test();
    SNAP_TEST();
    //long n = Conn(12,4);
    //printf("n=%d\n",n);
    //const char *s1="ab";
    //const char *s2="cd";
    //std::string str = Conn("ab", "cd");
    //char a = ToChar(1);
    //str = ToString(123132);
}
