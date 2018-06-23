/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_DTCALLS_H
#define MPASM_MPASM_DTCALLS_H

#include "stdafx.h"
#include "op_calls.h"

#include "../syscalls/syscall.h"
#include "bytecode_op_funcs/op_parrayfuncs.h"
#include "bytecode_op_funcs/op_ptrfuncs.h"
#include "bytecode_op_funcs/op_valuefuncs.h"

#include "run_context.h"

#define op_call(indirection, shorttype, type)\
void DT##shorttype##(context &ctx)\
{\
	switch ((OP)ctx.inst()[ctx.IP() + 1])\
	{\
	case OP::ConvF32:\
	{\
		##indirection##conv(type, float32_t);\
		break;\
	}\
	case OP::ConvF64:\
	{\
		##indirection##conv(type, float64_t);\
		break;\
	}\
	case OP::ConvI8:\
	{\
		##indirection##conv(type, int8_t);\
		break;\
	}\
	case OP::ConvI16:\
	{\
		##indirection##conv(type, int16_t);\
		break;\
	}\
	case OP::ConvI32:\
	{\
		##indirection##conv(type, int32_t);\
		break;\
	}\
	case OP::ConvI64:\
	{\
		##indirection##conv(type, int64_t);\
		break;\
	}\
	case OP::ConvUI8:\
	{\
		##indirection##conv(type, uint8_t);\
		break;\
	}\
	case OP::ConvUI16:\
	{\
		##indirection##conv(type, uint16_t);\
		break;\
	}\
	case OP::ConvUI32:\
	{\
		##indirection##conv(type, uint32_t);\
		break;\
	}\
	case OP::ConvUI64:\
	{\
		##indirection##conv(type, uint64_t);\
		break;\
	}\
	case OP::Gosub:\
	{\
		##indirection##gosub(type);\
		break;\
	}\
	case OP::Jmp:\
	{\
		##indirection##jmpif(type);\
		break;\
	}\
	case OP::JmpIf:\
	{\
		##indirection##jmpif(type);\
		break;\
	}\
	case OP::OpAdd:\
	{\
		##indirection##op(type, +);\
		break;\
	}\
	case OP::OpDiv:\
	{\
		##indirection##op(type, / );\
		break;\
	}\
	case OP::OpLog:\
	{\
		##indirection##funcop(type, log<type>);\
		break;\
	}\
	case OP::OpMod:\
	{\
		##indirection##funcop(type, std::fmod);\
		break;\
	}\
	case OP::OpMul:\
	{\
		##indirection##op(type, *);\
		break;\
	}\
	case OP::OpPow:\
	{\
		##indirection##funcop(type, std::pow);\
		break;\
	}\
	case OP::OpSub:\
	{\
		##indirection##op(type, -);\
		break;\
	}\
	case OP::Push:\
	{\
		##indirection##push(type);\
		break;\
	}\
	case OP::QuickCall:\
	{\
		##indirection##quickcall(type);\
		break;\
	}\
	case OP::QuickShortCall:\
	{\
		##indirection##quickshortcall(type);\
		break;\
	}\
	case OP::SetIShortCall:\
	{\
		##indirection##setishortcall(type);\
		break;\
	}\
	case OP::ShortCall:\
	{\
		##indirection##shortcall(type);\
		break;\
	}\
	case OP::SysCall:\
	{\
		##indirection##syscall(type);\
		break;\
	}\
	}\
}

#endif // !MPASM_MPASM_DTCALLS_H
