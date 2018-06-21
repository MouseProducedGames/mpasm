#include "stdafx.h"
/* #include "syscall.h"

#include "dthelper.h"

#include "syscall1console.h"
#include "syscall2memory.h"

template<>
const syscallfunc &getcall<std::vector<int64_t>>(
	const syscallid &syscall,
	const uint64_t &subcall,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
)
{
	switch (syscall)
	{
	default: throw std::exception("null system call");
	case syscallid::Console: return getsyscall1_console<std::vector<int64_t>>((const syscall1op)(subcall));
	case syscallid::Memory: return getsyscall2_memory<std::vector<int64_t>>((const syscall2op)(subcall));
	}
}

template<>
const syscallfunc &getquickshortcall<std::vector<int64_t>>(
	const uint64_t &subcall,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
)
{
	return getcall<std::vector<int64_t>>(IShortCall, subcall, inst, IP, stk, SP, memadjust, memloc);
}

template<>
const syscallfunc &getsyscall<std::vector<int64_t>>(
	const syscallid &id,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
)
{
	uint64_t * subcall;
	uint64_t fb_subcall = 0;
	getpvalue_restack(uint64_t, IP + 2, subcall, fb_subcall);
	return getcall<std::vector<int64_t>>(id, *subcall, inst, IP, stk, SP, memadjust, memloc);
}

template<>
const syscallfunc &getshortcall<std::vector<int64_t>>(
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	const size_t memadjust,
	size_t &memloc
)
{
	return getsyscall<std::vector<int64_t>>(IShortCall, inst, IP, stk, SP, memadjust, memloc);
}
*/