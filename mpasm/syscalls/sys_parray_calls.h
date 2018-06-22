#ifndef MPASM_MPASM_SYS_PARRAY_CALLS_H
#define MPASM_MPASM_SYS_PARRAY_CALLS_H

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

#endif // !MPASM_MPASM_SYS_PARRAY_CALLS_H
