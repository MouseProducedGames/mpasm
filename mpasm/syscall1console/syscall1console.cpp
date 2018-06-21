#include "stdafx.h"
#include "syscall1console.h"

#include <conio.h>
#include <iostream>

#include "consolevaluefuncs.h"
#include "dthelper.h"
#include "mparray.h"

consolegetcalls(parray, mparray<float32_t>, float32_t, "%g");
consolegetcalls(ptr, float32_t*, float32_t, "%g");
consolegetcalls(value, float32_t, float32_t, "%g");

consolegetcalls(parray, mparray<float64_t>, float64_t, "%g");
consolegetcalls(ptr, float64_t*, float64_t, "%g");
consolegetcalls(value, float64_t, float64_t, "%g");

consolegetcalls(parray, mparray<int8_t>, int8_t, "%hhd");
consolegetcalls(ptr, int8_t*, int8_t, "%hhd");
consolegetcalls(value, int8_t, int8_t, "%hhd");

consolegetcalls(parray, mparray<int16_t>, int16_t, "%hd");
consolegetcalls(ptr, int16_t*, int16_t, "%hd");
consolegetcalls(value, int16_t, int16_t, "%hd");

consolegetcalls(parray, mparray<int32_t>, int32_t, "%ld");
consolegetcalls(ptr, int32_t*, int32_t, "%ld");
consolegetcalls(value, int32_t, int32_t, "%ld");

consolegetcalls(parray, mparray<int64_t>, int64_t, "%lld");
consolegetcalls(ptr, int64_t*, int64_t, "%lld");
consolegetcalls(value, int64_t, int64_t, "%lld");

consolegetcalls(parray, mparray<uint8_t>, uint8_t, "%hhd");
consolegetcalls(ptr, uint8_t*, uint8_t, "%hhd");
consolegetcalls(value, uint8_t, uint8_t, "%hhd");

consolegetcalls(parray, mparray<uint16_t>, uint16_t, "%hd");
consolegetcalls(ptr, uint16_t*, uint16_t, "%hd");
consolegetcalls(value, uint16_t, uint16_t, "%hd");

consolegetcalls(parray, mparray<uint32_t>, uint32_t, "%ld");
consolegetcalls(ptr, uint32_t*, uint32_t, "%ld");
consolegetcalls(value, uint32_t, uint32_t, "%ld");

consolegetcalls(parray, mparray<uint64_t>, uint64_t, "%lld");
consolegetcalls(ptr, uint64_t*, uint64_t, "%lld");
consolegetcalls(value, uint64_t, uint64_t, "%lld");