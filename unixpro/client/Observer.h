#ifndef __OBSERVER_H__
#define __OBSERVER_H__
#include <iostream>
#include <string>
#include "Observable.h"
class Observable;
class Observer//抽象类
{
    public:
        virtual ~Observer();
        virtual void update()=0;//纯虚函数

        void observe(Observable *s);//订阅
    protected:
        Observable* __subject;//订阅的对象
};
#endif
