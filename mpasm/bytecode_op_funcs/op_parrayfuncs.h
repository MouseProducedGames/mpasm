/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_PARRAYUNCS_H
#define MPASM_MPASM_PARRAYUNCS_H

#include "data_helpers/data_parrayhelper.h"
#include "parray.h"

#define parrayop(type, op)\
parray<type> * pleft;\
parray<type> * pright;\
size_t memloc = ctx.IP() + 4;\
getpavalue_restack(parray<type>, ctx.IP() + 3, pright);\
getpavalue(parray<type>, ctx.IP() + 2, pleft);\
parray<type> left = *pleft;\
parray<type> right = *pright;\
for (size_t i = 0; i < left.length() && i < right.length(); ++i)\
{\
	left[i] op= right[i];\
}\
ctx.IP() = memloc;

#define parrayfuncop(type, funcop)\
parray<type> * pleft;\
parray<type> * pright;\
size_t memloc = ctx.IP() + 4;\
getpavalue_restack(parray<type>, ctx.IP() + 3, pright);\
getpavalue(parray<type>, ctx.IP() + 2, pleft);\
parray<type> left = *pleft;\
parray<type> right = *pright;\
for (size_t i = 0; i < left.length() && i < right.length(); ++i)\
{\
	left[i] = (type)funcop(left[i], right[i]);\
}\
ctx.IP() = memloc;

#define parrayconv(fromtype, totype)\
parray<fromtype> * pavalue;\
size_t memloc = ctx.IP() + 4;\
getpavalue(parray<fromtype>, ctx.IP() + 3, pavalue);\
parray<totype> * patvalue = (parray<totype>*)pavalue;\
size_t i = 0;\
while(i < patvalue->length())\
{\
	(*patvalue)[i] = (totype)(*pavalue)[i];\
	++i;\
}\
setpavalue(parray<totype>, ctx.IP() + 2, patvalue);\
ctx.IP() = memloc;

#define parraygosub(type)\
parray<uint64_t> * ppanewIP;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(parray<uint64_t>, ctx.IP() + 2, ppanewIP) \
parray<uint64_t> panewIP = *ppanewIP;\
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
parray<uint64_t> * ppanewIP;\
type * pjmpcheck;\
uint64_t memloc = ctx.IP() + 4;\
getpvalue_restack(parray<uint64_t>, ctx.IP() + 2, ppanewIP) \
getpvalue_restack(type, ctx.IP() + 3, pjmpcheck) \
if (*pjmpcheck)\
{\
	parray<uint64_t> panewIP = *ppanewIP;\
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
parray<type> * value;\
size_t memloc = ctx.IP() + 4;\
getpavalue(parray<type>, ctx.IP() + 3, value);\
pushpavalue(parray<type>, ctx.IP() + 2, value);\
ctx.IP() = memloc;

#define parrayquickcall(type)\
size_t memloc = ctx.IP() + 4;\
getcall<parray<type>>(\
	(syscallid)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 2])),\
	(uint64_t)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 3]))\
)(ctx);\
ctx.IP() = memloc;

#define parrayquickshortcall(type)\
size_t memloc = ctx.IP() + 4;\
getquickshortcall<parray<type>>(\
	(uint64_t)(*(uint16_t*)(&ctx.inst()[ctx.IP() + 2]))\
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
getshortcall<parray<type>>(ctx, memloc)(ctx);\
ctx.IP() = memloc;

#define parraysyscall(type)\
parray<uint64_t> * ppasyscall;\
size_t memloc = ctx.IP() + 4;\
getpavalue_restack(parray<uint64_t>, ctx.IP() + 2, ppasyscall);\
parray<syscallid> pasyscall = *(parray<syscallid>*)ppasyscall;\
size_t i = 0;\
while (i < pasyscall.length())\
{\
	getsyscall<parray<type>>(\
		(syscallid)(pasyscall[i++]),\
		ctx,\
		memloc)\
	(ctx);\
}\
ctx.IP() = memloc;

#endif // !MPASM_MPASM_PARRAYUNCS_H
