#ifndef MPASM_MPASM_SYSCALL2MEMORY_H
#define MPASM_MPASM_SYSCALL2MEMORY_H

#include "../syscalls/syscall.h"

enum class syscall2op : uint64_t
{
	Allocate = 1,
	Deallocate
};

template<typename T>
const syscallfunc &getsyscall2_memory(const syscall2op &op);

#endif // !MPASM_MPASM_SYSCALL1CONSOLE_H
