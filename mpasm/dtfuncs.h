#ifndef MPASM_MPASM_DTFUNCS_H
#define MPASM_MPASM_DTFUNCS_H

#include "stdafx.h"
#include <vector>

#include "bytecode.h"
#include "dthelper.h"

#define dtimpl(shorttype)\
void DT##shorttype##(\
	const std::vector<uint8_t> &inst,\
	size_t &IP,\
	std::vector<byte> &stk,\
	size_t &SP,\
	size_t memadjust\
);

dtimpl(PAF32);
dtimpl(PF32);
dtimpl(F32);

dtimpl(PAF64);
dtimpl(PF64);
dtimpl(F64);

dtimpl(PAI8);
dtimpl(PI8);
dtimpl(I8);

dtimpl(PAI16);
dtimpl(PI16);
dtimpl(I16);

dtimpl(PAI32);
dtimpl(PI32);
dtimpl(I32);

dtimpl(PAI64);
dtimpl(PI64);
dtimpl(I64);

dtimpl(PAUI8);
dtimpl(PUI8);
dtimpl(UI8);

dtimpl(PAUI16);
dtimpl(PUI16);
dtimpl(UI16);

dtimpl(PAUI32);
dtimpl(PUI32);
dtimpl(UI32);

dtimpl(PAUI64);
dtimpl(PUI64);
dtimpl(UI64);

#endif // !MPASM_MPASM_DTFUNCS_H
