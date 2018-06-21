#ifndef MPASM_MPASM_CONSOLEPARRAYFUNCS_H
#define MPASM_MPASM_CONSOLEPARRAYFUNCS_H

#include "stdafx.h"

#include <iostream>
#include <string>

#define parraygetkey(type)\
size_t length = *((size_t*)(&stk.at(SP -= sizeof(size_t))));\
size_t tptr = *((size_t*)(&stk.at(SP -= sizeof(size_t))));\
type * ptr = (type*)(size_t*)((uint8_t*)(tptr) + memadjust);\
mparray<type> value(ptr, length);\
size_t i = 0;\
while (i < value.length())\
{\
	value[i++] = (type)_getwch();\
}

#define parrayread(type)\
std::wstring s;\
std::wcin >> s;\
type * ptr = new type[s.length()]; \
size_t i = 0;\
while (i < s.length())\
{\
	ptr[i] = (type)s[i];\
	++i;\
}\
ptr = storeptr(type, ptr);\
mparray<type> value(ptr, s.length());\
push(value, stk, SP);

#define parraywrite(type, format)\
size_t length = *((size_t*)(&stk.at(SP -= sizeof(size_t))));\
size_t tptr = *((size_t*)(&stk.at(SP -= sizeof(size_t))));\
static const size_t BUFFER_COUNT = 255;\
char buffer[BUFFER_COUNT];\
sprintf_s(buffer, format, (type)tptr);\
printf(buffer);

#define parraywritechar(type)\
size_t length = *((size_t*)(&stk.at(SP -= sizeof(size_t)))); \
type * tptr = ((type*)(&stk.at(SP -= sizeof(size_t))));\
type * ptr = getmemfullptr(type, tptr);\
mparray<type> value(ptr, length);\
size_t i = 0;\
while (i < value.length() && value[i] != '\0')\
{\
	putchar((wchar_t)value[i++]);\
}

#define consoleparrayfuncs(type, format)\
static void getkeyparray##type##(std::vector<byte> &stk, size_t &SP, const size_t memadjust)\
{\
	parraygetkey(type);\
}\
\
static void readparray##type##(std::vector<byte> &stk, size_t &SP, const size_t memadjust)\
{\
	parrayread(type);\
}\
\
static void writeparray##type##(std::vector<byte> &stk, size_t &SP, const size_t memadjust)\
{\
	parraywrite(type, format);\
}\
\
static void writecharparray##type##(std::vector<byte> &stk, size_t &SP, const size_t memadjust)\
{\
	parraywritechar(type);\
}

#endif // !MPASM_MPASM_CONSOLEPARRAYFUNCS_H

