/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#include "stdafx.h"
#include "syscall.h"

#include "data_helpers/data_helper.h"
#include "data_helpers/data_parrayhelper.h"
#include "syscall_console/syscall_console.h"
#include "syscall_memory/syscall_memory.h"
#include "sys_parray_calls.h"
#include "sys_ptr_calls.h"
#include "sys_value_calls.h"
#include "run_context.h"

syscallid IShortCall = syscallid::Console;

sysgetparraycall(float32_t);
sysgetptrcall(float32_t);
sysgetvaluecall(float32_t);

sysgetparraycall(float64_t);
sysgetptrcall(float64_t);
sysgetvaluecall(float64_t);

sysgetparraycall(int8_t);
sysgetptrcall(int8_t);
sysgetvaluecall(int8_t);

sysgetparraycall(int16_t);
sysgetptrcall(int16_t);
sysgetvaluecall(int16_t);

sysgetparraycall(int32_t);
sysgetptrcall(int32_t);
sysgetvaluecall(int32_t);

sysgetparraycall(int64_t);
sysgetptrcall(int64_t);
sysgetvaluecall(int64_t);

sysgetparraycall(uint8_t);
sysgetptrcall(uint8_t);
sysgetvaluecall(uint8_t);

sysgetparraycall(uint16_t);
sysgetptrcall(uint16_t);
sysgetvaluecall(uint16_t);

sysgetparraycall(uint32_t);
sysgetptrcall(uint32_t);
sysgetvaluecall(uint32_t);

sysgetparraycall(uint64_t);
sysgetptrcall(uint64_t);
sysgetvaluecall(uint64_t);