package main

// #cgo LDFLAGS: -L. -lfoo
// #include "interface.h"
import "C"
import (
	"fmt"
)

type GoPersion struct {
	foo C.Persion
}

func New(age int, name string) GoPersion {
	var ret GoPersion
	age_c := C.int(age)
	name_c := C.CString(name)
	ret.foo = C.PersionInit(age_c, name_c)
	return ret
}
func (f GoPersion) Free() {
	C.PersionFree(f.foo)
}
func (f GoPersion) sayHi() {
	C.sayHi(f.foo)
}

func (f GoPersion) info() string {
	res := C.info(f.foo)
	go_str_res := C.GoString(res)

	return go_str_res
}

func main() {
	p := New(18, "Tom")
	p.sayHi()
	info := p.info()
	fmt.Println(info)

	p.Free()
}
