#include "valgrind.h"

int _valgrind_test0()
{
     cout << "haha,I crash again. Catch me if you can" << endl;
     return 0;
}

int _valgrind_test1()
{
    int len = 10;
    char* pbuf = NULL;
    void* data= NULL;
    pbuf = new char[len]();
    //data = memset(pbuf, 0, len);
    data = pbuf;
    double f = 2.0;
    sscanf((char*)data, "(f = %lf)\n)", &f);
    printf("data = %s\n", (char*)data);
    delete []pbuf;
    return 0;
}

int _valgrind_test3()
{
//    char buf[256] = {0};
    char buf[256];
    buf[255] = 0; // prevent overflow
    double f = 2.0;
    int i = 0;
    i = sscanf(buf, "(f = %lf)\n)", &f);

    FILE* fp = fopen("file_path", "r");
    i = fscanf(fp, "(f = %lf)\n)", &f);
    printf("i = %d, but = %s\n", i, buf);
    printf("&i = %0x\n", &i);
    return 0;

    char str[100] ="123568qwerSDDAE";
    char lowercase[100];
    int num;
    sscanf(str,"%d %[a-z]", &num, lowercase);
    printf("The number is: %d.\n", num);
    printf("The lowercase is: %s.\n", lowercase);
    return 0;
}

typedef struct dt_vtx_s {
    double cv;
    union {
        double dv;
        float ctrl[2];
        int pos[2];
    } u;
} dt_vtx_t;

int dt_ii_get_ctrl_point3(double t)
{
    if (t) {
        printf("t\n");
    } else {
        printf("!t\n");
    }
    return 0;
}

void dt_ptable_copy_marker(dt_vtx_t* v)
{
    dt_ii_get_ctrl_point3(v->u.ctrl[1]);
}

int _valgrind_test4()
{
    dt_vtx_t v;
    //memset(&v, 0, sizeof(dt_vtx_t));
    dt_ptable_copy_marker(&v);
    return 0;
}

int _valgrind_test5()
{
    char buf[256];
    int i = 0;
    printf("&i = 0x%08x\n", &i);
    printf("buf = 0x%08x\n", buf);
    return 0;
}

typedef struct
{
    int x;
    int y;
} Vtx;

#define VV_X(p) ((p)->x)
#define VV_Y(p) ((p)->y)

#define VV_SUB(p, q, v)              \
    {                                \
        VV_X(v) = (p) - (q);         \
        VV_Y(v) = (p) - (q);         \
    }

#define VV_CALCDIR(x, y, dir)                                                                                          \
    {                                                                                                                  \
        if ((y) == 0) {                                                                                                \
            (dir) = ((x) >= 0) ? 0 : 4;                                                                                \
        } else if ((x) == 0) {                                                                                         \
            (dir) = ((y) >= 0) ? 2 : 6;                                                                                \
        } else if ((x) == (y)) {                                                                                       \
            (dir) = ((x) >= 0) ? 1 : 5;                                                                                \
        } else if ((x) == -(y)) {                                                                                      \
            (dir) = ((y) >= 0) ? 3 : 7;                                                                                \
        } else {                                                                                                       \
            (dir) = 16;                                                                                                \
        }                                                                                                              \
    }

int _valgrind_test6()
{
    /* calculate current vertex's direction */
    int p = 10;
    int q = 2;
    Vtx vv;
    int dir = 0;
    VV_SUB(p, q, &vv);
    VV_CALCDIR(vv.x, vv.y, dir);
    return dir;
}

//valgrind --leak-check=yes ./main.out
//valgrind --leak-check=yes  --leak-check=full --show-leak-kinds=all --log-file=valgrind.log ./main.out
int valgrind_test()
{
    _valgrind_test6();
    return 0;
}
