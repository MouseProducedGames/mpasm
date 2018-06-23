/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_SYSCALL2MEMORY_H
#define MPASM_MPASM_SYSCALL2MEMORY_H

#include "../syscalls/syscall.h"

#include "memory_ops.h"

template<typename T>
const syscallfunc &getsyscall2_memory(const memory_op &op);

#endif // !MPASM_MPASM_SYSCALL1CONSOLE_H
