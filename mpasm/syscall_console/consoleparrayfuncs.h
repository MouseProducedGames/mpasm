/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_CONSOLEPARRAYFUNCS_H
#define MPASM_MPASM_CONSOLEPARRAYFUNCS_H

#define parraygetkey(type)\
size_t length = *((size_t*)(&ctx.stk().at(ctx.SP() -= sizeof(size_t))));\
size_t tptr = *((size_t*)(&ctx.stk().at(ctx.SP() -= sizeof(size_t))));\
type * ptr = (type*)(size_t*)((uint8_t*)(tptr) + ctx.memadjust());\
parray<type> value(ptr, length);\
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
parray<type> value(ptr, s.length());\
push(value, ctx.stk(), ctx.SP());

#define parraywrite(type, format)\
/* We don't need the length of the array.
 * However, we do need to pop it off the stack.
 */\
ctx.SP() -= sizeof(size_t);\
size_t tptr = *((size_t*)(&ctx.stk().at(ctx.SP() -= sizeof(size_t))));\
static const size_t BUFFER_COUNT = 255;\
char buffer[BUFFER_COUNT];\
sprintf_s(buffer, format, (type)tptr);\
printf(buffer);

#define parraywritechar(type)\
size_t length = *((size_t*)(&ctx.stk().at(ctx.SP() -= sizeof(size_t)))); \
type * tptr = ((type*)(&ctx.stk().at(ctx.SP() -= sizeof(size_t))));\
type * ptr = getmemfullptr(type, tptr);\
parray<type> value(ptr, length);\
size_t i = 0;\
while (i < value.length() && value[i] != '\0')\
{\
	putchar((wchar_t)value[i++]);\
}

#define consoleparrayfuncs(type, format)\
static void getkeyparray##type##(context &ctx)\
{\
	parraygetkey(type);\
}\
\
static void readparray##type##(context &ctx)\
{\
	parrayread(type);\
}\
\
static void writeparray##type##(context &ctx)\
{\
	parraywrite(type, format);\
}\
\
static void writecharparray##type##(context &ctx)\
{\
	parraywritechar(type);\
}

#endif // !MPASM_MPASM_CONSOLEPARRAYFUNCS_H

