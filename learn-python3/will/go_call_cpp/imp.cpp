#include <iostream>
#include <sstream>
#include "imp.hpp"

CppPersion::CppPersion(int age, const std::string& name): _age(age), _name(name) {
	std::cout << "==class construction" << std::endl;
}

CppPersion::~CppPersion() {
	std::cout << "==class deconstruction" << std::endl;
}

void CppPersion::sayHi(void) {
	std::cout<< "Hi, I am " << this->_name << ", age " << this->_age<<std::endl;
}

std::string CppPersion::info() const {
	std::stringstream ss;
	ss << "Name:" << _name << ", age:" << _age;
	return ss.str();
}