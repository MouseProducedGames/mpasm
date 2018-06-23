/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_SYSCALLS_SYS_PTR_CALLS_H
#define MPASM_MPASM_SYSCALLS_SYS_PTR_CALLS_H

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
	case syscallid::Console: return getsyscall1_console<type*>((const console_op)(subcall));\
	case syscallid::Memory: return getsyscall2_memory<type*>((const memory_op)(subcall));\
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

#endif // !MPASM_MPASM_SYSCALLS_SYS_PTR_CALLS_H
