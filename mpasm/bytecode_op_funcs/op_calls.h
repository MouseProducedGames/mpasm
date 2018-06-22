#ifndef MPASM_MPASM_DTFUNCS_H
#define MPASM_MPASM_DTFUNCS_H

#include "stdafx.h"

#include "run_context.h"

#define opcalls_impl(shorttype)\
void DT##shorttype##(context &ctx);

opcalls_impl(PAF32);
opcalls_impl(PF32);
opcalls_impl(F32);

opcalls_impl(PAF64);
opcalls_impl(PF64);
opcalls_impl(F64);

opcalls_impl(PAI8);
opcalls_impl(PI8);
opcalls_impl(I8);

opcalls_impl(PAI16);
opcalls_impl(PI16);
opcalls_impl(I16);

opcalls_impl(PAI32);
opcalls_impl(PI32);
opcalls_impl(I32);

opcalls_impl(PAI64);
opcalls_impl(PI64);
opcalls_impl(I64);

opcalls_impl(PAUI8);
opcalls_impl(PUI8);
opcalls_impl(UI8);

opcalls_impl(PAUI16);
opcalls_impl(PUI16);
opcalls_impl(UI16);

opcalls_impl(PAUI32);
opcalls_impl(PUI32);
opcalls_impl(UI32);

opcalls_impl(PAUI64);
opcalls_impl(PUI64);
opcalls_impl(UI64);

#endif // !MPASM_MPASM_DTFUNCS_H
