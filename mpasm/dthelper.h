#ifndef MPASM_MPASM_DTHELPER_H
#define MPASM_MPASM_DTHELPER_H

#include "stdafx.h"
#include <vector>

#include "paccess.h"
#include "registers.h"

#define getpvalue(type, IP, value, fb_value) \
switch ((ML)inst[IP])\
{\
	default: value = &reg<type>[inst[IP]]; break;\
	case ML::Mem:\
		getmemloc(type, value);\
		memloc += sizeof(size_t);\
		break;\
	case ML::Stk:\
		value = getstk(type);\
		break;\
}

#define getpvalue_restack(type, IP, value, fb_value) \
switch ((ML)inst[IP])\
{\
	default: value = &reg<type>[inst[IP]]; break;\
	case ML::Mem:\
		getmemloc(type, value);\
		memloc += sizeof(size_t);\
		break;\
	case ML::Stk:\
		value = popstk(type);\
		break;\
}

#define setpvalue(type, IP, value)\
switch ((ML)inst[IP])\
{\
	default: reg<type>[inst[IP]] = static_cast<type>(*value); break;\
	case ML::Mem:\
		setmemloc(type, value);\
		memloc += sizeof(size_t);\
		break;\
	case ML::Stk:\
		setstk(type, value);\
		break;\
}

#define pushpvalue(type, IP, value)\
switch ((ML)inst[IP])\
{\
	default: reg<type>[inst[IP]] = static_cast<type>(*value); break;\
	case ML::Mem:\
		setmemloc(type, value);\
		memloc += sizeof(size_t);\
		break;\
	case ML::Stk:\
		push(static_cast<type>(*value), stk, SP);\
		break;\
}

template<typename T>
void push(const T &value, std::vector<byte> &stk, size_t &SP)
{
	size_t size = SP + sizeof(T);
	if (size > stk.size())
	{
		stk.resize(size);
	}
	T* back = ((T*)(&stk.at(SP)));
	*back = value;
	SP += sizeof(T);
}

#endif // !MPASM_MPASM_DTHELPER_H

