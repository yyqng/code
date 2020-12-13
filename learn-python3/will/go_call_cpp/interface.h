#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

	typedef void* Persion;
	Persion PersionInit(int age, char* name);
	void PersionFree(Persion);
	void sayHi(Persion);
	const char *info(Persion);

#ifdef __cplusplus
}
#endif

#endif
