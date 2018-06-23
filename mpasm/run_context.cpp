/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#include "stdafx.h"
#include "run_context.h"

#include <vector>

#include "bytecode.h"
#include "bytecode_op_funcs/op_calls.h"

#define pdt(dt) (DT)((uint8_t)DT::Ptr | (uint8_t)dt)
#define arraydt(dt) (DT)((uint8_t)DT::Array | (uint8_t)dt)

#define typecall(shorttype)\
case DT::##shorttype##: DT##shorttype##(*this); break;\
case pdt(DT::##shorttype##): DTP##shorttype##(*this); break;\
case pdt(arraydt(DT::##shorttype##)): DTPA##shorttype##(*this); break;\

context::context(
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	size_t memadjust
) : m_inst(inst), m_IP(IP), m_stk(stk), m_SP(SP), m_memadjust(memadjust)
{
	while (IP < inst.size())
	{
		switch ((DT)inst[IP])
		{
#pragma warning(push)
#pragma warning(disable:4063)
		default: return;
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
#pragma warning(pop)
	}
}

const std::vector<uint8_t> &context::inst()
{
	return m_inst;
}
size_t &context::IP()
{
	return m_IP;
}
std::vector<byte> &context::stk()
{
	return m_stk;
}
size_t &context::SP()
{
	return m_SP;
}
size_t context::memadjust()
{
	return m_memadjust;
}