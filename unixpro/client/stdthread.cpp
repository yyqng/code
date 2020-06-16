#include "stdthread.h"

const int SIZE = 10;

void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "f1: Thread 1 n = " << n << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        ++n;
        std::cout << "f2: Thread 2 n = " <<  n << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int test1()
{
    std::thread t1;                   // t1 is not a thread
    std::thread t2(f1, 1);            // pass by value
    int n = 0;
    std::thread t3(f2, std::ref(n));  // pass by reference
    std::thread t4(std::move(t3));    // t4 is now running f2(). t3 is no longer a thread
    t2.join();
    t4.join();
    std::cout << "Final value of n is " << n << '\n';
    return 0;
}




void thread_task(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "hello thread "
        << std::this_thread::get_id()
        << " paused " << n << " seconds" << std::endl;
}

int test2()
{
    std::thread threads[5];
    std::cout << "Spawning 5 threads...\n";
    for (int i = 0; i < 5; i++) {
        threads[i] = std::thread(thread_task, i + 1);
    }
    std::cout << "Done spawning threads! Now wait for them to join\n";
    for (auto& t: threads) {
        t.join();
    }
    std::cout << "All threads joined.\n";

    return EXIT_SUCCESS;
}




void foo3()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int test3()
{
    std::thread t1(foo3);
    std::thread::id t1_id = t1.get_id();
  
    std::thread t2(foo3);
    std::thread::id t2_id = t2.get_id();
  
    std::cout << "t1's id: " << t1_id << '\n';
    std::cout << "t2's id: " << t2_id << '\n';
  
    t1.join();
    t2.join();
    return 0;
}




void foo4()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int test4()
{
    std::thread t;
    std::cout << "before starting, joinable: " << t.joinable() << '\n';
  
    t = std::thread(foo4);
    std::cout << "after starting, joinable: " << t.joinable() << '\n';
  
    t.join();
    return 0;
}




void foo5()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar5()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int test5()
{
    std::cout << "starting first helper...\n";
    std::thread helper1(foo5);
  
    std::cout << "starting second helper...\n";
    std::thread helper2(bar5);
  
    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();
  
    std::cout << "done!\n";
    return 0;
}




void independentThread() 
{
    std::cout << "Starting concurrent thread.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Exiting concurrent thread.\n";
}
 
void threadCaller() 
{
    std::cout << "Starting thread caller.\n";
    std::thread t(independentThread);
    t.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Exiting thread caller. t.joinable() = " << t.joinable() << "\n";
}
 
int test6() 
{
    threadCaller();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}




void foo7()
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar7()
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

int test7()
{
    std::thread t1(foo7);
    std::thread t2(bar7);
  
    std::cout << "thread 1 id: " << t1.get_id() << std::endl;
    std::cout << "thread 2 id: " << t2.get_id() << std::endl;
  
    std::swap(t1, t2);
  
    std::cout << "after std::swap(t1, t2):" << std::endl;
    std::cout << "thread 1 id: " << t1.get_id() << std::endl;
    std::cout << "thread 2 id: " << t2.get_id() << std::endl;
  
    t1.swap(t2);
  
    std::cout << "after t1.swap(t2):" << std::endl;
    std::cout << "thread 1 id: " << t1.get_id() << std::endl;
    std::cout << "thread 2 id: " << t2.get_id() << std::endl;
  
    t1.join();
    t2.join();
    return 0;
}



std::mutex iomutex;
void f(int num)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
   
    sched_param sch;
    int policy; 
    pthread_getschedparam(pthread_self(), &policy, &sch);
    std::lock_guard<std::mutex> lk(iomutex);
    std::cout << "Thread " << num << " is executing at priority "
              << sch.sched_priority << '\n';
}

int test8()
{
    std::thread t1(f, 1), t2(f, 2);
  
    sched_param sch;
    int policy; 
    pthread_getschedparam(t1.native_handle(), &policy, &sch);
    sch.sched_priority = 20;
    if(pthread_setschedparam(t1.native_handle(), SCHED_FIFO, &sch)) {
        std::cout << "Failed to setschedparam: " << std::strerror(errno) << '\n';
    }
  
    t1.join();
    t2.join();
    return 0;
}




int test9()
{
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
    return 0;
}




std::mutex g_display_mutex;

void foo10()
{
    std::thread::id this_id = std::this_thread::get_id();
  
    g_display_mutex.lock();
    std::cout << "thread " << this_id << " sleeping...\n";
    g_display_mutex.unlock();
  
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int test10()
{
    std::thread t1(foo10);
    std::thread t2(foo10);
  
    t1.join();
    t2.join();
    return 0;
}




// "busy sleep" while suggesting that other threads run 
// for a small amount of time
void little_sleep(std::chrono::microseconds us)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    do {
        std::this_thread::yield();
    } while (std::chrono::high_resolution_clock::now() < end);
}

int test11()
{
    auto start = std::chrono::high_resolution_clock::now();
  
    little_sleep(std::chrono::microseconds(1000000));
  
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "waited for "
              << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
              << " microseconds\n";
    return 0;
}




int test12()
{
    std::cout << "Hello waiter" << std::endl;
    std::chrono::milliseconds dura( 2000 );
    std::this_thread::sleep_for( dura );
    std::cout << "Waited 2000 ms\n";
    return 0;
}



int x = 0; //共享变量
 
void synchronized_procedure()
{
    static std::mutex m; 
    m.lock(); 
    x = x + 1; 
    if(x < 5) {
         cout << "hello"; 
    } 
    m.unlock(); 
} 

int test13()
{
    synchronized_procedure(); 
    x = x + 2; 
    cout << "x is " << x; 
    return 0;
} 

void stdthread_test()
{
    test12();
}
