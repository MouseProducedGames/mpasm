/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#include "stdafx.h"
#include "runtimememorycallhive.h"

#include "runtime/parray_datacalls.h"
#include "runtime/ptr_datacalls.h"
#include "runtime/value_datacalls.h"
#include "bytecode.h"
#include "memory_ops.h"
#include "parray.h"
#include "run_context.h"

template<typename T>
bool mem_parray_operator(uint64_t subcall, context &ctx)
{
	switch ((memory_op)subcall)
	{
	default: return false;
	case memory_op::Allocate:
	{
		psize length = value_getdata<psize>(ML::Stk, ctx);
		parray<T> data(new T[(size_t)length], (size_t)length);
		parray_setdata<T>(ML::Stk, ctx, data);
		return true;
	}
	case memory_op::Deallocate:
	{
		parray<T> &data = parray_getdata_restack<T>(ML::Stk, ctx);
		delete data.ptr();
		return true;
	}
	}
}

template<typename T>
bool mem_ptr_operator(uint64_t subcall, context &ctx)
{
	switch ((memory_op)subcall)
	{
	default: return false;
	case memory_op::Allocate:
	{
		psize newT = (psize)new T*((T*)ptr_getdata<psize>(ML::Stk, ctx)) - ctx.memadjust();
		value_setdata<psize>(ML::Stk, ctx, newT);
		return true;
	}
	case memory_op::Deallocate:
	{
		psize oldT = (psize)ptr_getdata_restack<psize>(ML::Stk, ctx);
		delete (T**)(oldT + ctx.memadjust());
		return true;
	}
	}
}

template<typename T>
bool mem_value_operator(uint64_t subcall, context &ctx)
{
	switch ((memory_op)subcall)
	{
	default: return false;
	case memory_op::Allocate:
	{
		psize newT = (psize)new T(value_getdata<T>(ML::Stk, ctx)) - ctx.memadjust();
		value_setdata<psize>(ML::Stk, ctx, newT);
		return true;
	}
	case memory_op::Deallocate:
	{
		psize oldT = (psize)value_getdata_restack<psize>(ML::Stk, ctx);
		delete (T*)(oldT + ctx.memadjust());
		return true;
	}
	}
}

template<> bool runtimemorycallhive<parray<float32_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<float32_t>(subcall, ctx); }
template<> bool runtimemorycallhive<parray<float64_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<float64_t>(subcall, ctx); }
template<> bool runtimemorycallhive<parray<int8_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<int8_t>(subcall, ctx); }
template<> bool runtimemorycallhive<parray<int16_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<int16_t>(subcall, ctx); }
template<> bool runtimemorycallhive<parray<int32_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<int32_t>(subcall, ctx); }
template<> bool runtimemorycallhive<parray<int64_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<int64_t>(subcall, ctx); }
template<> bool runtimemorycallhive<parray<uint8_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<uint8_t>(subcall, ctx); }
template<> bool runtimemorycallhive<parray<uint16_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<uint16_t>(subcall, ctx); }
template<> bool runtimemorycallhive<parray<uint32_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<uint32_t>(subcall, ctx); }
template<> bool runtimemorycallhive<parray<uint64_t>>::operator()(uint64_t subcall, context &ctx) const { return mem_parray_operator<uint64_t>(subcall, ctx); }

template<> bool runtimemorycallhive<float32_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<float32_t>(subcall, ctx); }
template<> bool runtimemorycallhive<float64_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<float64_t>(subcall, ctx); }
template<> bool runtimemorycallhive<int8_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<int8_t>(subcall, ctx); }
template<> bool runtimemorycallhive<int16_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<int16_t>(subcall, ctx); }
template<> bool runtimemorycallhive<int32_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<int32_t>(subcall, ctx); }
template<> bool runtimemorycallhive<int64_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<int64_t>(subcall, ctx); }
template<> bool runtimemorycallhive<uint8_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<uint8_t>(subcall, ctx); }
template<> bool runtimemorycallhive<uint16_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<uint16_t>(subcall, ctx); }
template<> bool runtimemorycallhive<uint32_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<uint32_t>(subcall, ctx); }
template<> bool runtimemorycallhive<uint64_t*>::operator()(uint64_t subcall, context &ctx) const { return mem_ptr_operator<uint64_t>(subcall, ctx); }

template<> bool runtimemorycallhive<float32_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<float32_t>(subcall, ctx); }
template<> bool runtimemorycallhive<float64_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<float64_t>(subcall, ctx); }
template<> bool runtimemorycallhive<int8_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<int8_t>(subcall, ctx); }
template<> bool runtimemorycallhive<int16_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<int16_t>(subcall, ctx); }
template<> bool runtimemorycallhive<int32_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<int32_t>(subcall, ctx); }
template<> bool runtimemorycallhive<int64_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<int64_t>(subcall, ctx); }
template<> bool runtimemorycallhive<uint8_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<uint8_t>(subcall, ctx); }
template<> bool runtimemorycallhive<uint16_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<uint16_t>(subcall, ctx); }
template<> bool runtimemorycallhive<uint32_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<uint32_t>(subcall, ctx); }
template<> bool runtimemorycallhive<uint64_t>::operator()(uint64_t subcall, context &ctx) const { return mem_value_operator<uint64_t>(subcall, ctx); }
