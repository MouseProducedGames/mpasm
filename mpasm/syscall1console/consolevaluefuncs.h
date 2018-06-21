#ifndef MPASM_MPASM_CONSOLEVALUEFUNCS_H
#define MPASM_MPASM_CONSOLEVALUEFUNCS_H

#define valuegetkey(type)\
type value = (type)_getwch();\
push(value, stk, SP);

#define valueread(type)\
type value;\
std::cin >> value;\
push(value, stk, SP);

#define valuewrite(type, format)\
const type value =\
	*((const type*)(&stk.at(SP - sizeof(type))));\
SP -= sizeof(type);\
static const size_t BUFFER_COUNT = 255;\
char buffer[BUFFER_COUNT];\
sprintf_s(buffer, format, value);\
printf(buffer);

#define valuewritechar(type)\
const type value =\
	*((const type*)(&stk.at(SP -= sizeof(type))));\
putchar((wchar_t)value);

#define consolevaluefuncs(type, format)\
static void getkeyvalue##type##(std::vector<byte> &stk, size_t &SP, const size_t memadjust)\
{\
	valuegetkey(type);\
}\
\
static void readvalue##type##(std::vector<byte> &stk, size_t &SP, const size_t memadjust)\
{\
	valueread(type);\
}\
\
static void writevalue##type##(std::vector<byte> &stk, size_t &SP, const size_t memadjust)\
{\
	valuewrite(type, format);\
}\
\
static void writecharvalue##type##(std::vector<byte> &stk, size_t &SP, const size_t memadjust)\
{\
	valuewritechar(type);\
}\

#endif // !MPASM_MPASM_CONSOLEVALUEFUNCS_H
