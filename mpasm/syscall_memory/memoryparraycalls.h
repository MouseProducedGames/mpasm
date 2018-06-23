/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_PARRAYCALLS_H
#define MPASM_MPASM_PARRAYCALLS_H

#include "syscall_memory.h"
#include "data_helpers/data_access.h"

#define allocateparraycode(type)\
size_t length = *((size_t*)(&ctx.stk().at(ctx.SP() -= sizeof(size_t))));\
type * ptr = new type[length];\
parray<type> value(storeptr(type, ptr), length);\
push(value, ctx.stk(), ctx.SP());

#define deallocateparraycode(type)\
/* We don't need the length of the array.
* However, we do need to pop it off the stack.
*/\
ctx.SP() -= sizeof(size_t); \
type * ptr = getmemfullptr(type, &ctx.stk()[ctx.SP() -= sizeof(size_t)]); \
delete[] ptr; \
ptr = nullptr; \
ptr = storeptr(type, ptr);

template<typename T>
static void allocateparray(context &ctx)
{
	allocateparraycode(T);
}

template<typename T>
static void deallocateparray(context &ctx)
{
	deallocateparraycode(T);
}

#define memoryparraycalls(type)\
template<>\
const syscallfunc& getsyscall2_memory<parray<type>>(const memory_op &op)\
{\
	switch (op)\
	{\
	default: throw std::exception("null system call");\
	case memory_op::Allocate: return (allocateparray_func<type*> = &allocateparray<type*>);\
	case memory_op::Deallocate: return (deallocateparray_func<type*> = &deallocateparray<type*>);\
	}\
}

#endif // !MPASM_MPASM_PARRAYCALLS_H
