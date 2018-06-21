#ifndef MPASM_MPASM_BYTECODE_H
#define MPASM_MPASM_BYTECODE_H

#include "stdafx.h"

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
	Array	= 0x40,
	Vector	= 0x80
};

enum class ML : uint8_t
{
	Stk,
	Mem
};

struct bytecode
{
public:
	DT dt;
	OP op;

	bytecode(DT dt, OP op) : dt(dt), op(op) {}
};

#endif //!MPASM_MPASM_BYTECODE_H