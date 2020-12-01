#ifndef _IMP_H_
#define _IMP_H_
#include <string>

class CppPersion {
public:
	CppPersion(int _a, const std::string& name);
	~CppPersion();
	void sayHi();
	std::string info() const;

private:
	int _age;
	std::string _name;
};

#endif
