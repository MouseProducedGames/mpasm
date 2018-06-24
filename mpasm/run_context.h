/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_RUN_H
#define MPASM_MPASM_RUN_H

#include "stdafx.h"

#include <vector>

class context;
class icommand;

class context
{
private:
	const icommand &m_commandmap;
	const std::vector<uint8_t> &m_inst;
	size_t &m_IP;
	std::vector<byte> &m_stk;
	size_t &m_SP;
	const size_t m_memadjust;

public:
	context(
		const icommand &m_commandmap,
		const std::vector<uint8_t> &inst,
		size_t &IP,
		std::vector<byte> &stk,
		size_t &SP,
		const size_t memadjust
	);

	const icommand &commandmap();
	const std::vector<uint8_t> &inst();
	size_t &IP();
	std::vector<byte> &stk();
	size_t &SP();
	size_t memadjust();
};

#endif // !MPASM_MPASM_RUN_H

