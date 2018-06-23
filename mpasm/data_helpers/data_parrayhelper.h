/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_DTARRAYHELPER_H
#define MPASM_MPASM_DTARRAYHELPER_H

#include "stdafx.h"
#include <vector>

#include "data_access.h"

#define getpavalue(type, IP, value)\
switch ((ML)ctx.inst()[IP])\
{\
	default: value = &reg<type>[ctx.inst()[IP]]; break;\
	case ML::Mem:\
	{\
		value = loadptr(type, ctx.inst()[memloc]);\
		memloc += sizeof(size_t);\
	}\
	break;\
	case ML::Stk:\
		value = getstk(type);\
		break;\
}

#define getpavalue_restack(type, IP, value) \
switch ((ML)ctx.inst()[IP])\
{\
	default: value = &reg<type>[ctx.inst()[IP]]; break;\
	case ML::Mem:\
		value = loadptr(type, ctx.inst()[memloc]);\
		memloc += sizeof(size_t);\
		break;\
	case ML::Stk:\
		value = popstk(type);\
		break;\
}

#define setpavalue(type, IP, value)\
switch ((ML)ctx.inst()[IP])\
{\
	default: reg<type>[ctx.inst()[IP]] = static_cast<type>(*value); break;\
	case ML::Mem:\
		setmemloc(type, value);\
		memloc += sizeof(size_t);\
		break;\
	case ML::Stk:\
		setstk(type, value);\
		break;\
}

#define pushpavalue(type, IP, value)\
switch ((ML)ctx.inst()[IP])\
{\
	default: reg<type>[ctx.inst()[IP]] = static_cast<type>(*value); break;\
	case ML::Mem:\
	{\
		setmemloc(type, value);\
		memloc += sizeof(size_t);\
		break;\
	}\
	case ML::Stk:\
		push(static_cast<type>(*value), ctx.stk(), ctx.SP());\
		break;\
}

#endif // !MPASM_MPASM_DTARRAYHELPER_H
