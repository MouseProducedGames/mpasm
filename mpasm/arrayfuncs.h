#ifndef MPASM_MPASM_ARRAYFUNCS_H
#define MPASM_MPASM_ARRAYFUNCS_H

#include "dtfuncs.h"

#define valueop(type, op)\
size_t * length;\
size_t fb_length = 0;\
size_t memloc = IP + 4;\
getpvalue_restack(size_t, IP + 3, length, fb_length);\
for (size_t i = 0; i < length; ++i)\
{\
	type * left;\
	type * right;\
	type fb_left = 0;\
	type fb_right = 0;\
	getpvalue_restack(type, IP + 3, right, fb_right);\
	getpvalue(type, IP + 2, left, fb_left);\
	*left op= *right;\
}\
IP = memloc;

#define valuefuncop(type, funcop)\
size_t * length;\
size_t fb_length = 0;\
size_t memloc = IP + 4;\
getpvalue_restack(size_t, IP + 3, length, fb_length);\
for (size_t i = 0; i < length; ++i)\
{\
	type * left;\
	type * right;\
	type fb_left = 0;\
	type fb_right = 0;\
	getpvalue_restack(type, IP + 3, right, fb_right);\
	getpvalue(type, IP + 2, left, fb_left);\
	*left = (type)funcop(*left, *right);\
}\
IP = memloc;

#define valueconv(fromtype, totype)\
size_t * length;\
size_t fb_length = 0;\
size_t memloc = IP + 4;\
getpvalue_restack(size_t, IP + 3, length, fb_length);\
for (size_t i = 0; i < length; ++i)\
{\
	fromtype * value;\
	fromtype fb_value = 0;\
	size_t memloc = IP + 4;\
	getpvalue(fromtype, IP + 3, value, fb_value);\
	setpvalue(totype, IP + 2, value);\
}\
IP = memloc;\

#define valuepush(type)\
type * value;\
type fb_value = 0;\
size_t memloc = IP + 4;\
getpvalue(type, IP + 3, value, fb_value);\
pushpvalue(type, IP + 2, value);\
IP = memloc;

#define valuequickcall(type)\
size_t memloc = IP + 4;\
getcall<type>(\
	(syscallid)(*(uint8_t*)(&inst[IP + 2])),\
	(uint64_t)(*(uint8_t*)(&inst[IP + 3])),\
	inst, IP,\
	stk, SP,\
	memadjust, memloc\
)(stk, SP, memadjust);\
IP = memloc;

#define valuequickshortcall(type)\
size_t memloc = IP + 4;\
getquickshortcall<type>(\
	(uint64_t)(*(uint16_t*)(&inst[IP + 2])),\
	inst, IP,\
	stk, SP,\
	memadjust, memloc\
)(stk, SP, memadjust);\
IP = memloc;

#define valuesetishortcall(type)\
syscallid * value;\
syscallid fb_value = (syscallid)0;\
size_t memloc = IP + 4;\
getpvalue(syscallid, IP + 2, value, fb_value);\
IShortCall = *value;\
IP = memloc;

#define valueshortcall(type)\
size_t memloc = IP + 4;\
getshortcall<type>(inst, IP, stk, SP, memadjust, memloc)(stk, SP, memadjust);\
IP = memloc;

#define valuesyscall(type)\
syscallid * syscall;\
syscallid fb_syscall = (syscallid)0;\
size_t memloc = IP + 4;\
getpvalue_restack(syscallid, IP + 2, syscall, fb_syscall);\
getsyscall<type>(*syscall, inst, IP, stk, SP, memadjust, memloc)(stk, SP, memadjust);\
IP = memloc;

#endif // !MPASM_MPASM_ARRAYFUNCS_H
