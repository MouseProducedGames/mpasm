/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_CONSOLEVALUEFUNCS_H
#define MPASM_MPASM_CONSOLEVALUEFUNCS_H

#define valuegetkey(type)\
type value = (type)_getwch();\
push(value, ctx.stk(), ctx.SP());

#define valueread(type)\
type value;\
std::cin >> value;\
push(value, ctx.stk(), ctx.SP());

#define valuewrite(type, format)\
const type value =\
	*((const type*)(&ctx.stk().at(ctx.SP() - sizeof(type))));\
ctx.SP() -= sizeof(type);\
static const size_t BUFFER_COUNT = 255;\
char buffer[BUFFER_COUNT];\
sprintf_s(buffer, format, value);\
printf(buffer);

#define valuewritechar(type)\
const type value =\
	*((const type*)(&ctx.stk().at(ctx.SP() -= sizeof(type))));\
putchar((wchar_t)value);

#define consolevaluefuncs(type, format)\
static void getkeyvalue##type##(context &ctx)\
{\
	valuegetkey(type);\
}\
\
static void readvalue##type##(context &ctx)\
{\
	valueread(type);\
}\
\
static void writevalue##type##(context &ctx)\
{\
	valuewrite(type, format);\
}\
\
static void writecharvalue##type##(context &ctx)\
{\
	valuewritechar(type);\
}\

#endif // !MPASM_MPASM_CONSOLEVALUEFUNCS_H
