#ifndef MPASM_MPASM_VALUEFUNCS_H
#define MPASM_MPASM_VALUEFUNCS_H

#include "dtfuncs.h"
#include "ptrfuncs.h"

#define valueop(type, op)\
type * left;\
type * right;\
size_t memloc = ctx.IP() + 4;\
getpvalue_restack(type, ctx.IP() + 3, right);\
getpvalue(type, ctx.IP() + 2, left);\
*left op= *right;\
ctx.IP() = memloc;

#define valuefuncop(type, funcop)\
type * left;\
type * right;\
size_t memloc = ctx.IP() + 4;\
getpvalue_restack(type, ctx.IP() + 3, right);\
getpvalue(type, ctx.IP() + 2, left);\
*left = (type)funcop(*left, *right);\
ctx.IP() = memloc;

#define valueconv(fromtype, totype)\
fromtype * value;\
size_t memloc = ctx.IP() + 4;\
getpvalue(fromtype, ctx.IP() + 3, value);\
setpvalue(totype, ctx.IP() + 2, value);\
ctx.IP() = memloc;

#define valuegosub(type)\
uint64_t * pnewIP;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(uint64_t, ctx.IP() + 2, pnewIP) \
uint64_t newIP = *pnewIP;\
context(\
	ctx.inst(),\
	newIP,\
	ctx.stk(),\
	ctx.SP(),\
	ctx.memadjust()\
);\
ctx.IP() = memloc;

#define valuejmp(type)\
uint64_t * pnewIP;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(uint64_t, ctx.IP() + 2, pnewIP) \
uint64_t newIP = *pnewIP;\
ctx.IP() = newIP;

#define valuejmpif(type)\
uint64_t * pnewIP;\
type * pjmpcheck;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(uint64_t, ctx.IP() + 2, pnewIP)\
getpvalue_restack(type, ctx.IP() + 3, pjmpcheck)\
if (*pjmpcheck)\
{\
	uint64_t newIP = *pnewIP;\
	ctx.IP() = newIP;\
}\
else\
{\
	ctx.IP() = memloc;\
}

#define valuepush(type)\
type * value;\
size_t memloc = ctx.IP() + 4;\
getpvalue(type, ctx.IP() + 3, value);\
pushpvalue(type, ctx.IP() + 2, value);\
ctx.IP() = memloc;

#define valuequickcall(type)\
size_t memloc = ctx.IP() + 4;\
getcall<type>(\
	(syscallid)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 2])),\
	(uint64_t)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 3]))\
)(ctx);\
ctx.IP() = memloc;

#define valuequickshortcall(type)\
size_t memloc = ctx.IP() + 4;\
getquickshortcall<type>(\
	(uint64_t)(*(uint16_t*)(&ctx.inst()[ctx.IP() + 2])),\
	ctx\
)(ctx);\
ctx.IP() = memloc;

#define valuesetishortcall(type)\
uint64_t * value;\
size_t memloc = ctx.IP() + 4;\
getpvalue(uint64_t, ctx.IP() + 2, value);\
IShortCall = (syscallid)(*value);\
ctx.IP() = memloc;

#define valueshortcall(type)\
size_t memloc = ctx.IP() + 4;\
getshortcall<type>(ctx, memloc)(ctx);\
ctx.IP() = memloc;

#define valuesyscall(type)\
uint64_t * syscall;\
size_t memloc = ctx.IP() + 4;\
getpvalue_restack(uint64_t, ctx.IP() + 2, syscall);\
getsyscall<type>((syscallid)(*syscall), ctx, memloc)(ctx);\
ctx.IP() = memloc;

#endif // !MPASM_MPASM_VALUEFUNCS_H
