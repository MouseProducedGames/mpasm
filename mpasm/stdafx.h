// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here

// Comment this out to build a full version.
#define TESTCODE

#include <cmath>
#include <stddef.h>
#include <stdint.h>

typedef unsigned char byte;
typedef char sbyte;

typedef float float32_t;
typedef double float64_t;

int64_t log(const int64_t &value, const int64_t &newbase);

template<typename T>
T log(const T &value, const T &newbase)
{
	return (T)(std::log(value) / std::log(newbase));
}