/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_SYSCALL_CONSOLE_CONSOLE_OPS_H
#define MPASM_MPASM_SYSCALL_CONSOLE_CONSOLE_OPS_H

#include "stdafx.h"

enum class console_op : uint64_t
{
	write = 1,
	getkey = 2,
	read = 3,
	writechar = 4,
};

#endif // !MPASM_MPASM_SYSCALL_CONSOLE_CONSOLE_OPS_H