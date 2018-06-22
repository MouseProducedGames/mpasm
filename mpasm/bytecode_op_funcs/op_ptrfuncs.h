#ifndef MPASM_MPASM_PTRFUNCS_H

#include "data_helpers/data_helper.h"
#include "data_helpers/data_access.h"

#define ptrop(type, op)\
type * pleft;\
type * pright;\
size_t memloc = ctx.IP() + 4;\
getpvalue_restack(type, ctx.IP() + 3, pright);\
getpvalue(type, ctx.IP() + 2, pleft);\
type *pvleft = getmemfullptr(type, pleft);\
type *pvright = getmemfullptr(type, pright);\
*pvleft op= *pvright;\
ctx.IP() = memloc;

#define ptrfuncop(type, funcop)\
type * pleft;\
type * pright;\
size_t memloc = ctx.IP() + 4;\
getpvalue_restack(type, ctx.IP() + 3, pright);\
getpvalue(type, ctx.IP() + 2, pleft);\
type *pvleft = getmemfullptr(type, pleft);\
type *pvright = getmemfullptr(type, pright);\
*pvleft = (type)funcop(*pvleft, *pvright);\
ctx.IP() = memloc;

#define ptrconv(fromtype, totype)\
fromtype * pvalue;\
size_t memloc = ctx.IP() + 4;\
getpvalue(fromtype, ctx.IP() + 3, pvalue);\
fromtype * pfvvalue = getmemfullptr(fromtype, pvalue);\
totype * ptvvalue = (totype*)pfvvalue;\
*ptvvalue = (totype)(*pfvvalue);\
size_t partialpvalue = (size_t)storeptr(totype, ptvvalue);\
setpvalue(size_t, ctx.IP() + 2, &partialpvalue);\
ctx.IP() = memloc;

#define ptrgosub(type)\
uint64_t * ppnewIP;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(uint64_t, ctx.IP() + 2, ppnewIP) \
uint64_t * pnewIP = getmemfullptr(uint64_t, ppnewIP);\
uint64_t newIP = *pnewIP;\
context(\
	ctx.inst(),\
	newIP,\
	ctx.stk(),\
	ctx.SP(),\
	ctx.memadjust()\
);\
ctx.IP() = memloc;

#define ptrjmp(type)\
uint64_t * ppnewIP;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(uint64_t, ctx.IP() + 2, ppnewIP) \
uint64_t * pnewIP = getmemfullptr(uint64_t, ppnewIP);\
uint64_t newIP = *pnewIP;\
ctx.IP() = newIP;

#define ptrjmpif(type)\
uint64_t * pnewIP;\
type * pjmpcheck;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(uint64_t, ctx.IP() + 2, pnewIP) \
getpvalue_restack(type, ctx.IP() + 3, pjmpcheck) \
if (*pjmpcheck)\
{\
	uint64_t newIP = *pnewIP;\
	ctx.IP() = newIP;\
}\
else\
{\
	ctx.IP() = memloc;\
}

#define ptrpush(type)\
type * value;\
size_t memloc = ctx.IP() + 4;\
getpvalue(type, ctx.IP() + 3, value);\
pushpvalue(type, ctx.IP() + 2, value);\
ctx.IP() = memloc;

#define ptrquickcall(type)\
size_t memloc = ctx.IP() + 4;\
getcall<type*>(\
	(syscallid)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 2])),\
	(uint64_t)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 3]))\
)(ctx);\
ctx.IP() = memloc;

#define ptrquickshortcall(type)\
uint64_t * pvalue = (uint64_t*)((uint16_t*)&ctx.inst()[ctx.IP() + 2]);\
uint64_t * pvvalue = getmemfullptr(uint64_t, pvalue);\
size_t memloc = ctx.IP() + 4;\
getquickshortcall<type*>(*pvvalue)(ctx);\
ctx.IP() = memloc;

#define ptrsetishortcall(type)\
uint64_t * pvalue;\
size_t memloc = ctx.IP() + 4;\
getpvalue(uint64_t, ctx.IP() + 2, pvalue);\
uint64_t * pvvalue = getmemfullptr(uint64_t, pvalue);\
IShortCall = (syscallid)(*pvvalue);\
ctx.IP() = memloc;

#define ptrshortcall(type)\
size_t memloc = ctx.IP() + 4;\
getshortcall<type*>(ctx, memloc)(ctx);\
ctx.IP() = memloc;\

#define ptrsyscall(type)\
uint64_t * psyscall;\
size_t memloc = ctx.IP() + 4;\
getpvalue_restack(uint64_t, ctx.IP() + 2, psyscall);\
syscallid * pvsyscall = getmemfullptr(syscallid, psyscall);\
getsyscall<type*>(\
	(syscallid)(*pvsyscall),\
	ctx,\
	memloc\
)(ctx);\
ctx.IP() = memloc;

#endif // !MPASM_MPASM_PTRFUNCS_H