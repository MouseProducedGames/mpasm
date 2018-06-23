/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_SYSCALL1CONSOLE_H
#define MPASM_MPASM_SYSCALL1CONSOLE_H

#include "../syscalls/syscall.h"

#include "console_ops.h"

template<typename T>
const syscallfunc &getsyscall1_console(const console_op &op);

template<>
const syscallfunc &getsyscall1_console<int64_t>(const console_op &op);

template<>
const syscallfunc &getsyscall1_console<float64_t>(const console_op &op);

// We store the funcs in a variable, otherwise it complains of a local variable.
#define consolegetcalls(indirection, type, innertype, format)\
console##indirection##funcs(innertype, format);\
template<>\
const syscallfunc &getsyscall1_console<type>(const console_op &op)\
{\
	switch (op)\
	{\
	default: throw std::exception("null system call");\
	case console_op::getkey: return (getkey_func<type> = &getkey##indirection####innertype##);\
	case console_op::read: return (read_func<type> = &read##indirection####innertype##);\
	case console_op::write: return (write_func<type> = &write##indirection####innertype##);\
	case console_op::writechar: return (writechar_func<type> = &writechar##indirection####innertype##);\
	}\
}\

#endif // !MPASM_MPASM_SYSCALL1CONSOLE_H
