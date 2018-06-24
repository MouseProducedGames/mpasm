/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_PARRAY_DATACALLS_H
#define MPASM_MPASM_PARRAY_DATACALLS_H

#include "stdafx.h"

#include "bytecode.h"
#include "parray.h"
#include "registers.h"

class context;

template<typename T>
parray<T> &parray_getdata(ML ml, context &ctx)
{
	switch (ml)
	{
	default:
	{
		parray<T> & data = reg<parray<T>>[(uint8_t)ml];
		data.ptr() += ctx.memadjust();
		return data;
	}
	case ML::Mem:
	{
		parray<T> & data = (parray<T>&)(*(parray<T>*)((*(psize*)&ctx.inst()[ctx.IP()]) + ctx.memadjust()));
		data.ptr() += ctx.memadjust();
		ctx.IP() += sizeof(psize);
		return data;
	}
	case ML::Stk:
	{
		parray<T> & data = *((parray<T>*)(&ctx.stk()[ctx.SP() - sizeof(parray<T>)]));
		data.ptr() += ctx.memadjust();
		return data;
	}
	}
}

template<typename T>
parray<T> &parray_getdata_restack(ML ml, context &ctx)
{
	switch (ml)
	{
	default:
	{
		parray<T> & data = reg<parray<T>>[(uint8_t)ml];
		data.ptr() += ctx.memadjust();
		return data;
	}
	case ML::Mem:
	{
		parray<T> & o = (parray<T>&)(*(parray<T>*)((*(psize*)&ctx.inst()[ctx.IP()]) + ctx.memadjust()));
		o.ptr() += ctx.memadjust();
		ctx.IP() += sizeof(psize);
		return o;
	}
	case ML::Stk:
	{
		parray<T> & data = *((parray<T>*)(&ctx.stk()[ctx.SP() -= sizeof(parray<T>)]));
		data.ptr() += ctx.memadjust();
		return data;
	}
	}
}

template<typename T>
void parray_setdata(ML ml, context &ctx, parray<T> &data)
{
	switch (ml)
	{
	default:
	{
		data.ptr() -= ctx.memadjust();
		reg<parray<T>>[(uint8_t)ml] = data; break;
	}
	case ML::Mem:
	{
		data.ptr() -= ctx.memadjust();
		*(parray<T>*)((*(psize*)&ctx.inst()[ctx.IP()]) + ctx.memadjust()) = data;
		ctx.IP() += sizeof(psize);
		break;
	}
	case ML::Stk:
	{
		data.ptr() -= ctx.memadjust();
		*((parray<T>*)(&ctx.stk()[ctx.SP()])) = data;
		ctx.SP() += sizeof(parray<T>);
		break;
	}
	}
}

#endif // !MPASM_MPASM_PARRAY_DATACALLS_H
