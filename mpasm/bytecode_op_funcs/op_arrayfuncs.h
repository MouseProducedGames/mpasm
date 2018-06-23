/* 
 * Copyright 2018 Mouse-Produced Games.
 * Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
 */

#ifndef MPASM_MPASM_ARRAYFUNCS_H
#define MPASM_MPASM_ARRAYFUNCS_H

#define valueop(type, op)\
size_t * length;\
size_t memloc = IP + 4;\
getpvalue_restack(size_t, IP + 3, length);\
for (size_t i = 0; i < length; ++i)\
{\
	type * left;\
	type * right;\
	getpvalue_restack(type, IP + 3, right);\
	getpvalue(type, IP + 2, left);\
	*left op= *right;\
}\
IP = memloc;

#define valuefuncop(type, funcop)\
size_t * length;\
size_t memloc = IP + 4;\
getpvalue_restack(size_t, IP + 3, length);\
for (size_t i = 0; i < length; ++i)\
{\
	type * left;\
	type * right;\
	getpvalue_restack(type, IP + 3, right);\
	getpvalue(type, IP + 2, left);\
	*left = (type)funcop(*left, *right);\
}\
IP = memloc;

#define valueconv(fromtype, totype)\
size_t * length;\
size_t memloc = IP + 4;\
getpvalue_restack(size_t, IP + 3, length);\
for (size_t i = 0; i < length; ++i)\
{\
	fromtype * value;\
	size_t memloc = IP + 4;\
	getpvalue(fromtype, IP + 3, value);\
	setpvalue(totype, IP + 2, value);\
}\
IP = memloc;\

#define valuepush(type)\
type * value;\
size_t memloc = IP + 4;\
getpvalue(type, IP + 3, value);\
pushpvalue(type, IP + 2, value);\
IP = memloc;

#define valuequickcall(type)\
size_t memloc = IP + 4;\
getcall<type>(\
	(syscallid)(*(uint8_t*)(&inst[IP + 2])),\
	(uint64_t)(*(uint8_t*)(&inst[IP + 3])),\
	inst, IP,\
	stk, SP,\
	memadjust\
)(stk, SP, memadjust);\
IP = memloc;

#define valuequickshortcall(type)\
size_t memloc = IP + 4;\
getquickshortcall<type>(\
	(uint64_t)(*(uint16_t*)(&inst[IP + 2])),\
	inst, IP,\
	stk, SP,\
	memadjust\
)(stk, SP, memadjust);\
IP = memloc;

#define valuesetishortcall(type)\
syscallid * value;\
size_t memloc = IP + 4;\
getpvalue(syscallid, IP + 2, value);\
IShortCall = *value;\
IP = memloc;

#define valueshortcall(type)\
size_t memloc = IP + 4;\
getshortcall<type>(inst, IP, stk, SP, memadjust, memloc)(stk, SP, memadjust);\
IP = memloc;

#define valuesyscall(type)\
uint64_t * syscall;\
size_t memloc = IP + 4;\
getpvalue_restack(uint64_t, IP + 2, syscall);\
getsyscall<type>((syscallid)(*syscall), inst, IP, stk, SP, memadjust, memloc)(stk, SP, memadjust);\
IP = memloc;

#endif // !MPASM_MPASM_ARRAYFUNCS_H
