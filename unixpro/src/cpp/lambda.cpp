#include "test-cpp.h"
//#include "shmtest.h"

void formattest()
{
    []{
            cout << "Hello lambda without () 不会输出到屏幕." << endl;
    };

    []{
            cout << "Hello lambda with () 输出到屏幕." << endl;
    }();

    auto L = []{
            cout << "Hello lambda object L(). 输出到屏幕" << endl;
    };
    L();

}

void paramtest()
{
    int id = 0;
    cout << "id 初始值:" << id << endl;
    auto L = [id]()mutable{
        ++id;
        cout << "id in L:" << id << endl;
    };
    L();
    cout << "id out of L:" << id << endl;

    auto F = [&id]()mutable{
        ++id;
        cout << "id in F:" << id << endl;
    };
    F();
    cout << "id out of F:" << id << endl;

    int param = 0;
    cout << "param 初始值:" << param << endl;
    auto G = [id](int &param)mutable{
        ++param;
        ++id;
        cout << "param in G:" << param << endl;
        cout << "id    in G:" << id    << endl;
    };
    G(param);
    cout << "param out of G:" << param << endl;
    cout << "id    out of G:" << param << endl;
}


int for_each_Lambda( )
{
    int a[] = {1,2,5,9,52,6,3,14};
    function <bool (const int & , const int &)> compare;
    auto output = [](int n)->void{ cout << n << endl; };
    // C++11标准中， auto 关键字新义，任意类型，类型由初始化表达式确定
    // “[](int n)->void{ cout << n << endl; }”是Lambda表达式

    cout << "升序排序" << endl;
    compare = []( const int & a , const int & b )->bool { return a < b; };
    sort( a, a+_countof(a), compare  );
    for_each( a, a+_countof(a), output );
    cout << endl;

    cout << "降序排序" << endl;
    compare = []( const int & a , const int & b )->bool { return b < a; };
    sort( a, a+_countof(a), compare  );
    for_each( a, a+_countof(a), output );
    cout << endl;

    return EXIT_SUCCESS;
}

void lambdatest()
{
    //formattest();
    //paramtest();
    for_each_Lambda( );
}
