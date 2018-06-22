#include "stdafx.h"
#include "op_calls.h"

#include "op_calls_impl.h"

op_call(parray, PAF32, float32_t);
op_call(ptr, PF32, float32_t);
op_call(value, F32, float32_t);

op_call(parray, PAF64, float64_t);
op_call(ptr, PF64, float64_t);
op_call(value, F64, float64_t);

op_call(parray, PAI8, int8_t);
op_call(ptr, PI8, int8_t);
op_call(value, I8, int8_t);

op_call(parray, PAI16, int16_t);
op_call(ptr, PI16, int16_t);
op_call(value, I16, int16_t);

op_call(parray, PAI32, int32_t);
op_call(ptr, PI32, int32_t);
op_call(value, I32, int32_t);

op_call(parray, PAI64, int64_t);
op_call(ptr, PI64, int64_t);
op_call(value, I64, int64_t);

op_call(parray, PAUI8, uint8_t);
op_call(ptr, PUI8, uint8_t);
op_call(value, UI8, uint8_t);

op_call(parray, PAUI16, uint16_t);
op_call(ptr, PUI16, uint16_t);
op_call(value, UI16, uint16_t);

op_call(parray, PAUI32, uint32_t);
op_call(ptr, PUI32, uint32_t);
op_call(value, UI32, uint32_t);

op_call(parray, PAUI64, uint64_t);
op_call(ptr, PUI64, uint64_t);
op_call(value, UI64, uint64_t);