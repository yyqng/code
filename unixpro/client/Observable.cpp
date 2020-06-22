#include "Observable.h"
#include "Observer.h"

void Observable::notify()
{
    for(int i=0;i<__observers.size();++i)//通知所有观察者
    {
        Observer * x = __observers[i];
        if(NULL!=x)
        {
            x->update();
        }
    }
}

void Observable::__register(Observer*x)
{
    __observers.push_back(x);
}

void Observable::__unregister(Observer *x)
{
    std::vector<Observer*>::iterator it = std::find(__observers.begin(),__observers.end(),x);
    if(it != __observers.end())//found!
    {
        std::swap(*it,__observers.back());
        __observers.pop_back();
    }
}

void Observable::status(const std::string &s)
{
    __status=s;
}
std::string Observable::status()
{
    return __status;
}



#include "Observer.h"
#include "Observable.h"
class BlogObserver : public Observer//订阅博客的人
{
    private:
    std::string __name;
    public:
    BlogObserver(std::string name):__name(name){}
    virtual void update();
};

class BlogCSDN : public Observable//博主
{
    private:
        std::string __name;//blog name
    public:
        BlogCSDN(std::string name ):__name(name){}
        ~BlogCSDN(){}
        void status(const std::string &s);
        std::string status(); 
};


void BlogCSDN::status(const std::string &s)//重写，更新博客
{
    __status="Blog Name: "+__name+" Content: "+s;

}

std::string BlogCSDN::status()
{
    return __status;
}


void BlogObserver::update()//更新（收到消息）
{
    std::string status=__subject->status();
    std::cout<<status<<std::endl;
    std::cout<<__name<<" is notified"<<std::endl;
}


int observer_test()
{
    Observer * p = new BlogObserver("SomeOne");//观察者1号
    Observer * q = new BlogObserver("SomeOne2");//观察者2号
    Observable *sub1= new BlogCSDN("zhangxiao93") ;//博主

    sub1->status("UNIX Network Programming(1)");//博主更新博文

    //观察者订阅
    p->observe(sub1);
    q->observe(sub1);
    sub1->notify();//通知所有观察者

    delete p;
    delete q;
    delete sub1;
    return 0;
}
