/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_SYS_PARRAY_CALLS_H
#define MPASM_MPASM_SYS_PARRAY_CALLS_H

#define sysgetparraycall(type)\
template<>\
const syscallfunc &getcall<parray<type>>(\
	const syscallid &syscall,\
	const uint64_t &subcall\
)\
{\
	switch (syscall)\
	{\
	default: throw std::exception("null system call");\
	case syscallid::Console: return getsyscall1_console<parray<type>>((const console_op)(subcall));\
	case syscallid::Memory: return getsyscall2_memory<parray<type>>((const memory_op)(subcall));\
	}\
}\
\
template<>\
const syscallfunc &getquickshortcall<parray<type>>(\
	const uint64_t &subcall\
)\
{\
	return getcall<parray<type>>(IShortCall, subcall);\
}\
\
template<>\
const syscallfunc &getsyscall<parray<type>>(\
	const syscallid &id,\
	context &ctx,\
	size_t &memloc\
)\
{\
	uint64_t * subcall;\
	getpvalue_restack(uint64_t, ctx.IP() + 2, subcall);\
	return getcall<parray<type>>(id, *subcall);\
}\
\
template<>\
const syscallfunc &getshortcall<parray<type>>(\
	context &ctx,\
	size_t &memloc\
)\
{\
	return getsyscall<parray<type>>(IShortCall, ctx, memloc);\
}

#endif // !MPASM_MPASM_SYS_PARRAY_CALLS_H
