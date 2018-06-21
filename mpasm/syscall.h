#ifndef MPASM_MPASM_SYSCALL_H
#define MPASM_MPASM_SYSCALL_H

#include "stdafx.h"
#include <vector>

#include "bytecode.h"
#include "mparray.h"

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

typedef void (*syscallfunc)(std::vector<byte> &stk, size_t &SP, const size_t memadjust);

template<typename T>
const syscallfunc &getcall(
	const syscallid &syscall,
	const uint64_t &subcall,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

template<>
const syscallfunc &getcall<int64_t>(
	const syscallid &syscall,
	const uint64_t &subcall,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
	);

template<>
const syscallfunc &getcall<float64_t>(
	const syscallid &syscall,
	const uint64_t &subcall,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
	);

template<typename T>
const syscallfunc &getquickshortcall(
	const uint64_t &subcall,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

template<>
const syscallfunc &getquickshortcall<int64_t>(
	const uint64_t &subcall,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

template<>
const syscallfunc &getquickshortcall<float64_t>(
	const uint64_t &subcall,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

template<typename T>
const syscallfunc &getsyscall(
	const syscallid &id,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

template<>
const syscallfunc &getsyscall<int64_t>(
	const syscallid &id,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

template<>
const syscallfunc &getsyscall<float64_t>(
	const syscallid &id,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

template<typename T>
const syscallfunc &getshortcall(
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

template<>
const syscallfunc &getshortcall<int64_t>(
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

template<>
const syscallfunc &getshortcall<float64_t>(
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
);

#define sysgetvaluecall(type)\
template<>\
const syscallfunc &getcall<type>(\
	const syscallid &syscall,\
	const uint64_t &subcall,\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
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
	const uint64_t &subcall,\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
	)\
{\
	return getcall<type>(IShortCall, subcall, inst, IP, stk, SP, memadjust, memloc);\
}\
\
template<>\
const syscallfunc &getsyscall<type>(\
	const syscallid &id,\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
	)\
{\
	uint64_t * subcall;\
	uint64_t fb_subcall = 0;\
	getpvalue_restack(uint64_t, IP + 2, subcall, fb_subcall);\
	return getcall<type>(id, *subcall, inst, IP, stk, SP, memadjust, memloc);\
}\
\
template<>\
const syscallfunc &getshortcall<type>(\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
	)\
{\
	return getsyscall<type>(IShortCall, inst, IP, stk, SP, memadjust, memloc);\
}

#define sysgetptrcall(type)\
template<>\
const syscallfunc &getcall<type*>(\
	const syscallid &syscall,\
	const uint64_t &subcall,\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
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
	const uint64_t &subcall,\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
)\
{\
	return getcall<type*>(IShortCall, subcall, inst, IP, stk, SP, memadjust, memloc);\
}\
\
template<>\
const syscallfunc &getsyscall<type*>(\
	const syscallid &id,\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
)\
{\
	uint64_t * psubcall;\
	uint64_t fb_psubcall = 0;\
	getpvalue_restack(uint64_t, IP + 2, psubcall, fb_psubcall);\
	uint64_t * pvsubcall = getmemfullptr(uint64_t, psubcall);\
	return getcall<type*>(id, *pvsubcall, inst, IP, stk, SP, memadjust, memloc);\
}\
\
template<>\
const syscallfunc &getshortcall<type*>(\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
)\
{\
	return getsyscall<type*>(IShortCall, inst, IP, stk, SP, memadjust, memloc);\
}

#define sysgetparraycall(type)\
template<>\
const syscallfunc &getcall<mparray<type>>(\
	const syscallid &syscall,\
	const uint64_t &subcall,\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
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
	const uint64_t &subcall,\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
)\
{\
	return getcall<mparray<type>>(IShortCall, subcall, inst, IP, stk, SP, memadjust, memloc);\
}\
\
template<>\
const syscallfunc &getsyscall<mparray<type>>(\
	const syscallid &id,\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
)\
{\
	uint64_t * subcall;\
	uint64_t fb_subcall = 0;\
	getpvalue_restack(uint64_t, IP + 2, subcall, fb_subcall);\
	return getcall<mparray<type>>(id, *subcall, inst, IP, stk, SP, memadjust, memloc);\
}\
\
template<>\
const syscallfunc &getshortcall<mparray<type>>(\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	const size_t memadjust,\
	size_t &memloc\
)\
{\
	return getsyscall<mparray<type>>(IShortCall, inst, IP, stk, SP, memadjust, memloc);\
}

#endif // !MPASM_MPASM_SYSCALL_H