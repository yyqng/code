/*
 * thread_test.cpp
 *
 * Copyright 2013 叶剑飞
 *
 * 编译命令：
 *     g++ thread_test.cpp -o thread_test -Wall -std=c++11 -pedantic-errors -pthread
 */

#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int threadtest(int argc, char *argv[]);
