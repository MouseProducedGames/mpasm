#ifndef MPASM_MPASM_PARRAYUNCS_H
#define MPASM_MPASM_PARRAYUNCS_H

#include "dtarrayhelper.h"
#include "mparray.h"
#include "ptrfuncs.h"

#define parrayop(type, op)\
mparray<type> * pleft;\
mparray<type> * pright;\
mparray<type> fb_pleft(nullptr, 0);\
mparray<type> fb_pright(nullptr, 0);\
size_t memloc = IP + 4;\
getpavalue_restack(mparray<type>, IP + 3, pright, fb_pright);\
getpavalue(mparray<type>, IP + 2, pleft, fb_pleft);\
mparray<type> left = *pleft;\
mparray<type> right = *pright;\
for (size_t i = 0; i < left.length() && i < right.length(); ++i)\
{\
	left[i] op= right[i];\
}\
IP = memloc;

#define parrayfuncop(type, funcop)\
mparray<type> * pleft;\
mparray<type> * pright;\
mparray<type> fb_pleft(nullptr, 0);\
mparray<type> fb_pright(nullptr, 0);\
size_t memloc = IP + 4;\
getpavalue_restack(mparray<type>, IP + 3, pright, fb_pright);\
getpavalue(mparray<type>, IP + 2, pleft, fb_pleft);\
mparray<type> left = *pleft;\
mparray<type> right = *pright;\
for (size_t i = 0; i < left.length() && i < right.length(); ++i)\
{\
	left[i] = (type)funcop(left[i], right[i]);\
}\
IP = memloc;

#define parrayconv(fromtype, totype)\
mparray<fromtype> * pavalue;\
mparray<fromtype> fb_pavalue(nullptr, 0);\
size_t memloc = IP + 4;\
getpavalue(mparray<fromtype>, IP + 3, pavalue, fb_pavalue);\
mparray<totype> * patvalue = (mparray<totype>*)pavalue;\
size_t i = 0;\
while(i < patvalue->length())\
{\
	(*patvalue)[i] = (totype)(*pavalue)[i];\
	++i;\
}\
setpavalue(mparray<totype>, IP + 2, patvalue);\
IP = memloc;

#define parraygosub(type)\
mparray<uint64_t> * ppanewIP;\
mparray<uint64_t> fb_ppanewIP(nullptr, 0);\
uint64_t memloc = IP + 4;\
getpvalue_restack(mparray<uint64_t>, IP + 2, ppanewIP, fb_ppanewIP) \
mparray<uint64_t> panewIP = *ppanewIP;\
size_t i = 0;\
while(i < panewIP.length())\
{\
	Run(\
		inst,\
		panewIP[i],\
		stk,\
		SP,\
		memadjust\
	);\
}\
IP = memloc;

#define parrayjmp(type) /* That's a very good question. */

#define parrayjmpif(type)\
mparray<uint64_t> * ppanewIP;\
mparray<uint64_t> fb_ppanewIP(nullptr, 0);\
type * pjmpcheck;\
type fb_pjmpcheck = 0;\
uint64_t memloc = IP + 4;\
getpvalue_restack(mparray<uint64_t>, IP + 2, ppanewIP, fb_ppanewIP) \
getpvalue_restack(type, IP + 3, pjmpcheck, fb_pjmpcheck) \
if (*pjmpcheck)\
{\
	mparray<uint64_t> panewIP = *ppanewIP;\
	size_t i = 0;\
	while(i < panewIP.length())\
	{\
		Run(\
			inst,\
			panewIP[i],\
			stk,\
			SP,\
			memadjust\
		);\
	}\
}\
IP = memloc;

#define parraypush(type)\
mparray<type> * value;\
mparray<type> fb_value(nullptr, 0);\
size_t memloc = IP + 4;\
getpavalue(mparray<type>, IP + 3, value, fb_value);\
pushpavalue(mparray<type>, IP + 2, value);\
IP = memloc;

#define parrayquickcall(type)\
size_t memloc = IP + 4;\
getcall<mparray<type>>(\
	(syscallid)(*(uint8_t*)(&inst[IP + 2])),\
	(uint64_t)(*(uint8_t*)(&inst[IP + 3])),\
	inst, IP,\
	stk, SP,\
	memadjust, memloc\
)(stk, SP, memadjust);\
IP = memloc;

#define parrayquickshortcall(type)\
size_t memloc = IP + 4;\
getquickshortcall<mparray<type>>(\
	(uint64_t)(*(uint16_t*)(&inst[IP + 2])),\
	inst, IP,\
	stk, SP,\
	memadjust, memloc\
)(stk, SP, memadjust);\
IP = memloc;

#define parraysetishortcall(type)\
uint64_t * value;\
uint64_t fb_value = (uint64_t)0;\
size_t memloc = IP + 4;\
getpavalue(uint64_t, IP + 2, value, fb_value);\
IShortCall = (syscallid)(*value);\
IP = memloc;

#define parrayshortcall(type)\
size_t memloc = IP + 4;\
getshortcall<mparray<type>>(inst, IP, stk, SP, memadjust, memloc)(stk, SP, memadjust);\
IP = memloc;

#define parraysyscall(type)\
mparray<uint64_t> * ppasyscall;\
mparray<uint64_t> fb_ppasyscall(nullptr, 0);\
size_t memloc = IP + 4;\
getpavalue_restack(mparray<uint64_t>, IP + 2, ppasyscall, fb_ppasyscall);\
mparray<syscallid> pasyscall = *(mparray<syscallid>*)ppasyscall;\
size_t i = 0;\
while (i < pasyscall.length())\
{\
	getsyscall<mparray<type>>(\
		(syscallid)(pasyscall[i++]),\
		inst,\
		IP,\
		stk,\
		SP,\
		memadjust,\
		memloc)\
	(stk, SP, memadjust);\
}\
IP = memloc;

#endif // !MPASM_MPASM_PARRAYUNCS_H
