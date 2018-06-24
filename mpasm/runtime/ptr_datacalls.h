/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_PTR_DATACALLS_H
#define MPASM_MPASM_PTR_DATACALLS_H

#include "stdafx.h"

#include "bytecode.h"
#include "registers.h"

class context;

template<typename T>
T *ptr_getdata(ML ml, context &ctx)
{
	switch (ml)
	{
	default: return (T*)reg<psize>[(uint8_t)ml];
	case ML::Mem:
	{
		T* blah = (T*)((*(psize*)&ctx.inst()[ctx.IP()]) + ctx.memadjust());
		psize* blah2 = (psize*)blah;
		ctx.IP() += sizeof(psize);
		return (T*)(*blah2);
	}
	case ML::Stk:
	{
		psize temp = *(psize*)(&ctx.stk()[ctx.SP() - sizeof(psize)]);
		return ((T*)(temp + ctx.memadjust()));
	}
	}
}

template<typename T>
T *ptr_getdata_restack(ML ml, context &ctx)
{
	switch (ml)
	{
	default: return (T*)reg<psize>[(uint8_t)ml];
	case ML::Mem:
	{
		T ** o = (T**)(((psize**)&ctx.inst()[ctx.IP()]) + ctx.memadjust());
		ctx.IP() += sizeof(psize);
		return *o;
	}
	case ML::Stk:
	{
		psize temp = *(psize*)(&ctx.stk()[ctx.SP() -= sizeof(psize)]);
		return ((T*)(temp + ctx.memadjust()));
	}
	}
}

template<typename T>
void ptr_setdata(ML ml, context &ctx, T* data)
{
	switch (ml)
	{
	default: reg<psize>[(uint8_t)ml] = (psize)data; break;
	case ML::Mem:
	{
		T* blah = (T*)((*(psize*)&ctx.inst()[ctx.IP()]) + ctx.memadjust());
		psize* blah2 = (psize*)blah;
		*blah2 = (psize)data;
		ctx.IP() += sizeof(psize);
		break;
	}
	case ML::Stk:
	{
		psize temp = (psize)data;
		*((T**)(&ctx.stk()[ctx.SP()])) = (T*)(temp - ctx.memadjust());
		ctx.SP() += sizeof(psize);
		break;
	}
	}
}

#endif // !MPASM_MPASM_PTR_DATACALLS_H
