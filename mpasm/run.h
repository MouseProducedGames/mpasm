#ifndef MPASM_MPASM_RUN_H
#define MPASM_MPASM_RUN_H

#include "stdafx.h"

#include <vector>

void Run(
	const std::vector<uint8_t> &inst,
	size_t &IP,
	std::vector<byte> &stk,
	size_t &SP,
	size_t memadjust
);

#endif // !MPASM_MPASM_RUN_H

