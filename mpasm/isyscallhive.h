/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef ISYSCALLHIVE_H
#define ISYSCALLHIVE_H

#include "stdafx.h"

#include "syscalls/syscallid.h"
#include "bytecode.h"

class context;

template<typename T>
class isyscallhive
{
	virtual bool operator()(syscallid id, uint64_t subcall, context &ctx) const = 0;
};

#endif // !ISYSCALLHIVE_H
