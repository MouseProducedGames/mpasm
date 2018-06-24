/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#include "stdafx.h"
#include "run_context.h"

#include <map>
#include <vector>

#include "bytecode.h"
#include "icommand.h"

context::context(
	const icommand &commandmap,
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	size_t memadjust
) : m_commandmap(commandmap), m_inst(inst), m_IP(IP), m_stk(stk), m_SP(SP), m_memadjust(memadjust)
{
	while (IP < m_inst.size())
	{
		size_t useIP = m_IP;
		m_IP += 4;
		if (!commandmap(
			(DT)m_inst[useIP],
			(OP)m_inst[useIP + 1],
			(ML)m_inst[useIP + 2],
			(ML)m_inst[useIP + 3],
			*this
		))
			return;
	}
}

const icommand &context::commandmap()
{
	return m_commandmap;
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