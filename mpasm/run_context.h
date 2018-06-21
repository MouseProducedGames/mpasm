#ifndef MPASM_MPASM_RUN_H
#define MPASM_MPASM_RUN_H

#include "stdafx.h"

#include <vector>

class context
{
private:
	const std::vector<uint8_t> &m_inst;
	size_t &m_IP;
	std::vector<byte> &m_stk;
	size_t &m_SP;
	const size_t m_memadjust;

public:
	context(
		const std::vector<uint8_t> &inst,
		size_t &IP,
		std::vector<byte> &stk,
		size_t &SP,
		const size_t memadjust
	);

	const std::vector<uint8_t> &inst();
	size_t &IP();
	std::vector<byte> &stk();
	size_t &SP();
	size_t memadjust();
};

#endif // !MPASM_MPASM_RUN_H

