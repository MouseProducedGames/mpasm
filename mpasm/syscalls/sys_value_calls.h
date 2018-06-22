#ifndef MPASM_MPASM_SYSCALLS_SYS_VALUE_CALLS_H
#define MPASM_MPASM_SYSCALLS_SYS_VALUE_CALLS_H

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

#endif // !MPASM_MPASM_SYSCALLS_SYS_VALUE_CALLS_H
