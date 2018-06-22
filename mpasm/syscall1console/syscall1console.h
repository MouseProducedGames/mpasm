#ifndef MPASM_MPASM_SYSCALL1CONSOLE_H
#define MPASM_MPASM_SYSCALL1CONSOLE_H

#include "../syscalls/syscall.h"

enum class syscall1op : uint64_t
{
	write = 1,
	getkey,
	read,
	writechar
};

template<typename T>
const syscallfunc &getsyscall1_console(const syscall1op &op);

template<>
const syscallfunc &getsyscall1_console<int64_t>(const syscall1op &op);

template<>
const syscallfunc &getsyscall1_console<float64_t>(const syscall1op &op);

// We store the funcs in a variable, otherwise it complains of a local variable.
#define consolegetcalls(indirection, type, innertype, format)\
console##indirection##funcs(innertype, format);\
template<>\
const syscallfunc &getsyscall1_console<type>(const syscall1op &op)\
{\
	switch (op)\
	{\
	default: throw std::exception("null system call");\
	case syscall1op::getkey: return (getkey_func<type> = &getkey##indirection####innertype##);\
	case syscall1op::read: return (read_func<type> = &read##indirection####innertype##);\
	case syscall1op::write: return (write_func<type> = &write##indirection####innertype##);\
	case syscall1op::writechar: return (writechar_func<type> = &writechar##indirection####innertype##);\
	}\
}\

#endif // !MPASM_MPASM_SYSCALL1CONSOLE_H
