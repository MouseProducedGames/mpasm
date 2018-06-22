#ifndef MPASM_MPASM_SYSCALL_H
#define MPASM_MPASM_SYSCALL_H

#include "stdafx.h"
#include <vector>

#include "bytecode.h"
#include "mparray.h"
#include "run_context.h"

enum class syscallid : uint64_t
{
	Console = 1,
	Memory
};

/* Default setting is Console/Terminal.
* If no Console/Terminal is available on the hardware, then provide a null
* Console/Terminal.
*/
extern syscallid IShortCall;

typedef void (*syscallfunc)(context &ctx);

template<typename T>
const syscallfunc &getcall(
	const syscallid &syscall,
	const uint64_t &subcall
);

template<typename T>
const syscallfunc &getquickshortcall(
	const uint64_t &subcall
);

template<typename T>
const syscallfunc &getsyscall(
	const syscallid &id,
	context &ctx,
	size_t &memloc
);

template<typename T>
const syscallfunc &getshortcall(
	context &ctx,
	size_t &memloc
);

#define sysgetvaluecall(type)\
template<>\
const syscallfunc &getcall<type>(\
	const syscallid &syscall,\
	const uint64_t &subcall\
	)\
{\
	switch (syscall)\
	{\
	default: throw std::exception("null system call");\
	case syscallid::Console: return getsyscall1_console<type>((const syscall1op)(subcall));\
	case syscallid::Memory: return getsyscall2_memory<type>((const syscall2op)(subcall));\
	}\
}\
\
template<>\
const syscallfunc &getquickshortcall<type>(\
	const uint64_t &subcall\
	)\
{\
	return getcall<type>(IShortCall, subcall);\
}\
\
template<>\
const syscallfunc &getsyscall<type>(\
	const syscallid &id,\
	context &ctx,\
	size_t &memloc\
	)\
{\
	uint64_t * subcall;\
	getpvalue_restack(uint64_t, ctx.IP() + 2, subcall);\
	return getcall<type>(id, *subcall);\
}\
\
template<>\
const syscallfunc &getshortcall<type>(\
	context &ctx,\
	size_t &memloc\
	)\
{\
	return getsyscall<type>(IShortCall, ctx, memloc);\
}

#define sysgetptrcall(type)\
template<>\
const syscallfunc &getcall<type*>(\
	const syscallid &syscall,\
	const uint64_t &subcall\
)\
{\
	switch (syscall)\
	{\
	default: throw std::exception("null system call");\
	case syscallid::Console: return getsyscall1_console<type*>((const syscall1op)(subcall));\
	case syscallid::Memory: return getsyscall2_memory<type*>((const syscall2op)(subcall));\
	}\
}\
\
template<>\
const syscallfunc &getquickshortcall<type*>(\
	const uint64_t &subcall\
)\
{\
	return getcall<type*>(IShortCall, subcall);\
}\
\
template<>\
const syscallfunc &getsyscall<type*>(\
	const syscallid &id,\
	context &ctx,\
	size_t &memloc\
)\
{\
	uint64_t * psubcall;\
	getpvalue_restack(uint64_t, ctx.IP() + 2, psubcall);\
	uint64_t * pvsubcall = getmemfullptr(uint64_t, psubcall);\
	return getcall<type*>(id, *pvsubcall);\
}\
\
template<>\
const syscallfunc &getshortcall<type*>(\
	context &ctx,\
	size_t &memloc\
)\
{\
	return getsyscall<type*>(IShortCall, ctx, memloc);\
}

#define sysgetparraycall(type)\
template<>\
const syscallfunc &getcall<mparray<type>>(\
	const syscallid &syscall,\
	const uint64_t &subcall\
)\
{\
	switch (syscall)\
	{\
	default: throw std::exception("null system call");\
	case syscallid::Console: return getsyscall1_console<mparray<type>>((const syscall1op)(subcall));\
	case syscallid::Memory: return getsyscall2_memory<mparray<type>>((const syscall2op)(subcall));\
	}\
}\
\
template<>\
const syscallfunc &getquickshortcall<mparray<type>>(\
	const uint64_t &subcall\
)\
{\
	return getcall<mparray<type>>(IShortCall, subcall);\
}\
\
template<>\
const syscallfunc &getsyscall<mparray<type>>(\
	const syscallid &id,\
	context &ctx,\
	size_t &memloc\
)\
{\
	uint64_t * subcall;\
	getpvalue_restack(uint64_t, ctx.IP() + 2, subcall);\
	return getcall<mparray<type>>(id, *subcall);\
}\
\
template<>\
const syscallfunc &getshortcall<mparray<type>>(\
	context &ctx,\
	size_t &memloc\
)\
{\
	return getsyscall<mparray<type>>(IShortCall, ctx, memloc);\
}

#endif // !MPASM_MPASM_SYSCALL_H