#include "stdafx.h"
#include "dtfuncs.h"

#include "DTcalls.h"

dtcall(parray, PAF32, float32_t);
dtcall(ptr, PF32, float32_t);
dtcall(value, F32, float32_t);

dtcall(parray, PAF64, float64_t);
dtcall(ptr, PF64, float64_t);
dtcall(value, F64, float64_t);

dtcall(parray, PAI8, int8_t);
dtcall(ptr, PI8, int8_t);
dtcall(value, I8, int8_t);

dtcall(parray, PAI16, int16_t);
dtcall(ptr, PI16, int16_t);
dtcall(value, I16, int16_t);

dtcall(parray, PAI32, int32_t);
dtcall(ptr, PI32, int32_t);
dtcall(value, I32, int32_t);

dtcall(parray, PAI64, int64_t);
dtcall(ptr, PI64, int64_t);
dtcall(value, I64, int64_t);

dtcall(parray, PAUI8, uint8_t);
dtcall(ptr, PUI8, uint8_t);
dtcall(value, UI8, uint8_t);

dtcall(parray, PAUI16, uint16_t);
dtcall(ptr, PUI16, uint16_t);
dtcall(value, UI16, uint16_t);

dtcall(parray, PAUI32, uint32_t);
dtcall(ptr, PUI32, uint32_t);
dtcall(value, UI32, uint32_t);

dtcall(parray, PAUI64, uint64_t);
dtcall(ptr, PUI64, uint64_t);
// dtcall(value, UI64, uint64_t);

void DTUI64(context &ctx)
{
	switch ((OP)ctx.inst()[ctx.IP() + 1])
	{
	case OP::ConvF32:
	{
		valueconv(uint64_t, float32_t);
		break;
	}
	case OP::ConvF64:
	{
		valueconv(uint64_t, float64_t);
		break;
	}
	case OP::ConvI8:
	{
		valueconv(uint64_t, int8_t);
		break;
	}
	case OP::ConvI16:
	{
		valueconv(uint64_t, int16_t);
		break;
	}
	case OP::ConvI32:
	{
		valueconv(uint64_t, int32_t);
		break;
	}
	case OP::ConvI64:
	{
		valueconv(uint64_t, int64_t);
		break;
	}
	case OP::ConvUI8:
	{
		valueconv(uint64_t, uint8_t);
		break;
	}
	case OP::ConvUI16:
	{
		valueconv(uint64_t, uint16_t);
		break;
	}
	case OP::ConvUI32:
	{
		valueconv(uint64_t, uint32_t);
		break;
	}
	case OP::ConvUI64:
	{
		valueconv(uint64_t, uint64_t);
		break;
	}
	case OP::Gosub:
	{
		valuegosub(uint64_t);
		break;
	}
	case OP::Jmp:
	{
		valuejmpif(uint64_t);
		break;
	}
	case OP::JmpIf:
	{
		valuejmpif(uint64_t);
		break;
	}
	case OP::OpAdd:
	{
		valueop(uint64_t, +);
		break;
	}
	case OP::OpDiv:
	{
		valueop(uint64_t, / );
		break;
	}
	case OP::OpLog:
	{
		valuefuncop(uint64_t, log<uint64_t>);
		break;
	}
	case OP::OpMod:
	{
		valuefuncop(uint64_t, std::fmod);
		break;
	}
	case OP::OpMul:
	{
		valueop(uint64_t, *);
		break;
	}
	case OP::OpPow:
	{
		valuefuncop(uint64_t, std::pow);
		break;
	}
	case OP::OpSub:
	{
		valueop(uint64_t, -);
		break;
	}
	case OP::Push:
	{
		valuepush(uint64_t);
		break;
	}
	case OP::QuickCall:
	{
		// valuequickcall(uint64_t);
		size_t memloc = ctx.IP() + 4; 
		getcall<uint64_t>(
			(syscallid)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 2])), 
			(uint64_t)(*(uint8_t*)(&ctx.inst()[ctx.IP() + 3]))
			)(ctx); 
		ctx.IP() = memloc;
		break;
	}
	case OP::QuickShortCall:
	{
		valuequickshortcall(uint64_t);
		break;
	}
	case OP::SetIShortCall:
	{
		valuesetishortcall(uint64_t);
		break;
	}
	case OP::ShortCall:
	{
		valueshortcall(uint64_t);
		break;
	}
	case OP::SysCall:
	{
		valuesyscall(uint64_t);
		break;
	}
	}
}