/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_VALUE_DATACALLS_H
#define MPASM_MPASM_VALUE_DATACALLS_H

#include "stdafx.h"

#include "bytecode.h"
#include "registers.h"

class context;

template<typename T>
T &value_getdata(ML ml, context &ctx)
{
	switch (ml)
	{
	default: return reg<T>[(uint8_t)ml];
	case ML::Mem:
	{
		T & o = (T&)(*(T*)((*(psize*)&ctx.inst()[ctx.IP()]) + ctx.memadjust()));
		ctx.IP() += sizeof(psize);
		return o;
	}
	case ML::Stk: return *((T*)(&ctx.stk()[ctx.SP() - sizeof(T)]));
	}
}

template<typename T>
T &value_getdata_restack(ML ml, context &ctx)
{
	switch (ml)
	{
	default: return reg<T>[(uint8_t)ml];
	case ML::Mem:
	{
		T & o = (T&)(*(T*)((*(psize*)&ctx.inst()[ctx.IP()]) + ctx.memadjust()));
		ctx.IP() += sizeof(psize);
		return o;
	}
	case ML::Stk: return *((T*)(&ctx.stk()[ctx.SP() -= sizeof(T)]));
	}
}

template<typename T>
void value_setdata(ML ml, context &ctx, T& data)
{
	switch (ml)
	{
	default: reg<T>[(uint8_t)ml] = data; break;
	case ML::Mem:
	{
		*(T*)((*(psize*)&ctx.inst()[ctx.IP()]) + ctx.memadjust()) = data;
		ctx.IP() += sizeof(psize);
		break;
	}
	case ML::Stk:
	{
		*((T*)(&ctx.stk()[ctx.SP()])) = data;
		ctx.SP() += sizeof(T);
		break;
	}
	}
}

#endif // !MPASM_MPASM_VALUE_DATACALLS_H
