#ifndef MPASM_MPASM_PTRFUNCS_H

#include "dthelper.h"
#include "paccess.h"

#define ptrop(type, op)\
type * pleft;\
type * pright;\
type fb_pleft = 0;\
type fb_pright = 0;\
size_t memloc = IP + 4;\
getpvalue_restack(type, IP + 3, pright, fb_pright);\
getpvalue(type, IP + 2, pleft, fb_pleft);\
type *pvleft = getmemfullptr(type, pleft);\
type *pvright = getmemfullptr(type, pright);\
*pvleft op= *pvright;\
IP = memloc;

#define ptrfuncop(type, funcop)\
type * pleft;\
type * pright;\
type fb_pleft = 0;\
type fb_pright = 0;\
size_t memloc = IP + 4;\
getpvalue_restack(type, IP + 3, pright, fb_pright);\
getpvalue(type, IP + 2, pleft, fb_pleft);\
type *pvleft = getmemfullptr(type, pleft);\
type *pvright = getmemfullptr(type, pright);\
*pvleft = (type)funcop(*pvleft, *pvright);\
IP = memloc;

#define ptrconv(fromtype, totype)\
fromtype * pvalue;\
fromtype fb_pvalue = 0;\
size_t memloc = IP + 4;\
getpvalue(fromtype, IP + 3, pvalue, fb_pvalue);\
fromtype * pfvvalue = getmemfullptr(fromtype, pvalue);\
totype * ptvvalue = (totype*)pfvvalue;\
*ptvvalue = (totype)(*pfvvalue);\
size_t partialpvalue = (size_t)storeptr(totype, ptvvalue);\
setpvalue(size_t, IP + 2, &partialpvalue);\
IP = memloc;

#define ptrgosub(type)\
uint64_t * ppnewIP;\
uint64_t fb_ppnewIP = 0;\
uint64_t memloc = IP + 4;\
getpvalue_restack(uint64_t, IP + 2, ppnewIP, fb_ppnewIP) \
uint64_t * pnewIP = getmemfullptr(uint64_t, ppnewIP);\
uint64_t newIP = *pnewIP;\
Run(\
	inst,\
	newIP,\
	stk,\
	SP,\
	memadjust\
);\
IP = memloc;

#define ptrjmp(type)\
uint64_t * ppnewIP;\
uint64_t fb_ppnewIP = 0;\
uint64_t memloc = IP + 4;\
getpvalue_restack(uint64_t, IP + 2, ppnewIP, fb_ppnewIP) \
uint64_t * pnewIP = getmemfullptr(uint64_t, ppnewIP);\
uint64_t newIP = *pnewIP;\
IP = newIP;

#define ptrjmpif(type)\
uint64_t * pnewIP;\
uint64_t fb_pnewIP = 0;\
type * pjmpcheck;\
type fb_pjmpcheck = 0;\
uint64_t memloc = IP + 4;\
getpvalue_restack(uint64_t, IP + 2, pnewIP, fb_pnewIP) \
getpvalue_restack(type, IP + 3, pjmpcheck, fb_pjmpcheck) \
if (*pjmpcheck)\
{\
	uint64_t newIP = *pnewIP;\
	IP = newIP;\
}\
else\
{\
	IP = memloc;\
}

#define ptrpush(type)\
type * value;\
type fb_value = 0;\
size_t memloc = IP + 4;\
getpvalue(type, IP + 3, value, fb_value);\
pushpvalue(type, IP + 2, value);\
IP = memloc;

#define ptrquickcall(type)\
size_t memloc = IP + 4;\
getcall<type*>(\
	(syscallid)(*(uint8_t*)(&inst[IP + 2])),\
	(uint64_t)(*(uint8_t*)(&inst[IP + 3])),\
	inst, IP,\
	stk, SP,\
	memadjust, memloc\
)(stk, SP, memadjust);\
IP = memloc;

#define ptrquickshortcall(type)\
uint64_t * pvalue = (uint64_t*)((uint16_t*)&inst[IP + 2]);\
uint64_t * pvvalue = getmemfullptr(uint64_t, pvalue);\
size_t memloc = IP + 4;\
getquickshortcall<type*>(\
	*pvvalue,\
	inst, IP,\
	stk, SP,\
	memadjust, memloc\
	)(stk, SP, memadjust);\
IP = memloc;

#define ptrsetishortcall(type)\
uint64_t * pvalue;\
uint64_t fb_pvalue = (uint64_t)0;\
size_t memloc = IP + 4;\
getpvalue(uint64_t, IP + 2, pvalue, fb_pvalue);\
uint64_t * pvvalue = getmemfullptr(uint64_t, pvalue);\
IShortCall = (syscallid)(*pvvalue);\
IP = memloc;

#define ptrshortcall(type)\
size_t memloc = IP + 4;\
getshortcall<type*>(inst, IP, stk, SP, memadjust, memloc)(stk, SP, memadjust);\
IP = memloc;\

#define ptrsyscall(type)\
uint64_t * psyscall;\
uint64_t fb_psyscall = (uint64_t)0;\
size_t memloc = IP + 4;\
getpvalue_restack(uint64_t, IP + 2, psyscall, fb_psyscall);\
syscallid * pvsyscall = getmemfullptr(syscallid, psyscall);\
getsyscall<type*>(\
	(syscallid)(*pvsyscall),\
	inst,\
	IP,\
	stk,\
	SP,\
	memadjust,\
	memloc\
)(stk, SP, memadjust);\
IP = memloc;

#endif // !MPASM_MPASM_PTRFUNCS_H