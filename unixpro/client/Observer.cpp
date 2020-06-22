#include "Observer.h"
#include "Observerable.h"

void Observer::observe(Observable*s)
{
    s->__register(this);//类似于注册回调函数，这里传递的是观察者地址。
    __subject=s;//观察者通过指针访问到它观察的对象
}
Observer::~Observer()
{
    __subject->__unregister(this);
}
