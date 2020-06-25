#include "trathread.h"
#include "Observer.h"
///* ***************************************** Thread Object **********************
//Create thread
//There are two styles to create a thread in OOP language.
//One is like QThread, inherit QThread and override run method then call start launch:
//*/
//class DeepThroughtThread : public QThread {
//    Q_OBJECT
//    virtual void run() override {
//        the_answer = 42;
//    }
//    int the_answer = 0;
//};
//
//void p6()
//{
//	DeepThroughtThread* thread = new DeepThroughtThread(...);
//	thread->start();
//	thread->wait();
//	assert(thread->the_answer == 42);
//}


/*
The other like std::thread and tpool, no need to inherit, pass thread body function to constructor and launch directly:
*/

void p7_0()
{
	int the_answer;
	std::thread thread([&]{
		the_answer = 42;
	});
	thread.join();
	assert(the_answer == 42);
    printf("the_answer = %d\n", the_answer);
}

/*
By default, arguments are copied, if we want to pass by reference, std::ref can help:
*/

void p7_1()
{
	int the_answer;
	auto deep_throught = [](int& output) { 
		output = 42; 
	};
	std::thread thread(deep_throught, std::ref(the_answer));
	//thread.detach();  //don't suggest
    std::this_thread::sleep_for(std::chrono::seconds(1));
	thread.join();
	assert(the_answer == 42);
    printf("the_answer = %d\n", the_answer);
}


///*
//Life cycle of thread object
//Thread object is noncopyable, if compiler supports c++11, it's moveable;
//
//Thread object is an agent to start and manage system thread, not the system thread itself. If we don't need to manage thread anymore, we can detach it:
//
//	std::thread thread(deep_throught, std::ref(the_answer));
//	thread.detach();
//We don't suggest to detach, because when main thread exits, the process will exit with it, all child thread will be cleaned up. It means your child thread may ends its work in a weird state.
//
//To prevent this issue, we need to join child threads, and the thread can not join after detached.
//
//When the destructor of thread object is called, if its associated thread is still running, std::terminate will be call.
//*/



/*
Some thread libraries support interruption, like boost::thread:

There are many interruption pointers other than boost::this_thread::interruption_point(), see the reference for details.
https://www.boost.org/doc/libs/1_54_0/doc/html/thread/thread_management.html#thread.thread_management.tutorial.interruption
*/

void repeating_itself()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
void p9()
{
	auto history = []() {
		try {
			for (;;) {
                printf("before repeating_itself\n");
				repeating_itself();
                printf("before interruption_point\n");
				boost::this_thread::interruption_point();
                printf("afterinterruption_point\n");
			}
		} catch (boost::thread_interrupted&) {
            printf("catch thread_interrupted\n");
			return;
		}
	};

    printf("before boost::thread\n");
	boost::thread tr(history);
	// we learn from it
    printf("before tr.interrupt\n");
	tr.interrupt();
    printf("before tr.join\n");
	tr.join();
    printf("after tr.join\n");
}



//*
//tpool supports CancelableThread, its mechanism likes:
//*/
void p10()
{
	bool is_cancel_request = false;
	auto check_cancellation = [&] {
		if (is_cancel_request) {
            printf("is_cancel_request is true and will throw std::exception\n");
			//throw std::exception("cancelled");
			throw std::exception();
		}
	};
	auto history = [&]() {
		try {
			for (;;) {
                printf("before repeating_itself\n");
				repeating_itself();
				check_cancellation();
			}
		} catch (std::exception&) {
            printf("catch exception\n");
			return;
		}
	};

	std::thread tr(history);
	// we learn from it
	is_cancel_request = true;
    printf("After set is_cancel_request = true\n");
	tr.join();
}


///*
//We can only stop a thread in specified interruption point and check cancellation point.
//We can not promise the thread will stop as soon as you call interruption or cancel.
//*/
//
//
//
///* ***************************************** Synchronization **********************
//Mutex
//A mutex object facilitates protection against data races and allows thread-safe synchronization of data between threads.
//
//A thread obtains ownership of a mutex object by calling one of the lock functions and relinquishes ownership by calling the corresponding unlock function.
//
//One mutex can only be owned by one thread at a time, once a thread locks a mutex, other thread which trying to like the mutex will block until the lock is released.
//
//mutex usually has the following interface:
class mutex : boost::noncopyable
{
    void lock();
    void unlock();
    bool try_lock();
};
void p15()
{
	long count = 0;
    const long rt = 100000; //assert failed
//    const long rt = 10000; //assert success
	std::mutex mtx;

	auto counter = [&]() {
		for (long i = 0; i < rt; i++) {
	//		mtx.lock();
			count++;
	//		mtx.unlock();
		}
	};

	std::thread tr1(counter);
	std::thread tr2(counter);

	tr1.join();
	tr2.join();
	assert(count == 2 * rt);
}




/*
lock_guard
For possible exceptions or forgetting to unlock, mutex should use with RAII objects, like std::lock_guard:
std::lock_guard will mutex in constructor and unlock in destructor. So the mutex will unlock when the lock_guard instance is out of scope.
*/
void p16()
{
	long count = 0;
    const long rt = 100000; //assert failed
	std::mutex mtx;
	auto counter = [&]() {
		for (long i = 0; i < rt; i++) {
			std::lock_guard<std::mutex> lk(mtx);
			count++;
		}
	};

	std::thread tr1(counter);
	std::thread tr2(counter);

	tr1.join();
	tr2.join();
	assert(count == 2 * rt);
}





/*
In tpool, tpool::sync::MutexLocker provides the same functionality:
*/
//class MutexLocker : private boost::noncopyable {
//public:
//    explicit MutexLocker(Mutex& m) : m_mutex(m) { m_mutex.Lock(); }
//
//    ~MutexLocker() { m_mutex.Unlock(); }
//
//private:
//    Mutex& m_mutex;
//};

/*
Recursive Mutex
std::recursive_mutex can be locked multiple times by the same thread:
*/
class Counter : private boost::noncopyable {
public:
    Counter(): m_count(0){}
    void add() {
        std::lock_guard<std::recursive_mutex> lk(m_mutex);
        add_internal();
    }
    long get_count() {
        return m_count;
    }
private:
    void add_internal() {
        std::lock_guard<std::recursive_mutex> lk(m_mutex);
        m_count++;
    }
    std::recursive_mutex m_mutex;
    long m_count;
};

void px1()
{
    const long rt = 100000; //assert failed
    Counter counter;
	auto counterf = [&]() {
		for (long i = 0; i < rt; i++) {
			counter.add();
		}
	};

	std::thread tr1(counterf);
	std::thread tr2(counterf);

	tr1.join();
	tr2.join();
	assert(counter.get_count() == 2 * rt);
}

/*
Recursive Mutex is dangerous for beginner
std::recursive_mutex allows class state be modified during the mutex is locked.
*/
//class Counter2;
//class Proxy {
//public:
//    Proxy(Counter2 &c) : m_counter(c) {}
//    Counter2 &m_counter;
//    void hook();
//};
//class Counter2 : private boost::noncopyable {
//public:
//    Counter2(): m_count(0){}
//    void add() {
//        std::lock_guard<std::recursive_mutex> lk(m_mutex);
//        add_internal();
//    }
//private:
//    void add_internal() {
//        std::lock_guard<std::recursive_mutex> lk(m_mutex);
//        m_count++;
//        if (m_count < 42) {
//            m_proxy.hook();
//        }
//    }
//    std::recursive_mutex m_mutex;
//    int m_count;
//    Proxy m_proxy;
//};
//void Proxy::hook() {
//    m_counter.add();
//}

/*
Pass Unnamed lock_guard as Argument
Don't use recursive mutex as possible as you can, deadlock is better than unexpected state.

But we still need to guarantee that private methods are called correctly with lock.

We can pass the lock_guard as extra argument explicitly:
*/
class Counter3 : private boost::noncopyable {
public:
    Counter3(): m_count(0){}
    void add() {
        std::lock_guard<std::mutex> lk(m_mutex);
        add_internal(lk);
    }
    long get_count() {
        return m_count;
    }
private:
    void add_internal(const std::lock_guard<std::mutex> &) {
        m_count++;
    }
    std::mutex m_mutex;
    int m_count;
};
void px3()
{
    const long rt = 100000; //assert failed
    Counter3 counter;
	auto counterf = [&]() {
		for (long i = 0; i < rt; i++) {
			counter.add();
		}
	};

	std::thread tr1(counterf);
	std::thread tr2(counterf);

	tr1.join();
	tr2.join();
	assert(counter.get_count() == 2 * rt);
}


/*
Condition Variable
Condition variable provide a mechanism for one or many threads to wait for notification from another thread that a particular condition has become true.

usually has the following interface:
*/
//class condition_variable : boost::noncopyable
//{
//    void wait(mutex&);
//    void notify_one();
//    void notify_all();
//};
//
//
///*
//condition_variable must use together with mutex (which protects the particular condition).
//
//To make sure user passes the right mutex to condition_variable, some libraries(like tpool) acquire the mutex as construction parameter:
//*/
//class condition_variable : boost::noncopyable
//{
//    condition_variable(mutex&)
//    void wait();
//    void notify_one();
//    void notify_all();
//private:
//    mutex& m_mutex;
//};
//
//
///*
//AS we talk before, we use mutex with RAII objects, so c++11/boost accepts unique_lock instead of mutex directly.
//unique_lock is similar to lock_guard, but unique_lock can lock and unlock many time.
//*/
//class condition_variable : boost::noncopyable
//{
//    void wait(std::unique_lock<std::mutex>&);
//    void notify_one();
//    void notify_all();
//};
//
//
/*
Example to use condition_variable:
*/
void p24()
{
	int the_answer = -1;
	bool the_answer_is_ready = false; // the condition we waiting for
	std::mutex mtx; // protect the_answer and the_answer_is_ready
	std::condition_variable cond;

	auto f1 = [&]() {
		// lock condition than modify
        printf("thread lock\n");
		std::lock_guard<std::mutex> lk(mtx);
		the_answer = 42;
		the_answer_is_ready = true;
		// notify waiters after condition modified
        printf("thread cond.notify_all\n");
		cond.notify_all();
	};
	std::thread tr1(f1);

	std::unique_lock<std::mutex> ulk(mtx);
    std::this_thread::sleep_for(std::chrono::seconds(1));
	while (!the_answer_is_ready) { // keep waiting when condition is not what we want
		// wait contains three step: 
		// 1. unlock ulk
		// 2. hang this thread until being notified
		// 3. relock ulk after notified
        printf("main thread waiting\n");
		cond.wait(ulk);
        printf("main thread recived\n");
	}
	assert(the_answer_is_ready == true);
	assert(the_answer == 42);
	tr1.join();
//	tr2.join();
//	std::thread tr3(f1);
//	tr3.join();
}




/*
Why we need a while loop waiting?
notify_all will wakeup all waiting thread, which may change the_answer_is_ready before other thread return from wait
Spurious wakeup allowed to return from wait even if not notified
Thinking questions:
why the_answer_is_ready is necessary in this case? What will happen if we remove it?


The general usage pattern:
One thread locks a mutex and then calls wait on an instance of condition_variable.
wait will atomically add the thread to waiting list of the condition variable, and unlock the mutex. This allows other threads to acquire the mutex to update the shared data and associated condition.
When the thread is waken, the mutex will be locked again before the call to wait returns.
When return from the wait, it checks to see if the appropriate condition is now true, and continues if so.
If the condition is not true, then the thread will calls wait again to resume waiting.
Considering that writing a while loop is cumbersome, boost(and c++11) provides a predicated version:
cond.wait(ulk, [&](){return the_answer_is_ready;});


mutex + condition_variable are the basic synchronization tool
In Theory, mutex + condition_variable can achieve any synchronization scene we can imagine.
And we can use mutex + condition_variable to implement other advanced synchronization tools.
(Semaphore have equal ability, we will discuss it next)
*/


///*
//Semaphore
//A (Counting) Semaphore is a synchronization tool that can control access shared resources.
//*/
#include <semaphore.h>
class semaphore : public boost::noncopyable {
public:
    semaphore(unsigned int limit, unsigned int count) {
        sem_init(&m_sem, 0, limit);
        for (unsigned int i = 0; i < count; ++i) {
            sem_wait(&m_sem);
        }
    }
//    void acquire(unsigned int diff = 1);
//    void release(unsigned int diff = 1);
    void acquire(unsigned int diff = 1) {
        sem_wait(&m_sem);
    }
    void release(unsigned int diff = 1) {
        sem_post(&m_sem);
    }
    ~semaphore() {
        sem_destroy(&m_sem);
    }
    sem_t m_sem;
};

/*
Binary semaphore sometimes use as mutex + condition_variable:
*/
void p28()
{
	int the_answer = -1;
	semaphore sem(1, 1);
	std::thread tr([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
		the_answer = 42;
        printf("in thread before sem.release\n");
		sem.release();
        printf("in thread after sem.release\n");
	});
    printf("in main before sem.acquire\n");
	sem.acquire();
    printf("in main after sem.acquire\n");
	assert(42 == the_answer);
    tr.join();
}

///*
//producer-consumer problem can solve using semaphore:
//*/
int production = 0;
void producer(semaphore &sem_product, semaphore &sem_slot, std::mutex &mtx) {
	while (true) {
		sem_slot.acquire();
		{
			std::lock_guard<std::mutex> lk(mtx);
            printf("producer: production = %d.\n", production);
            ++production;
		}                              
		sem_product.release();
	}    
}
void consumer(semaphore &sem_product, semaphore &sem_slot, std::mutex &mtx) {
	while (true) {
		sem_product.acquire();
		{
			std::lock_guard<std::mutex> lk(mtx);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            printf("consumer ------: production = %d.\n", production);
            --production;
		}                          
		sem_slot.release();         
	}
}
void p29()
{
	static const int N = 5;                       
	std::mutex mtx;                                   
	semaphore sem_slot(N, 0);                     
	semaphore sem_product(N, N);                  
	std::thread tr1([&]() {
        producer(sem_product, sem_slot, mtx);
	});
	std::thread tr2([&]() {
        consumer(sem_product, sem_slot, mtx);
	});
    tr1.join();
    tr2.join();
}



///*
//It can also apply to limit the concurrent access to one resources, e.g. limit connection to server.
//*/
//void p30()
//{
//	static const int g_limit = 100;
//	semaphore sem_limit(s_limit, 0); 
//
//	while (true) {
//		sem_limit.acquire();
//		connect_to_server();
//		do_something_with_the_connection();
//		disconnect();
//		sem_limit.release();
//	}
//}
//
//
//
//
//
///*
//Be careful with semaphore
//Semaphore achieved same effect as mutex + condition variable.
//Without RAII object, easy to forget release.
//Binary semaphore is confused with mutex.
//Different from mutex, semaphore can acquire in one thread but release in another thread.
//boost doesn't provide semaphore, tpool and c++ 20(std::counting_semaphore) provided.
//*/
//
//
///*
//Future/Promise
//What if it throws an exception while calculating the_answer?

//In previous example, we declared value(the_answer), state(the_answer_is_ready), mutex(mtx), condition variable(cond), thread(tr), and maybe need handle exception. This complexity usage pattern is hard for beginner.
//
//So people provide future/promise:
//*/
//
#include <boost/thread/future.hpp>
//#include <boost/thread/promise.hpp>

void p33a()
{
    std::promise<int> pr;
    std::future<int> fu = pr.get_future();
    auto f = [](std::promise<int>& pr) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printf("p33a: pr.set_value(42)\n");
        pr.set_value(42);
    };
    std::thread tr(f, std::ref(pr));
    assert(fu.get() == 42);
}

void p33b()
{
	boost::promise<int> pr;
	boost::unique_future<int> fu = pr.get_future();
	auto f = [](boost::promise<int>& pr) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printf("p33b: pr.set_value(42)\n");
		pr.set_value(42);
	};
	boost::thread tr(f, boost::ref(pr));
    printf("p33b: fu.get() = %d\n", fu.get());
	assert(fu.get() == 42);
}




///*
//Further more, we don't want to declare promise and thread, we can use free function async to simplify it:
//Each async will launch a new thread.
//*/
//
void p34()
{
	std::future<int> fu = std::async([](){ return 42;});
	assert(fu.get() == 42);
}




///*
//Future/Promise are proxy for async result
//promise usually has the following interface:
//*/
//template<typename T>
//class promise : boost::noncopyable{
//public:
//    promise();
//    ~promise();
//    future<T> get_future();
//    void set_value(const T& value);
//    void set_exception(boost::exceptional_ptr p);
//};
//
///*
//future usually has the following interface:
//promise and future shared same internal state, which contains value, state, mutex condition variable and exception we talk before.
//*/
//template<typename T>
//class future {
//     friend class promise<T>;
//public:
//     T get();
//     bool is_ready() const;
//     bool has_exception() const;
//     bool has_value() const;
//     void wait() const;
//};
//
///*
//Future can be a default tool for one-time synchronization
//Most case can solve by one future, if can't, use two futures!
//Some libraries didn't provide future/promise, e.g. ancient java, tpool. But they also provide similar tool FutureTask, which can use in thread pool:
//
//If two futures still insufficient: Barrier, Latch or Blocking Queue
//*/
//void p37()
//{
//	tpool::LThreadPool& pool = tpool::GetThreadPool();
//	tpool::FutureTask<int>::Ptr task = pool.AddFutureTask([](){ return 42;});
//	assert(task.GetResult() == 42);
//}
//
//
//
//
///*
//Barrier
//A barrier is a synchronization point between multiple threads.
//
//The barrier is configured for a particular number of threads (n), and as threads reach the barrier they must wait until all n threads have arrived.
//
//Once the n-th thread has reached the barrier, all the waiting threads can proceed, and the barrier is reset.
//*/
//
//void p38()
//{
//	int many_anwer[5];
//	boost::barrier br(5+1); // thread number to rendezvous, add main thread here
//
//	for (int& answer: many_anwer) {
//		boost::thread tr([&]() {
//			answer = 42;
//			br.wait();
//		});
//		tr.detach();
//	}
//	br.wait(); // threads finished after this wait
//}
//
//
//
//
///*
//Latch
//Latches are a thread co-ordination mechanism that allow one or more threads
//to block until one or more threads have reached a point.
//
//boost provides barrier & latch, c++20 also;
//tpool provides CyclicBarrier & CountDownLatch.
//*/
//
//void p7()
//{
//	int many_anwer[5];
//	boost::latch lt(5); // worker number to be cound down, no need main thread
//
//	for (int& answer: many_anwer) {
//		boost::thread tr([&]() {
//			answer = 42;
//			lt.count_down();
//		});
//		tr.detach();
//	}
//	lt.wait(); // threads may finished before this wait
//}
//
//
//
//
///*
//Blocking Queue
//Blocking queue is simplest implementation of thread safe queue, blocking in pop if queue is empty.
//
//Please notice that size() and empty() are meaningless in multi-thread programming.
//*/
//template<typename T>
//class blocking_queue : boost::noncopyable {
//    std::queue<T> m_queue;
//    std::condition_variable m_cond;
//    mutable std::mutex m_mutex;
//public:
//    blocking_queue() {}
//    void push(const T& val);
//    void pop(T& val);
//    bool try_pop(const T& val);
//    size_t size() const;
//    bool empty() const;
//};
//
//
//
//
///*
//Bounded Blocking Queue
//Similar to blocking queue, but the size is limited, which means that push will also block if buffer is full.
//
//Producer-Consumer problem by bounded blocking queue:
//*/
//static const int N = 100;  
//class production;
//bounded_blocking_queue<production> queue(N);
//std::thread producer([&]() {
//    production item;
//    while (true) {
//        item  = produce_item();
//        queue.push(item);
//    }
//});
//
//std::thread consumer([&]() {
//    production item;
//    while (true) {
//        queue.pop(item);
//        consume_item(item);  
//    }
//});
//
//
//
///* ***************************************** Synchronization **********************
//Task based execution
//We know that thread creation and scheduling are expensive. For computationally intensive tasks, create thread frequently is not worth it.
//
//To reuse threads, we create thread pool:
//*/
//typedef std::function<void()> task_type;
//blocking_queue<task_type> task_queue;
//std::thread worker_thread([&]() {
//    task_type task;
//    while (true) {
//        task_queue.pop(task);
//        if (task) {
//            task();
//        }
//    }
//});
//std::vector<int> result(233);
//for (int i = 0; i < 233; i++) {
//    task_queue.push([i, &result]{}{
//        result[i] = 42;
//    });
//}
//worker_thread.join(); // BUG: block forever
//
//
///*
//We have different philosophy about how to define task:
//
//boost use boost::function<void()> as task. task queue stores boost::function<void()> directly.
//Some other library(like tpool) define a task_base class, user inherit from it. task queue store smart pointers of task base:
//*/
//
//struct task_base {
//    virtual ~task_base(){}
//    virtual void run() = 0;
//};
//typedef std::shared_ptr<task_base> task_type;
//
//blocking_queue<task_type> task_queue;
//std::thread worker_thread([&]() {
//    task_type task;
//    while (true) {
//        task_queue.pup(task);
//        if (task) {
//            task->run();
//        }
//    }
//});
//
//struct function_task: public task_base {
//    std::function<void()> func;
//    function_task(const std::function<void()>& _func): func(_func){}
//    virtual void run() override {
//        if (func) {
//            func();
//        }
//    }
//}
//
//std::vector<int> result(233);
//for (int i = 0; i < 233; i++) {
//    task_type task(new function_task([i, &result]() {
//        result[i] = 42;
//    }))
//    task_queue.push(task);
//}
//worker_thread.join(); // BUG: block forever
//
//void p7()
//{
//}
//
//
//
//
///*
//Thread Pool
//Thread pool is multiple threads share a task queue.
//
//But there are some questions to be discuss:
//how to close a task queue
//how to destruct a thread pool instance
//how to handle exception from task
//*/
//
///*
//Closing task queue
//In simplest implementation of blocking queue, task queue can not be closed because of pop is a blocking call.
//
//There are two ways to close a task queue:
//
//one is add a flag in blocking queue, then always check this flag when push and pop called, if the flag was set to close, return without block or throw exception. boost is an example.
//the other called "poison pill", it means when worker thread ends itself when it pulled a special task from queue. tpool is an example.
//*/
//
///*
//Destruction of thread pool
//What should be done when we want to destruct a thread pool?
//
//close the task queue?
//cancel or interrupt running tasks?
//give up task pending on task queue?
//Take tpool as example, it close the task queue, join worker thread, so pending tasks will be finished.
//
//Global thread pool is different. In tpool, global thread pool will stop worker threads, which means trying to cancel all running tasks and give up pending tasks.
//
//boost thread pool will close task queue , then interrupt and join worker threads. But no interrupt point there, so pending task will be finished.
//*/
//
///*
//Exception handling
//What if task throws an exception?
//
//In tpool, Run method will catch the exception(actually, user override DoRun, which called by Run), so worker threads won't stop by exception.
//
//boost is different, std::terminate() will be called if task throws. But we usually use future in boost, future can store exception(use std::exception_ptr or boost::exception_ptr).
//*/
//
///*
//Basic Thread Pool Implementation
//*/
//class basic_thread_pool {
//    boost::thread_group m_threads;
//    boost::concurrent::sync_queue<task_type> m_tasks;
//public:
//    basic_thread_pool(size_t thread_count = boost::thread::hardware_concurrency() + 1) {
//        try {
//            for (size_t i = 0; i < thread_count; ++i) {
//                m_threads.create_thread(boost::bind(&basic_thread_pool::worker_thread, this));
//            }
//        } catch(...) {
//            close();
//            throw;
//        }
//    }
//    ~basic_thread_pool() {
//        close();
//        join();
//    }
//public:
//    void close() {
//        m_tasks.close();
//    }
//    bool closed() const{
//        return m_tasks.closed();
//    }
//    void submit(task_type& w) {
//        m_tasks.push(w);
//    }
//
//private:
//    void join() {
//        m_threads.interrupt_all();
//        m_threads.join_all();
//    } 
//    void worker_thread() {
//        try {
//            for (;;) {
//                work task;
//                try {
//                    boost::concurrent::queue_op_status st = m_tasks.wait_pull(task);
//                    if (st == boost::concurrent::queue_op_status::closed) {
//                        return;
//                    }
//                    task();
//                } catch (boost::thread_interrupted&) {
//                    return;
//                }
//            } // for
//        } catch (...) {
//            std::terminate();
//            return;
//        }
//    }
//};
//
///*
//Basic Thread Pool is Easy to Deadlock
//For thread pool with fixed thread number, it easy to dead lock:
//
//Waiting for sub tasks blocks current worker thread, if all worker threads waiting sub tasks, sub tasks can't be executed.
//*/
//template<typename Ex = basic_thread_pool>
//int fib(Ex& ex, int n) {
//    if (n == 0) {
//        return 0;
//    } else if (n == 1) {
//        boost::future<int> f1 = boost::async(ex, fib, n-1);
//        boost::future<int> f2 = boost::async(ex, fib, n-2);
//        return f1.get() + f2.get();
//    }
//}
//
///*
//Reschedule Until
//Help to execute other tasks until sub tasks finished:
//*/
//template <typename Pred>
//bool basic_thread_pool::reschedule_until(const Pred& pred) {
//    do {
//        if (!try_executing_one()) {
//            return false;
//        }
//    } while (!pred());
//    return true;
//}
//bool basic_thread_pool::try_executing_one() {
//    try {
//        work task;
//        if (m_tasks.try_pull(task) == queue_op_status::success) {
//            task();
//            return true;
//        }
//        return false;
//    } catch (...) {
//        std::terminate();
//    }
//}
//
//
///*
//So we are not blocking wait:
//*/
//int fib(Ex& ex, int n) {
//    if (n = 0) {
//        return 0;
//    } else if (n == 1) {
//        return 1;
//    } else {
//        boost::future<int> f1 = boost::async(ex, fib, n-1);
//        boost::future<int> f2 = boost::async(ex, fib, n-2);
//        ex.reschedule_until([&]()->bool{
//            return f1.is_ready() && f2.is_ready();
//        });
//        return f1.get() + f2.get();
//    }
//}
//
//
///*
//Scheduler
//Scheduler maintains timed tasks, it means execute a task after a time duration or execute a task at a time point.
//e.g. do something after 1 second, do other thing at 8:20.
//
//In simplest case, scheduler is similar to thread pool but it only have one worker thread. Its task queue is sorted by time point(time duration will also convert to time point once it submitted), its condition variable wait for the time point form the top of task queue.
//Submitting a new task will also wake up the condition variable, because the new task may have the nearest time point.
//*/
//void p54()
//{
//	boost::executors::scheduler<boost::chrono::steady_clock> sc;
//	sc.submit_after([] {
//		std::cout << "hello world" << std::endl;
//	}, boost::chrono::seconds(5));
//}
//
//
//
//
///*
//The task may take long time to delay other tasks, so we can use with thread pool, submit the task to thread pool when the time point is reached.
//
//In tpool , we provides tpool::Timer as scheduler.
//*/
//
//void p55()
//{
//	scheduler sc;
//	basic_thread_pool ex;
//	sc.on(ex).after(boost::chrono::milliseconds(500)).submit([](){
//		std::cout << "hello world" << std::endl;
//	});
//}
//
//
//
//
///*
//Thread or Thread Pool?
//For long running tasks, use thread.
//For disk I/O task, multi-thread can't help, but can reduce blocking.
//For socket I/O task, multi-thread may help, but we suggest select/epoll, coroutine.
//For CPU-bound task, use global thread pool.
//For detailed discussion about executor, please ref to Appendix: Executor & Fork/Join.
//*/
//
//
/*
What is Thread Safety?
A class is thread-safe if it behaves correctly when accessed from multiple threads, regardless of the scheduling or interleaving of the execution of those threads by the runtime environment.
thread-safe classes encapsulate any needed synchronization so that clients need not provide their own.
Stateless objects are always thread-safe.
How to Achieve Thread-safety
1. Stateless Implementations

It's always thread-safe if a method neither relies on external state nor maintains state at all.

2. Re-entrancy

Saving state information in local variables instead of static or global variables or other non-local state.

Be careful with third-party libraries which may have static or global state.

3. Thread-Local Storage

Variables are localized so that each thread has its own private copy, the code which accesses them might be executed simultaneously by another thread.

But carefully use in thread pool, because you don't know which worker thread will execute your task.
4. Immutable Objects

A class instance is immutable when its internal state can't be modified after it has been constructed.

Mutable (non-const) operations can then be implemented in such a way that they create new objects instead of modifying existing ones.

5. Mutual exclusion

Access to shared data is serialized using mechanisms that ensure only one thread reads or writes to the shared data at any time, e.g. std::mutex.

6. Atomic operation

Shared data is accessed by using atomic operations which cannot be interrupted by other threads, e.g. std::atomic

For operation depends on internal states, put state check and operation in one synchronized method, e.g. compare_and_change instead of compare then change

Thread Safe Class
Thread-safe construction:

don't register callback in constructor
don't pass this to any other cross-thread object
two-phase construction
*/

class Observable;
class Foo : public Observer {
public:
    explicit Foo(Observable* s) {
        s->__register(this); // BAD: may be notify before construction finish
    }
    Foo() = default;
    virtual void update() override {
    }
};

/*
Thread-safe destruction:

don't use naked pointer to handle dynamic allocated thread-safe object, use smart pointer instead.
destructor doesn't need to be protected by it's member mutex
*/


void p50()
{
    Foo* ins = new Foo;
    
    std::thread tr1([&]() {
        delete ins;
    });
    
    std::thread tr2([&]() {
        delete ins;
    });
}

// BAD: double free

/*
Thread-safe copy/move constructors:

if a class contains condition variables, it should be noncopyable.
if only contains mutex, don't provide copy/move constructor until you really need it:
*/

// use c++11 delegation constructor if your data member don't have default constructor
class Counter4 {
public:
    std::mutex m_mtx;
    int m_count = 0;
    //Counter4(const Counter4& that, const std::lock_guard<std::mutex>&): m_count(that.m_count) {}
    Counter4(const Counter4& that, std::lock_guard<std::mutex>&): m_count(that.m_count) {}
public:
    //Counter4(const Counter4& that): Counter4(that, std::lock_guard<std::mutex>(that.m_mtx)) {}
    Counter4(Counter4& that) {
        std::lock_guard<std::mutex> m(that.m_mtx);
        Counter4(that, m);
    }
};

/*
Thread-safe assignment and swap:

if a class contains condition variables, it should not provide assignment operator or swap.
if only contains mutex, don't provide assignment operator and swap until you really need it:
*/
void swap(Counter4& lhs, Counter4& rhs) {
    if (&lhs == &rhs) {
        return;
    }
    std::lock(lhs.m_mtx, rhs.m_mtx);
    std::lock_guard<std::mutex> lock_l(lhs.m_mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock_r(rhs.m_mtx, std::adopt_lock);
    swap(lhs.m_count, rhs.m_count);
}

/*
mutable mutex member for const methods:

const methods still need to be protected by mutex for other synchronization tools.

But lock is a non-const method, so we need to declare member mutex as mutable:
*/
class Counter5 {
    mutable std::mutex m_mutex;
    int m_count = 0;
    void add() {
        std::lock_guard<std::mutex> lk(m_mutex);
        m_count++;
    }
    int count() const {
        std::lock_guard<std::mutex> lk(m_mutex);
        return m_count;
    }
};


/*
mutable member should be thread-safe:

If you want a member to be mutable, it should be thread safe.
*/
class Counter6 {
    mutable std::mutex m_mutex; // ok, mutex is already thread safe
    mutable std::atomic<int> m_called_count; // ok, atomic already is thread safe
    mutable std::string m_last_error; // no, std::string is not thread safe, but ok if you protected it by m_mutex
};

/*
Thread safety of standard libraries
standard library can concurrent read, they promised that const methods are bitwise const or internal synchronized.
data race if one thread writes to some location by other thread read this location concurrently without synchronization
implementations are required to avoid data races when the contents of the contained object in different elements in the same sequence, excepting std::vector<bool>, are modified concurrently
*/

/*
Memory Management
Smart Pointer
Concurrent Memory Allocation
Thread Local Storage
False Sharing
Atomic

Smart Pointer
It's not easy to delete a pointer which may reference in different thread. we can use smart pointer like boost::shared_ptr to handle it.
Reference counter of shared pointer is atomically, so copy and reset a boost::shared_ptr is thread safe.
*/
void p87()
{
    std::shared_ptr<int> the_answer = std::make_shared<int>(42);
    std::thread tr([the_answer]() {
        std::shared_ptr<int> copy = the_answer; //OK: copy is safe
        assert(*copy == 42);
    });
    tr.join();
    assert(*the_answer == 42);
}


/*
Concurrent assign (or reset) same instance of shared pointer will cause data race:

In future, boost::atomic_shared_pointer and c++20 std::atomic<std::shared_ptr<T>> can help with this.

Remember, only "control block" of shared_ptr is thread safe, associated data is not!
*/
void p90()
{
    std::shared_ptr<int> the_answer;
    std::thread tr([&the_answer]() {
        the_answer = std::make_shared<int>(42); // BUG: assign is not safe
    });
    the_answer = std::make_shared<int>(233);
    tr.join();
    assert(*the_answer == 42); // Undefined!
}


/*
Concurrent Memory Allocation
Allocating memory from the system heap can be an expensive operation due to a lock used by system runtime libraries to synchronize access to the heap.

Contention on this lock can limit the performance benefits from multithreading.

Third-party allocators jemalloc or tcmalloc can help with this, and they are easy to use:

env LD_PRELOAD=libjemalloc.so /path/to/your/binary
*/


/*
Thread Local Storage
Where a single-threaded application would use static or global data, this could lead to contention, deadlock or data corruption in a multi-threaded application.

Thread local storage allows multi-threaded applications to have a separate instance of a given data item for each thread.
the output will be(example in vs2019):

construct in 17888
main thread 17888
construct in 19316
worker thread 19316
destruct in 19316
destruct in 17888
*/
struct Answer {
    Answer() { 
        std::cout << "construct in " << std::this_thread::get_id() << std::endl;
    }
    ~Answer() { 
        std::cout << "destruct in " << std::this_thread::get_id() << std::endl;
    }
    int m_the_answer = 0;
};

thread_local Answer the_answer;

int p91() { 
    std::cout << "main thread " << std::this_thread::get_id() << std::endl;
    std::thread tr([]() { 
        std::cout << "worker thread " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    });
    tr.join();
    return 0;
}

/*
boost::thread_specific_ptr
boost::thread_specific_ptr provides a portable mechanism for thread-local storage when you don't have C++11 support.

You need to call reset before use it in each thread and the pointed object will be delete when a thread exits.
*/
#include <boost/thread/tss.hpp>

void p92()
{
    static boost::thread_specific_ptr<Answer> the_answer;
    
    if (!the_answer.get()) {
        the_answer.reset(new Answer());
    }
}


/*
False Sharing
False sharing occurs when threads on different processors modify variables that reside on the same cache line. This invalidates the cache line and forces a memory update to maintain cache coherency.

Thread-local storage or local variables can be ruled out as sources of false sharing.

In following case, a and b will false sharing, tr1's i and tr2's i will false sharing.
*/
void printTime(struct timespec start, const char *info)
{
    struct timespec finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << info << " time cost :" << elapsed << endl;
}
int p93(int64_t &a, int64_t &b)
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
	auto fa = [](int64_t &c) { 
        const int64_t n = 1e8;
        for (int64_t i = 0; i < n; ++i) {
            c++;
        }
	};
	std::thread thread1(fa, std::ref(a));
    thread1.join();
    printTime(start, "change  a.");

    clock_gettime(CLOCK_MONOTONIC, &start);
	std::thread thread2(fa, std::ref(b));
    thread2.join();
    printTime(start, "change  b.");

    clock_gettime(CLOCK_MONOTONIC, &start);
	std::thread thread4(fa, std::ref(a));
	std::thread thread3(fa, std::ref(b));
    thread3.join();
    thread4.join();
    printTime(start, "change ab.");
    return 0;
}
int false_sharing()
{
    int64_t a[2] = {0};
    p93(a[0], a[1]);
    cout << "After fix" << endl;
    int64_t b[64 / sizeof(int64_t)] = {0};
    p93(b[0], b[64 / sizeof(int64_t) - 1]);
    return 0;
}
//change  a. time cost :0.251094
//change  b. time cost :0.247693
//change ab. time cost :0.538793
//After fix
//change  a. time cost :0.249504
//change  b. time cost :0.249257
//change ab. time cost :0.256371




/*
We can find cache line size from /sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size, example 64 byte, then we can use `__declspec (align(64))` to fix this:
*/
struct Foo3 {
//    __declspec (align(64)) int32_t a = 0;
//    __declspec (align(64)) int32_t b = 0;
    int32_t a = 0;
    int32_t b = 0;
};

int p94() {
    const int32_t n = 1000 * 1000 * 1000;
    Foo3 foo3;
    std::thread tr1([&]() {
        //for (__declspec (align(64)) int32_t i = 0; i < n; ++i) {
        for (int32_t i = 0; i < n; ++i) {
            foo3.a++;
        }
    });
    std::thread tr2([&]() {
        //for (__declspec (align(64)) int32_t i = 0; i < n; ++i) {
        for (int32_t i = 0; i < n; ++i) {
            foo3.b++;
        }
    });
    tr1.join();
    tr2.join();
    return 0;
}
#include<malloc.h>
void stdmalloc (char **p, int n)
{ 
    for (int i = 0; i < n; ++i) {
        p[i] = (char*)malloc(sizeof(char));
    }
};
void printTime2(struct timespec start, const char *info)
{
    struct timespec finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << info << elapsed << " s" << endl;
}
const int N = 1e7;
char *p1[N];
char *p2[N];
int malloc_test0()
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    std::thread thread1(stdmalloc, p1, N);
    thread1.join();
    printTime2(start, "thread1   new.");
    for (int i = 0; i < N; ++i) {
        free(p1[i]);
        p1[i] = NULL;
    }

//    clock_gettime(CLOCK_MONOTONIC, &start);
//	std::thread thread2(stdmalloc, p2, N);
//    thread2.join();
//    printTime2(start, "thread2   new.");
//    for (int i = 0; i < N; ++i) {
//        delete p2[i];
//        p2[i] = NULL;
//    }

    clock_gettime(CLOCK_MONOTONIC, &start);
	std::thread thread3(stdmalloc, p1, N);
	std::thread thread4(stdmalloc, p2, N);
    thread3.join();
    thread4.join();
    printTime2(start, "thread3/4 new.");
    for (int i = 0; i < N; ++i) {
        delete p1[i];
        p1[i] = NULL;
        delete p2[i];
        p2[i] = NULL;
    }
    return 0;
}

struct Strarg {
    char **p;
    int len;
};

static void *threadf(void *arg)       
{
    Strarg *s = (Strarg*)arg;
    for (int i = 0; i < s->len; ++i) {
        s->p[i] = (char*)malloc(sizeof(char));
    }
    pthread_exit(NULL);
}

int malloc_test()
{

    pthread_t threads[2];
    memset(&threads, 0, sizeof(threads));
    Strarg s1 = {p1, N};
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    if (pthread_create(&threads[0], NULL, threadf, (void*)&s1) == -1) {
        printf("thread1 create falied\n");
        exit(-1);
    }
    pthread_join(threads[0],NULL);
    printTime2(start, "thread1   malloc.");
    for (int i = 0; i < N; ++i) {
        free(s1.p[i]);
        s1.p[i] = NULL;
    }

    memset(&threads, 0, sizeof(threads));
    clock_gettime(CLOCK_MONOTONIC, &start);
    if (pthread_create(&threads[0], NULL, threadf, (void*)&s1) == -1) {
        printf("threads1 create falied\n");
        exit(-1);
    }
    Strarg s2 = {p2, N};
    if (pthread_create(&threads[1], NULL, threadf, (void*)&s2) == -1) {
        printf("threads1 create falied\n");
        exit(-1);
    }
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    printTime2(start, "thread0/1 malloc.");
    for (int i = 0; i < N; ++i) {
        free(s1.p[i]);
        s1.p[i] = NULL;
        free(s2.p[i]);
        s2.p[i] = NULL;
    }
    return 0;
}

extern "C"
{
#include "jemalloc/jemalloc.h"
}
void jemalloc(char **p, int n)
{
    for (int i = 0; i < n; ++i) {
        p[i] = (char*)mallocx(sizeof(char), 0);
    }
}

int jemalloc_test()
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    std::thread thread1(jemalloc, p1, N);
    thread1.join();
    printTime2(start, "thread1   mallocx.");
    for (int i = 0; i < N; ++i) {
        p1[i] = NULL;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    std::thread thread3(jemalloc, p1, N);
    std::thread thread4(jemalloc, p2, N);
    thread3.join();
    thread4.join();
    printTime2(start, "thread3/4 mallocx.");
    for (int i = 0; i < N; ++i) {
        p1[i] = NULL;
        p2[i] = NULL;
    }
    return 0;
}

int malloc_test2()
{
    printf("\nmalloc_test\n");
    malloc_test();
    printf("\njemalloc_test\n");
    jemalloc_test();
    return 0;
}


/*
Atomic
Concurrent operations on POD(Plain Old Data) , e.g. int32_t, are not safe.

The atomic library provides components for fine-grained atomic operations allowing for lockless concurrent programming.

Each atomic operation is indivisible with regards to any other atomic operation that involves the same object.

Atomic objects are free of data races.
*/
class Counter7 : public boost::noncopyable {
    //std::atomic<int> m_count = 0;
    std::atomic<int> m_count;
public:
    void add(int value) {
        m_count.fetch_add(value);
    }
    int value() {
        return m_count.load();
    }
};


/*
C++ 11 provides std::atomic<T>, and some type alias, like std::atomic_int32_t is equal to std::atomic<int32_t>.

Template parameter T require trivially copyable, which mean it should able to copy by std::memcpy.

The sizeof T decides whether std::atomic<T> is lock free:
*/


struct Counter8 {
    int64_t count = 0;
};

struct Foo4 {
    int64_t a = 0;
    int64_t b = 0;
};

void p95()
{
    std::atomic<Counter8> c;
//    assert(c.is_lock_free());
    
    std::atomic<Foo4> f;
//    assert(!f.is_lock_free());
}


/*
Concurrent Design Pattern
Singleton
Observer
Active Object
Singleton
Thread-safe singleton is hard to implement before C++11. Fortunately, in C++ 11, compiler ensures that concurrent execution shall wait for static local variable being initialized.
*/

/*If you want pointer, std::call_once can help:
*/
class Singleton {
public:
    static Singleton* instance() { 
        std::call_once(s_once_flag, &Singleton::init);
        return sp_instance;
    }
private:
    static Singleton* sp_instance;
    static std::once_flag s_once_flag;
    static void init() {
        sp_instance = new Singleton;
    }
};
static Singleton& instance() { 
    static Singleton s_instance;
    return s_instance;
}




std::atomic<int> foo (0);

void set_foo(int x) {
  foo.store(x,std::memory_order_relaxed);     // set value atomically
}

void print_foo() {
  int x;
  do {
    x = foo.load(std::memory_order_relaxed);  // get value atomically
  } while (x==0);
  std::cout << "foo: " << x << '\n';
}

static int test()
{
  std::thread first (print_foo);
  std::thread second (set_foo,10);
  first.join();
  second.join();
  return 0;
}

/*
For double-check locking, we have std::atomic in C++11, it can acts as a memory barrier:
*/
//class Singleton2 {
//public:
//    static Singleton2* instance() { 
//        Singleton2* tmp = asp_instance->load(std::memory_order_relaxed);
//        //Singleton2* tmp = asp_instance.load();
//        if (!tmp) {
//            std::lock_guard<std::mutex> lk(s_mutex);
//            tmp = instance.load();
//            if (!tmp) {
//                tmp = new Singleton2;
//                asp_instance.store(tmp, std::memory_order_relaxed);
//            }
//        }
//        return tmp;
//    }
//    static std::atomic<Singleton2*> asp_instance;
//    static std::mutex s_mutex;
//};

/*
Observer
Thread-safe Observer pattern is important in "future continuation" or "future watcher":
*/
//#include <boost/assign.hpp>
//#include <boost/typeof/typeof.hpp>
//#include <boost/thread.hpp>
//#include <boost/array.hpp>
//#include <boost/foreach.hpp>
//#include <boost/ref.hpp>
//int p96() {
//    //boost::future<int> f = boost::async([](){ return 42;});
//    //boost::future<std::string> fs = f.then([](boost::future<int> prev) {
//    boost::unique_future<int> f = boost::async([](){ return 42;});
//    boost::unique_future<std::string> fs = f.then([](boost::unique_future<int> prev) {
//        int the_answer = prev.get();
//        return std::to_string(the_answer);
//    });
//    assert(fs.get() == "42");
//}



/*
The key points to implementation are:

register weak_ptr or shared_ptr of observer to observable, so we don't need to maintains the life cycle of observer instance.
copy all observer pointers and remove expired under lock guard when notify, so we don't need to worry about registering new observers during notification.
call observer's notify method out of lock guard, so we can register new observer to observable during notification and notification won't block observable too much time.
boost::future is an example registered shared_ptr; tpool::ObservableFutureTask is an example registered weak_ptr.
*/
//void Observable::notify() {
//    std::vector<std::weak_ptr<Observer>>> to_notify;
//    {
//        std::lock_guard<std::mutex> lk(m_mutex);
//        for (const auto& wp : m_observers) {
//            if (!wp.expired()) {
//                to_notify.push_back(wp);
//            }
//        }
//        m_observers = to_notify;
//    }
//    for (const auto& wp : to_notify) {
//        auto sp = wp.lock();
//        if (sp) {
//            sp->notify();
//        }
//    }
//}



/*
Active Object
The active object design pattern decouples method execution from method invocation for objects that each reside in their own thread of control.

In some case, it can help us handle some thread un-safe modules that we can not change. It sounds like "call concurrent, execute serial".

Take counter as a simple example:
*/
class Counter9 {
    int m_count = 0;
public:
    int add(int value) { 
        m_count += value; 
        return m_count;
    }
};
/*
It's unsafe for concurrent access, we can apply active object pattern for it:

CounterProxy can concurrency access now.
*/
//Class CounterProxy {
//    Counter9 m_counter;
//    boost::serial_executor m_executor;
//Public:
//    boost::future<int> add(int value) {
//        return boost::async(m_executor, [=] {
//            return this->m_counter.add(value);
//        });
//    }
//};



/*
Other Tips
mutex is enough for most case
You don't need to use spin-lock explicitly, because mutex was implemented like spin-lock in modern os.

be wary of read-write lock
Unless the hold time for the lock is long, read-write lock will scale no better than single mutex.

Use lock-free structure only if you absolutely must
It's hard to implement or use/debug lock-free structure, even for experts.

Read reference, documentation, source code(optional) before use a thread library
Different library may have some special implementation. And we should remember that third-party lib may have bugs, even boost or other well known third-party lib.

Further Reading
Anthony Williams, C++ Concurrency in Action: Practical Multithreading, 2012
Brian Goetz, Java Concurrency in Practice, 2006
Atul S. Khot, Concurrent Patterns and Best Practices, 2018
*/


void future_test()
{
    //通过async来获取异步操作结果
    std::future<int>  result = std::async([](){ 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return 8; 
    });
    
    std::cout << "the future result : " << result.get() << std::endl;
    std::cout << "the future status : " << result.valid() << std::endl;
    try
    {
        result.wait();  //或者 result.get() ,会异常
      //因此std::future只能用于单线程中调用 ，多线程调用使用std::share_future();
    }
    catch (...)
    {
        std::cout << "get error....\n ";
    }
}


#include <chrono>               // std::chrono::milliseconds
// a non-optimized way of checking for prime numbers:
bool is_prime(int x)
{
    for (int i = 2; i < x; ++i)
        if (x % i == 0)
            return false;
    return true;
}
void future_test2()
{
    // call function asynchronously:
    std::future < bool > fut = std::async(is_prime, 444444443);
    std::cout << "std::async\n";

    // do something while waiting for function to set future:
    std::cout << "checking, please wait\n";
    //std::chrono::milliseconds span(100);
    //while (fut.wait_for(span) == std::future_status::timeout)
    //    std::cout << '.';

    bool x = fut.get();         // retrieve return value

    std::cout << "\n444444443 " << (x ? "is" : "is not") << " prime.\n";
}
/*
选择题
1. 对于一次性异步计算的结果, 以下哪个同步工具比较合适:(单选, 5分) C
A. blocking queue, B. latch, C. future, D. mutex

2. 对于生产者消费者问题, 以下哪个同步工具比较合适:(单选, 5分) D
A. blocking queue, B. latch, C. future, D. mutex

3. 以下哪个不是线程安全的实现方法:(单选, 5分) A
A. static local variable
B. thread local sotrage
C. mutual exclusion
D. stateless implementation

4. 以下的说法, 正确的是:(多选, 10分, 错选得0分, 少选得5分) E
A. boost::future::then是线程安全observer模式的体现
B. 为了实现线程安全c++类, mutable 成员变量本身应当是线程安全的
C. 跨线程引用的对象, 可以使用智能指针管理其生命周期
D. 互斥量和条件变量都是不可复制的
E. std::thread提供了cancel机制

问答题:
5. std::lock_guard和std::unique_lock有什么区别? 各有什么使用场景?(10分)
    lock_guard使用起来比较简单，除了构造函数外没有其他member function，在整个区域都有效。
    unique_guard除了lock_guard的功能外，提供了更多的member_function，相对来说更灵活一些。
    unique_guard的最有用的一组函数为： lock, unlock, try_lock, try_lock_for, try_lock_until
    通过这些函数，可以灵活的控制锁的范围和加锁的等待时间，但是资源的消耗要大一些。

6. 什么是false sharing, 写一个简单的代码示例, 并提供解决方法(15分)
当多线程修改互相独立的变量时，如果这些变量共享同一个缓存行，就会无意中影响彼此的性能，这就是伪共享。
示例代码的解决方法是使多线程访问的变量无法在同一个缓存行容纳。


7. 内存分配会成为多线程程序的性能瓶颈吗, 如果是, 写一个简单的代码示例, 并提供解决方法(20分)

编程题:
8. 以C++11标准库实现bounded blocking queue并测量其性能 (30分)
*/


void trathread_test()
{
//    p7_0();
//    p7_1();
//    p9();
//    p10();
//    p15();
//    p16();
//    px1();
//    px3();
//    p24();
//    p28();
//    p29();
//    p33a();
//    p33b();
    p34();
//    false_sharing();
//    malloc_test2();
//    future_test();
//    future_test2();
}
