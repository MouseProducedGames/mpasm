/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_RUNTIME_VALUE_OPCALLS_H
#define MPASM_MPASM_RUNTIME_VALUE_OPCALLS_H

#include "run_context.h"
#include "value_datacalls.h"

template<typename T, typename TConv>
bool value_convcall(ML mla, ML mlb, context &ctx)
{
	TConv to = (TConv)value_getdata_restack<T>(mlb, ctx);
	value_setdata<TConv>(mla, ctx, to);
	return true;
}

template<typename T>
bool value_opcalls(OP op, ML mla, ML mlb, context &ctx)
{
	switch (op)
	{
	default: return false;
	case OP::ConvF32: return value_convcall<T, float32_t>(mla, mlb, ctx);
	case OP::ConvF64: return value_convcall<T, float64_t>(mla, mlb, ctx);
	case OP::ConvI8: return value_convcall<T, int8_t>(mla, mlb, ctx);
	case OP::ConvI16: return value_convcall<T, int16_t>(mla, mlb, ctx);
	case OP::ConvI32: return value_convcall<T, int32_t>(mla, mlb, ctx);
	case OP::ConvI64: return value_convcall<T, int64_t>(mla, mlb, ctx);
	case OP::ConvUI8: return value_convcall<T, uint8_t>(mla, mlb, ctx);
	case OP::ConvPSize: return value_convcall<T, psize>(mla, mlb, ctx);
	case OP::ConvUI16: return value_convcall<T, uint16_t>(mla, mlb, ctx);
	case OP::ConvUI32: return value_convcall<T, uint32_t>(mla, mlb, ctx);
	case OP::ConvUI64: return value_convcall<T, uint64_t>(mla, mlb, ctx);
	case OP::Gosub:
	{
		size_t newIP = (size_t)value_getdata_restack<psize>(mla, ctx);
		context(
			ctx.commandmap(),
			ctx.inst(), newIP,
			ctx.stk(), ctx.SP(),
			ctx.memadjust()
		);
		return true;
	}
	case OP::Jmp:
	{
		ctx.IP() = (size_t)value_getdata_restack<psize>(mla, ctx);
		return true;
	}
	case OP::JmpIf:
	{
		if (value_getdata<T>(mlb, ctx))
		{
			ctx.IP() = (size_t)value_getdata_restack<psize>(mla, ctx);
		}
		return true;
	}
	case OP::OpAdd:
	{
		T & right = value_getdata_restack<T>(mlb, ctx);
		value_getdata<T>(mla, ctx) += right;
		return true;
	}
	case OP::OpDiv:
	{
		T & right = value_getdata_restack<T>(mlb, ctx);
		value_getdata<T>(mla, ctx) /= right;
		return true;
	}
	case OP::OpLog:
	{
		T & right = value_getdata_restack<T>(mlb, ctx);
		T & left = value_getdata<T>(mla, ctx);
		left = (T)log(left, right);
		return true;
	}
	case OP::OpMod:
	{
		T & right = value_getdata_restack<T>(mlb, ctx);
		T & left = value_getdata<T>(mla, ctx);
		left = (T)fmod(left, right);
		return true;
	}
	case OP::OpMul:
	{
		T & right = value_getdata_restack<T>(mlb, ctx);
		value_getdata<T>(mla, ctx) *= right;
		return true;
	}
	case OP::OpPow:
	{
		T & right = value_getdata_restack<T>(mlb, ctx);
		T & left = value_getdata<T>(mla, ctx);
		left = (T)pow(left, right);
		return true;
	}
	case OP::OpSub:
	{
		T & right = value_getdata_restack<T>(mlb, ctx);
		value_getdata<T>(mla, ctx) -= right;
		return true;
	}
	case OP::Push:
	{
		value_setdata<T>(mla, ctx, value_getdata<T>(mlb, ctx));
		return true;
	}
	case OP::PushDeref:
	{
		value_setdata<T>(mla, ctx, *ptr_getdata<T>(mlb, ctx));
		return true;
	}
	case OP::PushRef:
	{
		ptr_setdata<T>(mla, ctx, &value_getdata<T>(mlb, ctx));
		return true;
	}
	case OP::PopPush:
	{
		value_setdata<T>(mla, ctx, value_getdata_restack<T>(mlb, ctx));
		return true;
	}
	case OP::PopPushDeref:
	{
		value_setdata<T>(mla, ctx, *ptr_getdata_restack<T>(mlb, ctx));
		return true;
	}
	case OP::PopPushRef:
	{
		ptr_setdata<T>(mla, ctx, &value_getdata_restack<T>(mlb, ctx));
		return true;
	}
	case OP::QuickCall:
	{
		return runtimesyscallhive<T>()((syscallid)mla, (uint64_t)mlb, ctx);
	}
	}
}

#endif // !MPASM_MPASM_RUNTIME_VALUE_OPCALLS_H
