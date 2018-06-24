/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_RUNTIME_PTR_OPCALLS_H
#define MPASM_MPASM_RUNTIME_PTR_OPCALLS_H

#include "ptr_datacalls.h"
#include "run_context.h"
#include "runtimesyscallhive.h"

template<typename T, typename TConv>
bool ptr_convcall(ML mla, ML mlb, context &ctx)
{
	T * from = ptr_getdata_restack<T>(mlb, ctx);
	TConv * to = (TConv*)from;
	*to = (TConv)(*from);
	ptr_setdata<TConv>(mla, ctx, to);
	return true;
}

template<typename T>
bool ptr_opcalls(OP op, ML mla, ML mlb, context &ctx)
{
	switch (op)
	{
	default: return false;
	case OP::ConvF32: return ptr_convcall<T, float32_t>(mla, mlb, ctx);
	case OP::ConvF64: return ptr_convcall<T, float64_t>(mla, mlb, ctx);
	case OP::ConvI8: return ptr_convcall<T, int8_t>(mla, mlb, ctx);
	case OP::ConvI16: return ptr_convcall<T, int16_t>(mla, mlb, ctx);
	case OP::ConvI32: return ptr_convcall<T, int32_t>(mla, mlb, ctx);
	case OP::ConvI64: return ptr_convcall<T, int64_t>(mla, mlb, ctx);
	case OP::ConvPSize: return ptr_convcall<T, psize>(mla, mlb, ctx);
	case OP::ConvUI8: return ptr_convcall<T, uint8_t>(mla, mlb, ctx);
	case OP::ConvUI16: return ptr_convcall<T, uint16_t>(mla, mlb, ctx);
	case OP::ConvUI32: return ptr_convcall<T, uint32_t>(mla, mlb, ctx);
	case OP::ConvUI64: return ptr_convcall<T, uint64_t>(mla, mlb, ctx);
	case OP::Gosub:
	{
		size_t newIP = *(size_t*)ptr_getdata_restack<psize>(mla, ctx);
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
		ctx.IP() = *(size_t*)ptr_getdata_restack<psize>(mla, ctx);
		return true;
	}
	case OP::JmpIf:
	{
		if (ptr_getdata<T>(mlb, ctx))
		{
			ctx.IP() = *(size_t*)ptr_getdata_restack<psize>(mla, ctx);
		}
		return true;
	}
	case OP::OpAdd:
	{
		T * right = ptr_getdata_restack<T>(mlb, ctx);
		*ptr_getdata<T>(mla, ctx) += *right;
		return true;
	}
	case OP::OpDiv:
	{
		T * right = ptr_getdata_restack<T>(mlb, ctx);
		*ptr_getdata<T>(mla, ctx) /= *right;
		return true;
	}
	case OP::OpLog:
	{
		T * right = ptr_getdata_restack<T>(mlb, ctx);
		T * left = ptr_getdata<T>(mla, ctx);
		*left = (T)log(*left, *right);
		return true;
	}
	case OP::OpMod:
	{
		T * right = ptr_getdata_restack<T>(mlb, ctx);
		T * left = ptr_getdata<T>(mla, ctx);
		*left = (T)fmod(*left, *right);
		return true;
	}
	case OP::OpMul:
	{
		T * right = ptr_getdata_restack<T>(mlb, ctx);
		*ptr_getdata<T>(mla, ctx) *= *right;
		return true;
	}
	case OP::OpPow:
	{
		T * right = ptr_getdata_restack<T>(mlb, ctx);
		T * left = ptr_getdata<T>(mla, ctx);
		*left = (T)pow(*left, *right);
		return true;
	}
	case OP::OpSub:
	{
		T * right = ptr_getdata_restack<T>(mlb, ctx);
		*ptr_getdata<T>(mla, ctx) -= *right;
		return true;
	}
	case OP::Push:
	{
		ptr_setdata<T>(mla, ctx, ptr_getdata<T>(mlb, ctx));
		return true;
	}
	case OP::PushDeref:
	{
		ptr_setdata<T>(mla, ctx, *((T**)(ptr_getdata<T>(mlb, ctx))));
		return true;
	}
	case OP::PushRef:
	{
		ptr_setdata<T>(mla, ctx, (T*)(&value_getdata<psize>(mlb, ctx)));
		return true;
	}
	case OP::PopPush:
	{
		ptr_setdata<T>(mla, ctx, ptr_getdata_restack<T>(mlb, ctx));
		return true;
	}
	case OP::PopPushDeref:
	{
		ptr_setdata<T>(mla, ctx, *((T**)(ptr_getdata_restack<T>(mlb, ctx))));
		return true;
	}
	case OP::PopPushRef:
	{
		ptr_setdata<T>(mla, ctx, (T*)(&value_getdata_restack<psize>(mlb, ctx)));
		return true;
	}
	case OP::QuickCall:
	{
		return runtimesyscallhive<T*>()((syscallid)mla, (uint64_t)mlb, ctx);
	}
	}
}

#endif // !MPASM_MPASM_RUNTIME_PTR_OPCALLS_H
