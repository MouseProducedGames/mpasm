#ifndef MPASM_MPASM_DTHELPER_H
#define MPASM_MPASM_DTHELPER_H

#include <vector>

#include "data_access.h"
#include "registers.h"

#define getpvalue(type, IP, value) \
switch ((ML)ctx.inst()[IP])\
{\
	default: value = &reg<type>[ctx.inst()[IP]]; break;\
	case ML::Mem:\
		getmemloc(type, value);\
		memloc += sizeof(size_t);\
		break;\
	case ML::Stk:\
		value = getstk(type);\
		break;\
}

#define getpvalue_restack(type, IP, value) \
switch ((ML)ctx.inst()[IP])\
{\
	default: value = &reg<type>[ctx.inst()[IP]]; break;\
	case ML::Mem:\
		getmemloc(type, value);\
		memloc += sizeof(size_t);\
		break;\
	case ML::Stk:\
		value = popstk(type);\
		break;\
}

#define setpvalue(type, IP, value)\
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

#define pushpvalue(type, IP, value)\
switch ((ML)ctx.inst()[IP])\
{\
	default: reg<type>[ctx.inst()[IP]] = static_cast<type>(*value); break;\
	case ML::Mem:\
		setmemloc(type, value);\
		memloc += sizeof(size_t);\
		break;\
	case ML::Stk:\
		push(static_cast<type>(*value), ctx.stk(), ctx.SP());\
		break;\
}

#endif // !MPASM_MPASM_DTHELPER_H

