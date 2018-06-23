/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_SYSCALL_MEMORY_H
#define MPASM_MPASM_SYSCALL_MEMORY_H

#include "stdafx.h"

enum class memory_op : uint64_t
{
	Allocate = 1,
	Deallocate = 2,
};

#endif // !MPASM_MPASM_SYSCALL_MEMORY_H
