/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_BYTECODE_H
#define MPASM_MPASM_BYTECODE_H

#include "stdafx.h"

enum class DT : uint8_t
{
	UI8 = 0x1,
	UI16 = 0x2,
	UI32 = 0x3,
	UI64 = 0x4,
	
	I8 = 0x5,
	I16 = 0x6,
	I32 = 0x7,
	I64 = 0x8,
	
	F32 = 0x9,
	F64 = 0xA,
	
	PSize = 0xB,

	Ptr = 0x20,
	Array = 0x40,
	Vector = 0x80
};

enum class OP : uint8_t
{
	SysCall = 0x1,
	SetIShortCall,
	ShortCall,
	QuickShortCall,
	QuickCall,

	OpAdd = 0x10,
	OpDiv,
	OpLog,
	OpMod,
	OpMul,
	OpPow,
	OpSub,

	Push = 0x30,
	PushDeref = 0x31,
	PushRef = 0x32,
	PopPush = 0x33,
	PopPushDeref = 0x34,
	PopPushRef = 0x35,

	ConvUI8 = 0x40,
	ConvUI16 = 0x41,
	ConvUI32 = 0x42,
	ConvUI64 = 0x43,
	
	ConvI8 = 0x44,
	ConvI16 = 0x45,
	ConvI32 = 0x46,
	ConvI64 = 0x47,

	ConvF32 = 0x48,
	ConvF64 = 0x49,

	ConvPSize = 0x4A,

	Gosub = 0x50,
	Jmp,
	JmpIf
};

// ML values of 2 or above refer to registers.
enum class ML : uint8_t
{
	Stk = 0,
	Mem = 1,
};

struct bytecode
{
public:
	DT dt;
	OP op;
	ML mla;
	ML mlb;

	bytecode(DT dt, OP op, ML mla, ML mlb) : dt(dt), op(op), mla(mla), mlb(mlb) {}
};

#endif //!MPASM_MPASM_BYTECODE_H