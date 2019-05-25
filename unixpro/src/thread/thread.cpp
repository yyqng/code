#include "thread.h"

using namespace std;

int threadtest(int argc, char *argv[])
{
    const int n = 5;
    const long t = 500;
    mutex m;
    thread thread1( [&m,n,t](void)->void
    {
        for ( int i=0; i < n; ++ i )
        {
            m.lock();
            cout << "Thread one." << endl;
            m.unlock();
            this_thread::sleep_for(chrono::milliseconds(t));
        }
    });
    thread thread2( [&m,n,t](void)->void
    {
        for ( int i=0; i < n; ++ i )
        {
            m.lock();
            cout << "Thread two." << endl;
            m.unlock();
            this_thread::sleep_for(chrono::milliseconds(t));
        }
    });
    thread1.join();
    thread2.join();
    return EXIT_SUCCESS;
}
