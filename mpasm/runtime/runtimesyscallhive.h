/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_RUNTIMESYSCALLHIVE_H
#define MPASM_MPASM_RUNTIMESYSCALLHIVE_H

#include "stdafx.h"
#include "isyscallhive.h"

#include "syscalls/syscallid.h"
#include "syscall_console/runtimeconsolecallhive.h"
#include "syscall_memory/runtimememorycallhive.h"

template<typename T>
class runtimesyscallhive : public isyscallhive<T>
{
public:
	bool operator()(syscallid id, uint64_t subcall, context &ctx) const override
	{
		switch (id)
		{
		default: return false;
		case syscallid::Console: return runtimeconsolecallhive<T>()(subcall, ctx);
		case syscallid::Memory: return runtimemorycallhive<T>()(subcall, ctx);
		}
	}
};

#endif // !MPASM_MPASM_RUNTIMESYSCALLHIVE_H
