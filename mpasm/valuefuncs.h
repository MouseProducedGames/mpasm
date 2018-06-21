#ifndef MPASM_MPASM_VALUEFUNCS_H
#define MPASM_MPASM_VALUEFUNCS_H

#include "dtfuncs.h"
#include "ptrfuncs.h"

#define valueop(type, op)\
type * left;\
type * right;\
type fb_left = 0;\
type fb_right = 0;\
size_t memloc = IP + 4;\
getpvalue_restack(type, IP + 3, right, fb_right);\
getpvalue(type, IP + 2, left, fb_left);\
*left op= *right;\
IP = memloc;

#define valuefuncop(type, funcop)\
type * left;\
type * right;\
type fb_left = 0;\
type fb_right = 0;\
size_t memloc = IP + 4;\
getpvalue_restack(type, IP + 3, right, fb_right);\
getpvalue(type, IP + 2, left, fb_left);\
*left = (type)funcop(*left, *right);\
IP = memloc;

#define valueconv(fromtype, totype)\
fromtype * value;\
fromtype fb_value = 0;\
size_t memloc = IP + 4;\
getpvalue(fromtype, IP + 3, value, fb_value);\
setpvalue(totype, IP + 2, value);\
IP = memloc;

#define valuegosub(type)\
uint64_t * pnewIP;\
uint64_t fb_pnewIP = 0;\
uint64_t memloc = IP + 4;\
getpvalue_restack(uint64_t, IP + 2, pnewIP, fb_pnewIP) \
uint64_t newIP = *pnewIP;\
Run(\
	inst,\
	newIP,\
	stk,\
	SP,\
	memadjust\
);\
IP = memloc;

#define valuejmp(type)\
uint64_t * pnewIP;\
uint64_t fb_pnewIP = 0;\
uint64_t memloc = IP + 4;\
getpvalue_restack(uint64_t, IP + 2, pnewIP, fb_pnewIP) \
uint64_t newIP = *pnewIP;\
IP = newIP;

#define valuejmpif(type)\
uint64_t * pnewIP;\
uint64_t fb_pnewIP = 0;\
type * pjmpcheck;\
type fb_pjmpcheck = 0;\
uint64_t memloc = IP + 4;\
getpvalue_restack(uint64_t, IP + 2, pnewIP, fb_pnewIP)\
getpvalue_restack(type, IP + 3, pjmpcheck, fb_pjmpcheck)\
if (*pjmpcheck)\
{\
	uint64_t newIP = *pnewIP;\
	IP = newIP;\
}\
else\
{\
	IP = memloc;\
}

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
uint64_t * value;\
uint64_t fb_value = (uint64_t)0;\
size_t memloc = IP + 4;\
getpvalue(uint64_t, IP + 2, value, fb_value);\
IShortCall = (syscallid)(*value);\
IP = memloc;

#define valueshortcall(type)\
size_t memloc = IP + 4;\
getshortcall<type>(inst, IP, stk, SP, memadjust, memloc)(stk, SP, memadjust);\
IP = memloc;

#define valuesyscall(type)\
uint64_t * syscall;\
uint64_t fb_syscall = (uint64_t)0;\
size_t memloc = IP + 4;\
getpvalue_restack(uint64_t, IP + 2, syscall, fb_syscall);\
getsyscall<type>((syscallid)(*syscall), inst, IP, stk, SP, memadjust, memloc)(stk, SP, memadjust);\
IP = memloc;

#endif // !MPASM_MPASM_VALUEFUNCS_H
