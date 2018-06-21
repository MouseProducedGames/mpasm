#ifndef MPASM_MPASM_CONSOLEPTRFUNCS_H
#define MPASM_MPASM_CONSOLEPTRFUNCS_H

#define ptrgetkey(type)\
type value = (type)_getwch();\
\
type * pvalue = new type(value);\
size_t adjusted = (size_t)((int8_t*)(pvalue) - ctx.memadjust());\
push(adjusted, ctx.stk(), ctx.SP());

#define ptrread(type)\
type value; \
std::cin >> value;\
\
type * pvalue = new type(value);\
size_t adjusted = (size_t)((int8_t*)(pvalue) - ctx.memadjust());\
push(adjusted, ctx.stk(), ctx.SP());

#define ptrwrite(type, format)\
size_t tptr = *((size_t*)(&ctx.stk().at(ctx.SP() - sizeof(size_t))));\
type * pvalue = (type*)((uint8_t*)(tptr) + ctx.memadjust());\
ctx.SP() -= sizeof(size_t);\
static const size_t BUFFER_COUNT = 255;\
char buffer[BUFFER_COUNT];\
sprintf_s(buffer, format, *pvalue);\
printf(buffer);

#define ptrwritechar(type)\
size_t tptr = *((size_t*)(&ctx.stk().at(ctx.SP() - sizeof(size_t))));\
type * pvalue = (type*)((uint8_t*)(tptr) + ctx.memadjust());\
ctx.SP() -= sizeof(size_t);\
putchar((wchar_t)(*pvalue));

#define consoleptrfuncs(type, format)\
static void getkeyptr##type##(context &ctx)\
{\
	ptrgetkey(type);\
}\
\
static void readptr##type##(context &ctx)\
{\
	ptrread(type);\
}\
\
static void writeptr##type##(context &ctx)\
{\
	ptrwrite(type, format);\
}\
\
static void writecharptr##type##(context &ctx)\
{\
	ptrwritechar(type);\
}\

#endif // !MPASM_MPASM_CONSOLEPTRFUNCS_H

