/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_SYSCALL_CONSOLE_CONSOLE_OPS_H
#define MPASM_MPASM_SYSCALL_CONSOLE_CONSOLE_OPS_H

#include "stdafx.h"

enum class console_op : uint64_t
{
	getkey = 1,
	readchar = 2,
	writechar = 3,
	read = 4,
	write = 5,
};

#endif // !MPASM_MPASM_SYSCALL_CONSOLE_CONSOLE_OPS_H