#include "stdafx.h"
/* #include "dtfuncs.h"

#include "syscall.h"
#include "valuefuncs.h"

void DTAI64(
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	size_t memadjust
)
{
	switch ((OP)inst[IP + 1])
	{
	case OP::ConvF64:
	{
		valueconv(int64_t, float64_t);
		break;
	}
	case OP::OpAdd:
	{
		valueop(int64_t, +);
		break;
	}
	case OP::OpDiv:
	{
		valueop(int64_t, /);
		break;
	}
	case OP::OpLog:
	{
		valuefuncop(int64_t, log<int64_t>);
		break;
	}
	case OP::OpMod:
	{
		valueop(int64_t, %);
		break;
	}
	case OP::OpMul:
	{
		valueop(int64_t, *);
		break;
	}
	case OP::OpPow:
	{
		valuefuncop(int64_t, std::pow);
		break;
	}
	case OP::OpSub:
	{
		valueop(int64_t, -);
		break;
	}
	case OP::Push:
	{
		valuepush(int64_t);
		break;
	}
	case OP::QuickCall:
	{
		valuequickcall(int64_t);
		break;
	}
	case OP::QuickShortCall:
	{
		valuequickshortcall(int64_t);
		break;
	}
	case OP::SetIShortCall:
	{
		valuesetishortcall(int64_t);
		break;
	}
	case OP::ShortCall:
	{
		valueshortcall(int64_t);
		break;
	}
	case OP::SysCall:
	{
		valuesyscall(int64_t);
		break;
	}
	}
}
*/