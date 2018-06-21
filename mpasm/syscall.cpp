#include "stdafx.h"
#include "syscall.h"

#include "dthelper.h"
#include "dtarrayhelper.h"
#include "run_context.h"
#include "syscall1console.h"
#include "syscall2memory.h"

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