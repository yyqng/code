#include "trathread.h"

const int SIZE = 10;



/* ***************************************** Thread Object **********************
Create thread
There are two styles to create a thread in OOP language.
One is like QThread, inherit QThread and override run method then call start launch:
*/
class DeepThroughtThread : public QThread {
    Q_OBJECT
    virtual void run() override {
        the_answer = 42;
    }
    int the_answer = 0;
};

void p6()
{
	DeepThroughtThread* thread = new DeepThroughtThread(...);
	thread->start();
	thread->wait();
	assert(thread->the_answer == 42);
}


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
	thread.join();
	assert(the_answer == 42);
}


/*
Life cycle of thread object
Thread object is noncopyable, if compiler supports c++11, it's moveable;

Thread object is an agent to start and manage system thread, not the system thread itself. If we don't need to manage thread anymore, we can detach it:

	std::thread thread(deep_throught, std::ref(the_answer));
	thread.detach();
We don't suggest to detach, because when main thread exits, the process will exit with it, all child thread will be cleaned up. It means your child thread may ends its work in a weird state.

To prevent this issue, we need to join child threads, and the thread can not join after detached.

When the destructor of thread object is called, if its associated thread is still running, std::terminate will be call.
*/



/*
Some thread libraries support interruption, like boost::thread:

There are many interruption pointers other than boost::this_thread::interruption_point(), see the reference for details.
https://www.boost.org/doc/libs/1_54_0/doc/html/thread/thread_management.html#thread.thread_management.tutorial.interruption
*/
void p9()
{
	auto history = []() {
		try {
			for (;;) {
				repeating_itself();
				boost::this_thread::interruption_point();
			}
		} catch (boost::thread_interrupted&) {
			return;
		}
	};

	boost::thread tr(history);
	// we learn from it
	tr.interrupt();
	tr.join();
}



/*
tpool supports CancelableThread, its mechanism likes:
*/
void p10()
{
	bool is_cancel_request = false;
	auto check_cancellation = [&] {
		if (is_cancel_request) {
			throw std::exception("cancelled");
		}
	}
	auto history = [&]() {
		try {
			for (;;) {
				repeating_itself();
				check_cancellation();
			}
		} catch (std::exception&) {
			return;
		}
	};

	std::thread tr(history);
	// we learn from it
	is_cancel_request = true;
	tr.join();
}


/*
We can only stop a thread in specified interruption point and check cancellation point.
We can not promise the thread will stop as soon as you call interruption or cancel.
*/



/* ***************************************** Synchronization **********************
Mutex
A mutex object facilitates protection against data races and allows thread-safe synchronization of data between threads.

A thread obtains ownership of a mutex object by calling one of the lock functions and relinquishes ownership by calling the corresponding unlock function.

One mutex can only be owned by one thread at a time, once a thread locks a mutex, other thread which trying to like the mutex will block until the lock is released.

mutex usually has the following interface:
class mutex : boost::noncopyable
{
    void lock();
    void unlock();
    bool try_lock();
};
*/
void p15()
{
	int count = 0;
	std::mutex mtx;

	auto counter = [&]() {
		for (int i = 0; i < 42; i++) {
			mtx.lock();
			count++;
			mtx.unlock();
		}
	};

	std::thread tr1(counter);
	std::thread tr2(counter);

	tr1.join();
	tr2.join();
	assert(count == 84);
}




/*
lock_guard
For possible exceptions or forgetting to unlock, mutex should use with RAII objects, like std::lock_guard:
std::lock_guard will mutex in constructor and unlock in destructor. So the mutex will unlock when the lock_guard instance is out of scope.
*/
void p16()
{
	auto counter = [&]() {
		for (int i = 0; o < 42; i++) {
			std::lock_guard<std::mutex> lk(mtx);
			count++;
		}
	};
}





/*
In tpool, tpool::sync::MutexLocker provides the same functionality:
*/
class MutexLocker : private boost::noncopyable {
public:
    explicit MutexLocker(Mutex& m) : m_mutex(m) { m_mutex.Lock(); }

    ~MutexLocker() { m_mutex.Unlock(); }

private:
    Mutex& m_mutex;
};

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
private:
    void add_internal() {
        std::lock_guard<std::recursive_mutex> lk(m_mutex);
        m_count++;
    }
    std::recursive_mutex m_mutex;
    int m_count;
};

/*
Recursive Mutex is dangerous for beginner
std::recursive_mutex allows class state be modified during the mutex is locked.
*/
class Counter;
class Proxy {
    Counter& m_counter;
    void hook() {
        m_counter.add();
    }
};

class Counter : private boost::noncopyable {
public:
    Counter(): m_count(0){}
    void add() {
        std::lock_guard<std::recursive_mutex> lk(m_mutex);
        add_internal();
    }
private:
    void add_internal() {
        std::lock_guard<std::recursive_mutex> lk(m_mutex);
        m_count++;
        if (m_count < 42) {
            m_proxy->hook();
        }
    }
    std::recursive_mutex m_mutex;
    int m_count;
    Proxy m_proxy;
};


/*
Pass Unnamed lock_guard as Argument
Don't use recursive mutex as possible as you can, deadlock is better than unexpected state.

But we still need to guarantee that private methods are called correctly with lock.

We can pass the lock_guard as extra argument explicitly:
*/
class Counter : private boost::noncopyable {
public:
    Counter(): m_count(0){}
    void add() {
        std::lock_guard<std::mutex> lk(m_mutex);
        add_internal(lk);
    }
private:
    void add_internal(const std::lock_guard&) {
        m_count++;
    }
    std::mutex m_mutex;
    int m_count;
};


/*
Condition Variable
Condition variable provide a mechanism for one or many threads to wait for notification from another thread that a particular condition has become true.

usually has the following interface:
*/
class condition_variable : boost::noncopyable
{
    void wait(mutex&);
    void notify_one();
    void notify_all();
};


/*
condition_variable must use together with mutex (which protects the particular condition).

To make sure user passes the right mutex to condition_variable, some libraries(like tpool) acquire the mutex as construction parameter:
*/
class condition_variable : boost::noncopyable
{
    condition_variable(mutex&)
    void wait();
    void notify_one();
    void notify_all();
private:
    mutex& m_mutex;
};


/*
AS we talk before, we use mutex with RAII objects, so c++11/boost accepts unique_lock instead of mutex directly.
unique_lock is similar to lock_guard, but unique_lock can lock and unlock many time.
*/
class condition_variable : boost::noncopyable
{
    void wait(std::unique_lock<std::mutex>&);
    void notify_one();
    void notify_all();
};


/*
Example to use condition_variable:
*/
void p24()
{
	int the_answer = -1;
	bool the_answer_is_ready = false; // the condition we waiting for
	std::mutex mtx; // protect the_answer and the_answer_is_ready
	std::condition_variable cond;

	std::thread tr([&]() {
		// lock condition than modify
		std::lock_guard<std::mutex> lk;
		the_answer = 42;
		the_answer_is_ready = true;
		// notify waiters after condition modified
		cond.notify_all();
	});

	std::unique_lock<std::mutex> ulk(mtx);
	while (!the_answer_is_ready) { // keep waiting when condition is not what we want
		// wait contains three step: 
		// 1. unlock ulk
		// 2. hang this thread until being notified
		// 3. relock ulk after notified
		cond.wait(ulk);
	}
	assert(the_answer_is_ready == true);
	assert(the_answer == 42);
	tr.join();
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


/*
Semaphore
A (Counting) Semaphore is a synchronization tool that can control access shared resources.
*/
class semaphore : public boost::noncopyable {
public:
    semaphore(unsigned int limit, unisgned int count);
    void acquire(unsigned int diff = 1);
    void release(unsigned int diff = 1);
};

/*
Binary semaphore sometimes use as mutex + condition_variable:
*/
void p28()
{
	int the_answer = -1;
	semaphore sem(1, 1);
	std::thread tr([&]() {
		the_answer = 42;
		sem.release();
	});
	sem.acquire();
	assert(42 == the_answer);
}

/*
producer-consumer problem can solve using semaphore:
*/
void p29()
{
	static const int N = 100;                       
	std::mutex mtx;                                   
	semaphore sem_slot(N, 0);                     
	semaphore sem_product(N, N);                  
	class production;
	void producer() {
		production item;
		while (true) {
			item = produce_item();
			sem_slot.acquire();
			{
				std::lock_guard<std::mutex> lk(mtx);
				insert_item(item);  
			}                              
			sem_product.release();    
		}    
	}
	void consumer() {
		production item;
		while (true) {
			sem_product.acquire();
			{
				std::lock_guard<std::mutex> lk(mtx);
				item = remove_item();  
			}                          
			sem_slot.release();         
			consume_item(item);                       
		}
	}
}



/*
It can also apply to limit the concurrent access to one resources, e.g. limit connection to server.
*/
void p30()
{
	static const int g_limit = 100;
	semaphore sem_limit(s_limit, 0); 

	while (true) {
		sem_limit.acquire();
		connect_to_server();
		do_something_with_the_connection();
		disconnect();
		sem_limit.release();
	}
}





/*
Be careful with semaphore
Semaphore achieved same effect as mutex + condition variable.
Without RAII object, easy to forget release.
Binary semaphore is confused with mutex.
Different from mutex, semaphore can acquire in one thread but release in another thread.
boost doesn't provide semaphore, tpool and c++ 20(std::counting_semaphore) provided.
*/


/*
Future/Promise
What if it throws an exception while calculating the_answer?
*/
void p32()
{
	int the_answer = -1;
	bool the_answer_is_ready = false; // the condition we waiting for
	std::mutex mtx; // protect the_answer and the_answer_is_ready
	std::condition_variable cond;

	std::thread tr([&]() {
		// lock condition than modify
		std::lock_guard<std::mutex> lk;
		the_answer = 42;
		the_answer_is_ready = true;
		// notify waiters after condition modified
		cond.notify_all();
	});

	std::unique_lock<std::mutex> ulk(mtx);
	while (!the_answer_is_ready) { // keep waiting when condition is not what we want
		// wait contains three step: 
		// 1. unlock ulk
		// 2. hang this thread until being notified
		// 3. relock ulk after notified
		cond.wait(ulk);
	}
	assert(the_answer_is_ready == true);
	assert(the_answer == 42);
	tr.join();
}




/*
In previous example, we declared value(the_answer), state(the_answer_is_ready), mutex(mtx), condition variable(cond), thread(tr), and maybe need handle exception. This complexity usage pattern is hard for beginner.

So people provide future/promise:
*/

void p33()
{
	boost::promise<int> pr;
	boost::future<int> fu = pr.get_future();
	boost::thread tr([](boost::promise<int>& ret) {
		ret.set_value(42);
	}, boost::ref(pr));
	tr.detach();
	assert(fu.get() == 42);
}




/*
Further more, we don't want to declare promise and thread, we can use free function async to simplify it:
Each async will launch a new thread.
*/

void p34()
{
	std::future<int> fu = std::async([](){ return 42;});
	assert(fu.get() == 42);
}




/*
Future/Promise are proxy for async result
promise usually has the following interface:
*/
template<typename T>
class promise : boost::noncopyable{
public:
    promise();
    ~promise();
    future<T> get_future();
    void set_value(const T& value);
    void set_exception(boost::exceptional_ptr p);
};

/*
future usually has the following interface:
promise and future shared same internal state, which contains value, state, mutex condition variable and exception we talk before.
*/
template<typename T>
class future {
     friend class promise<T>;
public:
     T get();
     bool is_ready() const;
     bool has_exception() const;
     bool has_value() const;
     void wait() const;
};

/*
Future can be a default tool for one-time synchronization
Most case can solve by one future, if can't, use two futures!
Some libraries didn't provide future/promise, e.g. ancient java, tpool. But they also provide similar tool FutureTask, which can use in thread pool:

If two futures still insufficient: Barrier, Latch or Blocking Queue
*/
void p37()
{
	tpool::LThreadPool& pool = tpool::GetThreadPool();
	tpool::FutureTask<int>::Ptr task = pool.AddFutureTask([](){ return 42;});
	assert(task.GetResult() == 42);
}




/*
Barrier
A barrier is a synchronization point between multiple threads.

The barrier is configured for a particular number of threads (n), and as threads reach the barrier they must wait until all n threads have arrived.

Once the n-th thread has reached the barrier, all the waiting threads can proceed, and the barrier is reset.
*/

void p38()
{
	int many_anwer[5];
	boost::barrier br(5+1); // thread number to rendezvous, add main thread here

	for (int& answer: many_anwer) {
		boost::thread tr([&]() {
			answer = 42;
			br.wait();
		});
		tr.detach();
	}
	br.wait(); // threads finished after this wait
}




/*
Latch
Latches are a thread co-ordination mechanism that allow one or more threads
to block until one or more threads have reached a point.

boost provides barrier & latch, c++20 also;
tpool provides CyclicBarrier & CountDownLatch.
*/

void p7()
{
	int many_anwer[5];
	boost::latch lt(5); // worker number to be cound down, no need main thread

	for (int& answer: many_anwer) {
		boost::thread tr([&]() {
			answer = 42;
			lt.count_down();
		});
		tr.detach();
	}
	lt.wait(); // threads may finished before this wait
}




/*
Blocking Queue
Blocking queue is simplest implementation of thread safe queue, blocking in pop if queue is empty.

Please notice that size() and empty() are meaningless in multi-thread programming.
*/
template<typename T>
class blocking_queue : boost::noncopyable {
    std::queue<T> m_queue;
    std::condition_variable m_cond;
    mutable std::mutex m_mutex;
public:
    blocking_queue() {}
    void push(const T& val);
    void pop(T& val);
    bool try_pop(const T& val);
    size_t size() const;
    bool empty() const;
};




/*
Bounded Blocking Queue
Similar to blocking queue, but the size is limited, which means that push will also block if buffer is full.

Producer-Consumer problem by bounded blocking queue:
*/
static const int N = 100;  
class production;
bounded_blocking_queue<production> queue(N);
std::thread producer([&]() {
    production item;
    while (true) {
        item  = produce_item();
        queue.push(item);
    }
});

std::thread consumer([&]() {
    production item;
    while (true) {
        queue.pop(item);
        consume_item(item);  
    }
});



/* ***************************************** Synchronization **********************
Task based execution
We know that thread creation and scheduling are expensive. For computationally intensive tasks, create thread frequently is not worth it.

To reuse threads, we create thread pool:
*/
typedef std::function<void()> task_type;
blocking_queue<task_type> task_queue;
std::thread worker_thread([&]() {
    task_type task;
    while (true) {
        task_queue.pop(task);
        if (task) {
            task();
        }
    }
});
std::vector<int> result(233);
for (int i = 0; i < 233; i++) {
    task_queue.push([i, &result]{}{
        result[i] = 42;
    });
}
worker_thread.join(); // BUG: block forever


/*
We have different philosophy about how to define task:

boost use boost::function<void()> as task. task queue stores boost::function<void()> directly.
Some other library(like tpool) define a task_base class, user inherit from it. task queue store smart pointers of task base:
*/

struct task_base {
    virtual ~task_base(){}
    virtual void run() = 0;
};
typedef std::shared_ptr<task_base> task_type;

blocking_queue<task_type> task_queue;
std::thread worker_thread([&]() {
    task_type task;
    while (true) {
        task_queue.pup(task);
        if (task) {
            task->run();
        }
    }
});

struct function_task: public task_base {
    std::function<void()> func;
    function_task(const std::function<void()>& _func): func(_func){}
    virtual void run() override {
        if (func) {
            func();
        }
    }
}

std::vector<int> result(233);
for (int i = 0; i < 233; i++) {
    task_type task(new function_task([i, &result]() {
        result[i] = 42;
    }))
    task_queue.push(task);
}
worker_thread.join(); // BUG: block forever

void p7()
{
}




/*
Thread Pool
Thread pool is multiple threads share a task queue.

But there are some questions to be discuss:
how to close a task queue
how to destruct a thread pool instance
how to handle exception from task
*/

/*
Closing task queue
In simplest implementation of blocking queue, task queue can not be closed because of pop is a blocking call.

There are two ways to close a task queue:

one is add a flag in blocking queue, then always check this flag when push and pop called, if the flag was set to close, return without block or throw exception. boost is an example.
the other called "poison pill", it means when worker thread ends itself when it pulled a special task from queue. tpool is an example.
*/

/*
Destruction of thread pool
What should be done when we want to destruct a thread pool?

close the task queue?
cancel or interrupt running tasks?
give up task pending on task queue?
Take tpool as example, it close the task queue, join worker thread, so pending tasks will be finished.

Global thread pool is different. In tpool, global thread pool will stop worker threads, which means trying to cancel all running tasks and give up pending tasks.

boost thread pool will close task queue , then interrupt and join worker threads. But no interrupt point there, so pending task will be finished.
*/

/*
Exception handling
What if task throws an exception?

In tpool, Run method will catch the exception(actually, user override DoRun, which called by Run), so worker threads won't stop by exception.

boost is different, std::terminate() will be called if task throws. But we usually use future in boost, future can store exception(use std::exception_ptr or boost::exception_ptr).
*/

/*
Basic Thread Pool Implementation
*/
class basic_thread_pool {
    boost::thread_group m_threads;
    boost::concurrent::sync_queue<task_type> m_tasks;
public:
    basic_thread_pool(size_t thread_count = boost::thread::hardware_concurrency() + 1) {
        try {
            for (size_t i = 0; i < thread_count; ++i) {
                m_threads.create_thread(boost::bind(&basic_thread_pool::worker_thread, this));
            }
        } catch(...) {
            close();
            throw;
        }
    }
    ~basic_thread_pool() {
        close();
        join();
    }
public:
    void close() {
        m_tasks.close();
    }
    bool closed() const{
        return m_tasks.closed();
    }
    void submit(task_type& w) {
        m_tasks.push(w);
    }

private:
    void join() {
        m_threads.interrupt_all();
        m_threads.join_all();
    } 
    void worker_thread() {
        try {
            for (;;) {
                work task;
                try {
                    boost::concurrent::queue_op_status st = m_tasks.wait_pull(task);
                    if (st == boost::concurrent::queue_op_status::closed) {
                        return;
                    }
                    task();
                } catch (boost::thread_interrupted&) {
                    return;
                }
            } // for
        } catch (...) {
            std::terminate();
            return;
        }
    }
};

/*
Basic Thread Pool is Easy to Deadlock
For thread pool with fixed thread number, it easy to dead lock:

Waiting for sub tasks blocks current worker thread, if all worker threads waiting sub tasks, sub tasks can't be executed.
*/
template<typename Ex = basic_thread_pool>
int fib(Ex& ex, int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        boost::future<int> f1 = boost::async(ex, fib, n-1);
        boost::future<int> f2 = boost::async(ex, fib, n-2);
        return f1.get() + f2.get();
    }
}

/*
Reschedule Until
Help to execute other tasks until sub tasks finished:
*/
template <typename Pred>
bool basic_thread_pool::reschedule_until(const Pred& pred) {
    do {
        if (!try_executing_one()) {
            return false;
        }
    } while (!pred());
    return true;
}
bool basic_thread_pool::try_executing_one() {
    try {
        work task;
        if (m_tasks.try_pull(task) == queue_op_status::success) {
            task();
            return true;
        }
        return false;
    } catch (...) {
        std::terminate();
    }
}


/*
So we are not blocking wait:
*/
int fib(Ex& ex, int n) {
    if (n = 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        boost::future<int> f1 = boost::async(ex, fib, n-1);
        boost::future<int> f2 = boost::async(ex, fib, n-2);
        ex.reschedule_until([&]()->bool{
            return f1.is_ready() && f2.is_ready();
        });
        return f1.get() + f2.get();
    }
}


/*
Scheduler
Scheduler maintains timed tasks, it means execute a task after a time duration or execute a task at a time point.
e.g. do something after 1 second, do other thing at 8:20.

In simplest case, scheduler is similar to thread pool but it only have one worker thread. Its task queue is sorted by time point(time duration will also convert to time point once it submitted), its condition variable wait for the time point form the top of task queue.
Submitting a new task will also wake up the condition variable, because the new task may have the nearest time point.
*/
void p54()
{
	boost::executors::scheduler<boost::chrono::steady_clock> sc;
	sc.submit_after([] {
		std::cout << "hello world" << std::endl;
	}, boost::chrono::seconds(5));
}




/*
The task may take long time to delay other tasks, so we can use with thread pool, submit the task to thread pool when the time point is reached.

In tpool , we provides tpool::Timer as scheduler.
*/

void p55()
{
	scheduler sc;
	basic_thread_pool ex;
	sc.on(ex).after(boost::chrono::milliseconds(500)).submit([](){
		std::cout << "hello world" << std::endl;
	});
}




/*
Thread or Thread Pool?
For long running tasks, use thread.
For disk I/O task, multi-thread can't help, but can reduce blocking.
For socket I/O task, multi-thread may help, but we suggest select/epoll, coroutine.
For CPU-bound task, use global thread pool.
For detailed discussion about executor, please ref to Appendix: Executor & Fork/Join.
*/


void trathread_test()
{
    p55();
}
