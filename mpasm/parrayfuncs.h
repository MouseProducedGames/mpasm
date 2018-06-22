#ifndef MPASM_MPASM_PARRAYUNCS_H
#define MPASM_MPASM_PARRAYUNCS_H

#include "dtarrayhelper.h"
#include "mparray.h"
#include "ptrfuncs.h"

#define parrayop(type, op)\
mparray<type> * pleft;\
mparray<type> * pright;\
size_t memloc = ctx.IP() + 4;\
getpavalue_restack(mparray<type>, ctx.IP() + 3, pright);\
getpavalue(mparray<type>, ctx.IP() + 2, pleft);\
mparray<type> left = *pleft;\
mparray<type> right = *pright;\
for (size_t i = 0; i < left.length() && i < right.length(); ++i)\
{\
	left[i] op= right[i];\
}\
ctx.IP() = memloc;

#define parrayfuncop(type, funcop)\
mparray<type> * pleft;\
mparray<type> * pright;\
size_t memloc = ctx.IP() + 4;\
getpavalue_restack(mparray<type>, ctx.IP() + 3, pright);\
getpavalue(mparray<type>, ctx.IP() + 2, pleft);\
mparray<type> left = *pleft;\
mparray<type> right = *pright;\
for (size_t i = 0; i < left.length() && i < right.length(); ++i)\
{\
	left[i] = (type)funcop(left[i], right[i]);\
}\
ctx.IP() = memloc;

#define parrayconv(fromtype, totype)\
mparray<fromtype> * pavalue;\
size_t memloc = ctx.IP() + 4;\
getpavalue(mparray<fromtype>, ctx.IP() + 3, pavalue);\
mparray<totype> * patvalue = (mparray<totype>*)pavalue;\
size_t i = 0;\
while(i < patvalue->length())\
{\
	(*patvalue)[i] = (totype)(*pavalue)[i];\
	++i;\
}\
setpavalue(mparray<totype>, ctx.IP() + 2, patvalue);\
ctx.IP() = memloc;

#define parraygosub(type)\
mparray<uint64_t> * ppanewIP;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(mparray<uint64_t>, ctx.IP() + 2, ppanewIP) \
mparray<uint64_t> panewIP = *ppanewIP;\
size_t i = 0;\
while(i < panewIP.length())\
{\
	context(\
		ctx.inst(),\
		panewIP[i],\
		ctx.stk(),\
		ctx.SP(),\
		ctx.memadjust()\
	);\
}\
ctx.IP() = memloc;

#define parrayjmp(type) /* That's a very good question. */

#define parrayjmpif(type)\
mparray<uint64_t> * ppanewIP;\
type * pjmpcheck;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(mparray<uint64_t>, ctx.IP() + 2, ppanewIP) \
getpvalue_restack(type, ctx.IP() + 3, pjmpcheck) \
if (*pjmpcheck)\
{\
	mparray<uint64_t> panewIP = *ppanewIP;\
	size_t i = 0;\
	while(i < panewIP.length())\
	{\
		context(\
			ctx.inst(),\
			panewIP[i],\
			ctx.stk(),\
			ctx.SP(),\
			ctx.memadjust()\
		);\
	}\
}\
ctx.IP() = memloc;

#define parraypush(type)\
mparray<type> * value;\
size_t memloc = ctx.IP() + 4;\
getpavalue(mparray<type>, ctx.IP() + 3, value);\
pushpavalue(mparray<type>, ctx.IP() + 2, value);\
ctx.IP() = memloc;

#define parrayquickcall(type)\
size_t memloc = ctx.IP() + 4;\
getcall<mparray<type>>(\
	(syscallid)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 2])),\
	(uint64_t)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 3])),\
)(ctx);\
ctx.IP() = memloc;

#define parrayquickshortcall(type)\
size_t memloc = ctx.IP() + 4;\
getquickshortcall<mparray<type>>(\
	(uint64_t)(*(uint16_t*)(&ctx.inst()[ctx.IP() + 2])),\
	ctx,\
)(ctx);\
ctx.IP() = memloc;

#define parraysetishortcall(type)\
uint64_t * value;\
size_t memloc = ctx.IP() + 4;\
getpavalue(uint64_t, ctx.IP() + 2, value);\
IShortCall = (syscallid)(*value);\
ctx.IP() = memloc;

#define parrayshortcall(type)\
size_t memloc = ctx.IP() + 4;\
getshortcall<mparray<type>>(ctx, memloc)(ctx);\
ctx.IP() = memloc;

#define parraysyscall(type)\
mparray<uint64_t> * ppasyscall;\
size_t memloc = ctx.IP() + 4;\
getpavalue_restack(mparray<uint64_t>, ctx.IP() + 2, ppasyscall);\
mparray<syscallid> pasyscall = *(mparray<syscallid>*)ppasyscall;\
size_t i = 0;\
while (i < pasyscall.length())\
{\
	getsyscall<mparray<type>>(\
		(syscallid)(pasyscall[i++]),\
		ctx,\
		memloc)\
	(ctx);\
}\
ctx.IP() = memloc;

#endif // !MPASM_MPASM_PARRAYUNCS_H
