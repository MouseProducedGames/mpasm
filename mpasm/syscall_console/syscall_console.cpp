/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#include "stdafx.h"
#include "syscall_console.h"

#include <conio.h>
#include <iostream>
#include <string>

#include "data_helpers/data_access.h"
#include "consoleparrayfuncs.h"
#include "consoleptrfuncs.h"
#include "consolevaluefuncs.h"

template<typename T>
static syscallfunc getkey_func;
template<typename T>
static syscallfunc read_func;
template<typename T>
static syscallfunc write_func;
template<typename T>
static syscallfunc writechar_func;

consolegetcalls(parray, parray<float32_t>, float32_t, "%g");
consolegetcalls(ptr, float32_t*, float32_t, "%g");
consolegetcalls(value, float32_t, float32_t, "%g");

consolegetcalls(parray, parray<float64_t>, float64_t, "%g");
consolegetcalls(ptr, float64_t*, float64_t, "%g");
consolegetcalls(value, float64_t, float64_t, "%g");

consolegetcalls(parray, parray<int8_t>, int8_t, "%hhd");
consolegetcalls(ptr, int8_t*, int8_t, "%hhd");
consolegetcalls(value, int8_t, int8_t, "%hhd");

consolegetcalls(parray, parray<int16_t>, int16_t, "%hd");
consolegetcalls(ptr, int16_t*, int16_t, "%hd");
consolegetcalls(value, int16_t, int16_t, "%hd");

consolegetcalls(parray, parray<int32_t>, int32_t, "%ld");
consolegetcalls(ptr, int32_t*, int32_t, "%ld");
consolegetcalls(value, int32_t, int32_t, "%ld");

consolegetcalls(parray, parray<int64_t>, int64_t, "%lld");
consolegetcalls(ptr, int64_t*, int64_t, "%lld");
consolegetcalls(value, int64_t, int64_t, "%lld");

consolegetcalls(parray, parray<uint8_t>, uint8_t, "%hhd");
consolegetcalls(ptr, uint8_t*, uint8_t, "%hhd");
consolegetcalls(value, uint8_t, uint8_t, "%hhd");

consolegetcalls(parray, parray<uint16_t>, uint16_t, "%hd");
consolegetcalls(ptr, uint16_t*, uint16_t, "%hd");
consolegetcalls(value, uint16_t, uint16_t, "%hd");

consolegetcalls(parray, parray<uint32_t>, uint32_t, "%ld");
consolegetcalls(ptr, uint32_t*, uint32_t, "%ld");
consolegetcalls(value, uint32_t, uint32_t, "%ld");

consolegetcalls(parray, parray<uint64_t>, uint64_t, "%lld");
consolegetcalls(ptr, uint64_t*, uint64_t, "%lld");
consolegetcalls(value, uint64_t, uint64_t, "%lld");