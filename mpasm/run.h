#ifndef MPASM_MPASM_RUN_H
#define MPASM_MPASM_RUN_H

#include "stdafx.h"
#include <vector>

#include "bytecode.h"
#include "dtfuncs.h"

#define pdt(dt) (DT)((uint8_t)DT::Ptr | (uint8_t)dt)
#define arraydt(dt) (DT)((uint8_t)DT::Array | (uint8_t)dt)

#define typecall(shorttype)\
case DT::##shorttype##: DT##shorttype##(inst, IP, stk, SP, memadjust); break;\
case pdt(DT::##shorttype##): DTP##shorttype##(inst, IP, stk, SP, memadjust); break;\
case pdt(arraydt(DT::##shorttype##)): DTPA##shorttype##(inst, IP, stk, SP, memadjust); break;\

void Run(
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	size_t memadjust
)
{
	while (IP < inst.size())
	{
		switch ((DT)inst[IP])
		{
			typecall(F32);
			typecall(F64);

			typecall(I8);
			typecall(I16);
			typecall(I32);
			typecall(I64);

			typecall(UI8);
			typecall(UI16);
			typecall(UI32);
			typecall(UI64);
		}
	}
}

#endif // !MPASM_MPASM_RUN_H

