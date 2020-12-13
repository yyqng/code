#include "imp.hpp"
#include "interface.h"

Persion PersionInit(int age, char* name) {
	CppPersion * ret = new CppPersion(age, name);
	return (void*)ret;
}

void PersionFree(Persion raw_ptr) {
	CppPersion * ins = (CppPersion*)raw_ptr;
	delete ins;
}

void sayHi(Persion raw_ptr) {
	CppPersion * ins = (CppPersion*)raw_ptr;
	ins->sayHi();
}

const char* info(Persion raw_ptr) {
	CppPersion * ins = (CppPersion*)raw_ptr;
	std::string res = ins->info();
	return res.c_str();
}

