#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Observer.h"
class Observer;
class Observable
{
    public:
        Observable(){}
        virtual ~Observable(){}
        void register(Observer *x);
        void unregister(Observer *x);
        void notify();//通知观察者
        virtual void status(const std::string &s);//set状态
        virtual std::string status();//get状态
    private:
        std::vector<Observer*> __observers;//记录所有的观察者
    protected:
        std::string __status;
};
#endif
