/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_BYTECODE_H
#define MPASM_MPASM_BYTECODE_H

#include "stdafx.h"

enum class DT : uint8_t
{
	UI8 = 1,
	UI16,
	UI32,
	UI64,
	I8,
	I16,
	I32,
	I64,
	F32,
	F64,

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

	ConvUI8 = 0x40,
	ConvUI16,
	ConvUI32,
	ConvUI64,
	
	ConvI8,
	ConvI16,
	ConvI32,
	ConvI64,

	ConvF32,

	ConvF64,

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