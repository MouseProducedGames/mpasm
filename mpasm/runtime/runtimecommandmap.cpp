/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#include "stdafx.h"
#include "runtimecommandmap.h"

#include <math.h>

#include "bytecode.h"
#include "parray_opcalls.h"
#include "ptr_opcalls.h"
#include "run_context.h"
#include "runtimesyscallhive.h"
#include "value_opcalls.h"

#define dtptr(dt) (DT)(((uint8_t)DT::Ptr | (uint8_t)dt))
#define dtarray(dt) (DT)(((uint8_t)DT::Array | (uint8_t)dt))

bool runtimecommandmap::operator()(DT dt, OP op, ML mla, ML mlb, context &ctx) const
{
	switch (dt)
	{
	default: return false;
	case DT::F32: return value_opcalls<float32_t>(op, mla, mlb, ctx);
	case DT::F64: return value_opcalls<float64_t>(op, mla, mlb, ctx);
	case DT::I8: return value_opcalls<int8_t>(op, mla, mlb, ctx);
	case DT::I16: return value_opcalls<int16_t>(op, mla, mlb, ctx);
	case DT::I32: return value_opcalls<int32_t>(op, mla, mlb, ctx);
	case DT::I64: return value_opcalls<int64_t>(op, mla, mlb, ctx);
	case DT::PSize: return value_opcalls<psize>(op, mla, mlb, ctx);
	case DT::UI8: return value_opcalls<uint8_t>(op, mla, mlb, ctx);
	case DT::UI16: return value_opcalls<uint16_t>(op, mla, mlb, ctx);
	case DT::UI32: return value_opcalls<uint32_t>(op, mla, mlb, ctx);
	case DT::UI64: return value_opcalls<uint64_t>(op, mla, mlb, ctx);

// Warning level 4 doesn't understand flag enums.
#pragma warning(push)
#pragma warning(disable:4063)
	case dtarray(DT::F32): return parray_opcalls<float32_t>(op, mla, mlb, ctx);
	case dtarray(DT::F64): return parray_opcalls<float64_t>(op, mla, mlb, ctx);
	case dtarray(DT::I8): return parray_opcalls<int8_t>(op, mla, mlb, ctx);
	case dtarray(DT::I16): return parray_opcalls<int16_t>(op, mla, mlb, ctx);
	case dtarray(DT::I32): return parray_opcalls<int32_t>(op, mla, mlb, ctx);
	case dtarray(DT::I64): return parray_opcalls<int64_t>(op, mla, mlb, ctx);
	case dtarray(DT::PSize): return parray_opcalls<psize>(op, mla, mlb, ctx);
	case dtarray(DT::UI8): return parray_opcalls<uint8_t>(op, mla, mlb, ctx);
	case dtarray(DT::UI16): return parray_opcalls<uint16_t>(op, mla, mlb, ctx);
	case dtarray(DT::UI32): return parray_opcalls<uint32_t>(op, mla, mlb, ctx);
	case dtarray(DT::UI64): return parray_opcalls<uint64_t>(op, mla, mlb, ctx);

	case dtptr(DT::F32): return ptr_opcalls<float32_t>(op, mla, mlb, ctx);
	case dtptr(DT::F64): return ptr_opcalls<float64_t>(op, mla, mlb, ctx);
	case dtptr(DT::I8): return ptr_opcalls<int8_t>(op, mla, mlb, ctx);
	case dtptr(DT::I16): return ptr_opcalls<int16_t>(op, mla, mlb, ctx);
	case dtptr(DT::I32): return ptr_opcalls<int32_t>(op, mla, mlb, ctx);
	case dtptr(DT::I64): return ptr_opcalls<int64_t>(op, mla, mlb, ctx);
	case dtptr(DT::PSize): return ptr_opcalls<psize>(op, mla, mlb, ctx);
	case dtptr(DT::UI8): return ptr_opcalls<uint8_t>(op, mla, mlb, ctx);
	case dtptr(DT::UI16): return ptr_opcalls<uint16_t>(op, mla, mlb, ctx);
	case dtptr(DT::UI32): return ptr_opcalls<uint32_t>(op, mla, mlb, ctx);
	case dtptr(DT::UI64): return ptr_opcalls<uint64_t>(op, mla, mlb, ctx);
#pragma warning(pop)
	}
}