// Code generated by cmd/cgo; DO NOT EDIT.

package main

import "unsafe"

import _ "runtime/cgo"

import "syscall"

var _ syscall.Errno
func _Cgo_ptr(ptr unsafe.Pointer) unsafe.Pointer { return ptr }

//go:linkname _Cgo_always_false runtime.cgoAlwaysFalse
var _Cgo_always_false bool
//go:linkname _Cgo_use runtime.cgoUse
func _Cgo_use(interface{})
type _Ctype_int int32

type _Ctype_intFunc *[0]byte

type _Ctype_void [0]byte

//go:linkname _cgo_runtime_cgocall runtime.cgocall
func _cgo_runtime_cgocall(unsafe.Pointer, uintptr) int32

//go:linkname _cgo_runtime_cgocallback runtime.cgocallback
func _cgo_runtime_cgocallback(unsafe.Pointer, unsafe.Pointer, uintptr, uintptr)

//go:linkname _cgoCheckPointer runtime.cgoCheckPointer
func _cgoCheckPointer(interface{}, ...interface{})

//go:linkname _cgoCheckResult runtime.cgoCheckResult
func _cgoCheckResult(interface{})
//go:linkname __cgo_fortytwo fortytwo
//go:cgo_import_static fortytwo
var __cgo_fortytwo byte
var _Cfpvar_fp_fortytwo unsafe.Pointer = (unsafe.Pointer)(unsafe.Pointer(&__cgo_fortytwo))

//go:cgo_import_static _cgo_e4aea1041496_Cfunc_bridge_int_func
//go:linkname __cgofn__cgo_e4aea1041496_Cfunc_bridge_int_func _cgo_e4aea1041496_Cfunc_bridge_int_func
var __cgofn__cgo_e4aea1041496_Cfunc_bridge_int_func byte
var _cgo_e4aea1041496_Cfunc_bridge_int_func = unsafe.Pointer(&__cgofn__cgo_e4aea1041496_Cfunc_bridge_int_func)

//go:cgo_unsafe_args
func _Cfunc_bridge_int_func(p0 *[0]byte) (r1 _Ctype_int) {
	_cgo_runtime_cgocall(_cgo_e4aea1041496_Cfunc_bridge_int_func, uintptr(unsafe.Pointer(&p0)))
	if _Cgo_always_false {
		_Cgo_use(p0)
	}
	return
}
//go:cgo_import_static _cgo_e4aea1041496_Cfunc_foo_say_hi
//go:linkname __cgofn__cgo_e4aea1041496_Cfunc_foo_say_hi _cgo_e4aea1041496_Cfunc_foo_say_hi
var __cgofn__cgo_e4aea1041496_Cfunc_foo_say_hi byte
var _cgo_e4aea1041496_Cfunc_foo_say_hi = unsafe.Pointer(&__cgofn__cgo_e4aea1041496_Cfunc_foo_say_hi)

//go:cgo_unsafe_args
func _Cfunc_foo_say_hi() (r1 _Ctype_int) {
	_cgo_runtime_cgocall(_cgo_e4aea1041496_Cfunc_foo_say_hi, uintptr(unsafe.Pointer(&r1)))
	if _Cgo_always_false {
	}
	return
}
