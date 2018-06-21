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
dtcall(value, UI64, uint64_t);

