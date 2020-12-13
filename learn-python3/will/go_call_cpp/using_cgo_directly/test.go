
package main

// #cgo LDFLAGS: -L. -lfoo
// #cgo CFLAGS: -I.
// #include <stdio.h>
// int foo_say_hi();
// typedef int (*intFunc) ();
//
// int
// bridge_int_func(intFunc f)
// {
//		return f();
// }
//
// int fortytwo()
// {
//	    return 42;
// }
import "C"
import "fmt"

func main() {
	C.foo_say_hi()
	f := C.intFunc(C.fortytwo)
	fmt.Println(int(C.bridge_int_func(f)))
	// Output: 42
}