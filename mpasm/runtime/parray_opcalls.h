/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_RUNTIME_PARRAY_OPCALLS_H
#define MPASM_MPASM_RUNTIME_PARRAY_OPCALLS_H

#include "run_context.h"
#include "runtimesyscallhive.h"
#include "parray.h"
#include "parray_datacalls.h"

template<typename T, typename TConv>
bool parray_convcall(ML mla, ML mlb, context &ctx)
{
	parray<T> &from = parray_getdata_restack<T>(mlb, ctx);
	parray<TConv> to(new TConv[(size_t)from.length()], (size_t)from.length());
	for (size_t i = 0; i < to.length() && i < from.length(); ++i)
	{
		to[i] = (TConv)from[i];
	}
	delete from.ptr();
	from.length() = 0;
	parray_setdata<TConv>(mla, ctx, to);
	return true;
}

template<typename T>
bool parray_opcalls(OP op, ML mla, ML mlb, context &ctx)
{
	switch (op)
	{
	default: return false;
	case OP::ConvF32: return parray_convcall<T, float32_t>(mla, mlb, ctx);
	case OP::ConvF64: return parray_convcall<T, float64_t>(mla, mlb, ctx);
	case OP::ConvI8: return parray_convcall<T, int8_t>(mla, mlb, ctx);
	case OP::ConvI16: return parray_convcall<T, int16_t>(mla, mlb, ctx);
	case OP::ConvI32: return parray_convcall<T, int32_t>(mla, mlb, ctx);
	case OP::ConvI64: return parray_convcall<T, int64_t>(mla, mlb, ctx);
	case OP::ConvUI8: return parray_convcall<T, uint8_t>(mla, mlb, ctx);
	case OP::ConvPSize: return parray_convcall<T, psize>(mla, mlb, ctx);
	case OP::ConvUI16: return parray_convcall<T, uint16_t>(mla, mlb, ctx);
	case OP::ConvUI32: return parray_convcall<T, uint32_t>(mla, mlb, ctx);
	case OP::ConvUI64: return parray_convcall<T, uint64_t>(mla, mlb, ctx);
	case OP::Gosub:
	{
		parray<psize> iparray = parray_getdata_restack<psize>(mla, ctx);
		for (size_t i = 0; i < iparray.length(); ++i)
		{
			size_t newIP = (size_t)iparray[i];
				context(
					ctx.commandmap(),
					ctx.inst(), newIP,
					ctx.stk(), ctx.SP(),
					ctx.memadjust()
				);
		}
		return true;
	}
	case OP::Jmp:
	{
		ctx.IP() = (size_t)value_getdata_restack<psize>(mla, ctx);
		return true;
	}
	case OP::JmpIf:
	{
		parray<T> checkdata = parray_getdata<T>(mlb, ctx);
		bool go = true;
		for (size_t i = 0; i < checkdata.length(); ++i)
		{
			if (checkdata[i] != 0)
			{
				go = false;
				break;
			}
		}
		if (go)
		{
			ctx.IP() = (size_t)value_getdata_restack<psize>(mla, ctx);
		}
		return true;
	}
	case OP::OpAdd:
	{
		parray<T> & right = parray_getdata_restack<T>(mlb, ctx);
		parray<T> & left = parray_getdata<T>(mlb, ctx);
		for (size_t i = 0; i < left.length() && i < right.length(); ++i)
		{
			left[i] += right[i];
		}
		return true;
	}
	case OP::OpDiv:
	{
		parray<T> & right = parray_getdata_restack<T>(mlb, ctx);
		parray<T> & left = parray_getdata<T>(mlb, ctx);
		for (size_t i = 0; i < left.length() && i < right.length(); ++i)
		{
			left[i] /= right[i];
		}
		return true;
	}
	case OP::OpLog:
	{
		parray<T> & right = parray_getdata_restack<T>(mlb, ctx);
		parray<T> & left = parray_getdata<T>(mlb, ctx);
		for (size_t i = 0; i < left.length() && i < right.length(); ++i)
		{
			left[i] = log(left[i], right[i]);
		}
		return true;
	}
	case OP::OpMod:
	{
		parray<T> & right = parray_getdata_restack<T>(mlb, ctx);
		parray<T> & left = parray_getdata<T>(mlb, ctx);
		for (size_t i = 0; i < left.length() && i < right.length(); ++i)
		{
			left[i] = (T)fmod(left[i], right[i]);
		}
		return true;
	}
	case OP::OpMul:
	{
		parray<T> & right = parray_getdata_restack<T>(mlb, ctx);
		parray<T> & left = parray_getdata<T>(mlb, ctx);
		for (size_t i = 0; i < left.length() && i < right.length(); ++i)
		{
			left[i] *= right[i];
		}
		return true;
	}
	case OP::OpPow:
	{
		parray<T> & right = parray_getdata_restack<T>(mlb, ctx);
		parray<T> & left = parray_getdata<T>(mlb, ctx);
		for (size_t i = 0; i < left.length() && i < right.length(); ++i)
		{
			left[i] = (T)pow(left[i], right[i]);
		}
		return true;
	}
	case OP::OpSub:
	{
		parray<T> & right = parray_getdata_restack<T>(mlb, ctx);
		parray<T> & left = parray_getdata<T>(mlb, ctx);
		for (size_t i = 0; i < left.length() && i < right.length(); ++i)
		{
			left[i] -= right[i];
		}
		return true;
	}
	case OP::Push:
	{
		parray_setdata<T>(mla, ctx, parray_getdata<T>(mlb, ctx));
		return true;
	}
	case OP::PushDeref:
	{
		parray_setdata<T>(mla, ctx, *ptr_getdata<parray<T>>(mlb, ctx));
		return true;
	}
	case OP::PushRef:
	{
		ptr_setdata<parray<T>>(mla, ctx, &parray_getdata<T>(mlb, ctx));
		return true;
	}
	case OP::PopPush:
	{
		parray_setdata<T>(mla, ctx, parray_getdata_restack<T>(mlb, ctx));
		return true;
	}
	case OP::PopPushDeref:
	{
		parray_setdata<T>(mla, ctx, *ptr_getdata_restack<parray<T>>(mlb, ctx));
		return true;
	}
	case OP::PopPushRef:
	{
		ptr_setdata<parray<T>>(mla, ctx, &parray_getdata_restack<T>(mlb, ctx));
		return true;
	}
	case OP::QuickCall:
	{
		return runtimesyscallhive<parray<T>>()((syscallid)mla, (uint64_t)mlb, ctx);
	}
	}
}

#endif // !MPASM_MPASM_RUNTIME_PARRAY_OPCALLS_H
