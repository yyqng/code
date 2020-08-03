#include "main.h"
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

#define pi 3.141
#include <unistd.h>
void int64_print_test()
{
//    int64_t x = 888;
//    int64_t y = 999;
//    printf("x=%d, y=%d\n", x, y);
    printf("pi = %f\n", pi);
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
    printf("OPC5556 = 1, VV_SNAPC_SP(%f, %f) = %d\n", p, q, grid);
    q = VV_SNAPC_DP(p, grid);
    printf("OPC5556 = 0, VV_SNAPC_DP(%f, %f) = %d\n", p, q, grid);

    p = 28;
    q = VV_SNAPC_SP(p, grid);
    printf("OPC5556 = 1, VV_SNAPC_SP(%f, %f) = %d\n", p, q, grid);
    q = VV_SNAPC_DP(p, grid);
    printf("OPC5556 = 0, VV_SNAPC_DP(%f, %f) = %d\n", p, q, grid);

    p = 29;
    q = VV_SNAPC_SP(p, grid);
    printf("OPC5556 = 1, VV_SNAPC_SP(%f, %f) = %d\n", p, q, grid);
    q = VV_SNAPC_DP(p, grid);
    printf("OPC5556 = 0, VV_SNAPC_DP(%f, %f) = %d\n", p, q, grid);

    p = 30;
    q = VV_SNAPC_SP(p, grid);
    printf("OPC5556 = 1, VV_SNAPC_SP(%f, %f) = %d\n", p, q, grid);
    q = VV_SNAPC_DP(p, grid);
    printf("OPC5556 = 0, VV_SNAPC_DP(%f, %f) = %d\n", p, q, grid);

    p = 50;
    q = VV_SNAPC_SP(p, grid);
    printf("OPC5556 = 1, VV_SNAPC_SP(%f, %f) = %dn", p, q, grid);
    q = VV_SNAPC_DP(p, grid);
    printf("OPC5556 = 0, VV_SNAPC_DP(%f, %f) = %d\n", p, q, grid);

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


typedef struct dt_vtx_s {
    int32_t utag;           /* user segment tag                     */
    int32_t ugrp;           /* user segment group                   */
    uint64_t uflag;         /* user level segment bit flag          */
    uint32_t dir : 5;       /* 0-16                                 */
    uint32_t snapup : 1;    /* specify way to round                 */
    uint32_t shadow : 1;    /* showdowed: projection dissection     */
    uint32_t skip : 1;      /* skipped: projection dissection       */
    uint32_t stitch : 1;    /* stitch segment flag                  */
    uint32_t ignore : 1;    /* segment ignored in exec segment func */
    uint32_t done : 1;      /* temporary flag                       */
    uint32_t remove : 1;    /* persistence flag, vtx removed        */
    uint32_t layer : 8;     /* layer number                         */
    uint32_t ftype : 3;     /* graphics type                        */
    uint32_t head : 1;      /* Used in C2C, head is wanted corner   */
    uint32_t tail : 1;      /* Used in C2C, tail is wanted corner   */
    uint32_t corseg : 1;    /* 1: segment is in a->tgraphics        */
    uint32_t collinear : 1; /* used in DT.position, mark if it is the collinear edge*/
    uint32_t fixn45 : 1;    /* used in fixn45 segment               */
    uint32_t del_sbar : 1;  /* used in split sbar                   */
    uint32_t model_retarget : 1;
    uint32_t prio_correct : 1; /* edge from previous correction or manually corrected,
                                  convert to ingore so that no touch in next corrects */
    uint32_t tmp : 1;          /* tmp storage per vertext */
    /* end of 32 */
    uint32_t patch : 6;        /* patch bbox classification            */
    uint32_t shadow_count : 8; /* pps handling                         */
    uint32_t priority : 14;
    uint32_t pre_prio : 1; /* used in DT.add_context */
    uint32_t drc_ignore : 1;
    uint32_t tmp2 : 2; /* tmp storage per vertext */
    /* end of 32 */
    uint32_t pre_prio_keep : 1; /* used in ebh, recipe indicate if the segment should be kept for next stage/level */
    uint32_t priority_keep : 1; /* used in ebh, binary indicate if the segment should be kept for next stage/level */
    uint32_t prio_healing_keep : 1;  /* used in ebh, indicate if the segment should be kept for repair in the next level */
    uint32_t dummy_dissect : 1; /* used in checker board/hscan, recipe indicate if the segment is just a dummy segment */
    uint32_t prio_healing : 1;
    uint32_t priority1 : 10; /* used in pps, required by TSMC */
    uint32_t priority2 : 10; /* used in pps, required by TSMC */
    uint32_t priority_new : 1;
    uint32_t recover_del : 1;
    uint32_t recover_new : 1;
    uint32_t use2shadow : 1;/* Use 1 to mark the point only used to shadow. Deleted these points after shadow*/
    uint32_t dummy : 3;
} dt_vtx_t;

void structTest()
{
    dt_vtx_t v;
    v.use2shadow = 1;
    printf("v.use2shadow = %d\n", v.use2shadow);
    v.use2shadow = 0;
    printf("v.use2shadow = %d\n", v.use2shadow);
}

enum
{
    RULE_FREEZE_LINE_END,
    RULE_FREEZE_LINE_END_SIDE,
    RULE_FREEZE_OUT_CORNER,
    RULE_FREEZE_SPACE_END,
    RULE_FREEZE_SPACE_END_SIDE,
    RULE_FREEZE_IN_CORNER,
    RULE_FREEZE_Z_SEGMENT,
    RULE_NUMBER_OF_FREEZE_SEGMENT_TYPE
};

void enumTest()
{
    printf("RULE_FREEZE_LINE_END = %d\n", RULE_FREEZE_LINE_END);
    printf("RULE_NUMBER_OF_FREEZE_SEGMENT_TYPE = %d\n", RULE_NUMBER_OF_FREEZE_SEGMENT_TYPE);
}

double *test(double *p)
{
    if(!p) {
        printf("p is null.\n");
    }
    //double *p1 = (double *)malloc(sizeof(double) * 2);
    p = (double *)malloc(sizeof(double) * 2);
    return p;
}

int f(int a)
{
    return 0;
}

int ptrdiff_t_test()
{
    char str[] = "Hello world!";
    char *pstart = str;
    char *pend = str + strlen(str);
    ptrdiff_t difp = pend - pstart;
    printf("%ld\n", difp);
    return 0;
}

int sscanf_test()
{
   int day, year;
   char weekday[20], month[20], dtm[100];

   strcpy( dtm, "Saturday March 25 1989" );
   sscanf( dtm, "%s %s %d  %d", weekday, month, &day, &year );

   printf("%s %d, %d = %s\n", month, day, year, weekday );
    
   return(0);
}

//#define TBX_VERSION_E20_06_0 on  20200600
//#define TBX_VERSION_E20_06_0_1   on  20200724    from    TBX_VERSION_E20_06_0
#define TBX_VERSION_E20_06_0 20200600
int print_test()
{
   float day = 0.111;
   double year = 0.222;
   if (&day == (float *)0x7fffffffdb44) {
       printf("Equal \n");
   }
   printf("%f %f\n", day, year);
   cout << endl;
   cout << TBX_VERSION_E20_06_0 << endl;
    
    int64_t right;
    int64_t left;
    printf("yyy: dt_merge_sbar right = %ld, left = %ld\n", 
            right, left);

   return(0);
}

int main()
{
    //structTest();
//      printf("hi. " "www\n");
//    int64_print_test();
//    lrint_test();
//    SNAP_TEST();
    //long n = Conn(12,4);
    //printf("n=%d\n",n);
    //const char *s1="ab";
    //const char *s2="cd";
    //std::string str = Conn("ab", "cd");
    //char a = ToChar(1);
    //str = ToString(123132);
    //enumTest();
    //test(NULL);
    //wtest();
    //ptrdiff_t_test();
    //const char p[] = "echo \"\" > test.bak";
    //system(p);
    valgrind_test();
    print_test();
    //sscanf_test();
}
