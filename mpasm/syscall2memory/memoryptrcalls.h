#ifndef MPASM_MPASM_MEMORYPTRCALLS_H
#define MPASM_MPASM_MEMORYPTRCALLS_H

#include "syscall2memory.h"
#include "data_helpers/data_access.h"

#define allocatecode(type)\
type value = *((type*)(&ctx.stk().at(ctx.SP() -= sizeof(type))));\
auto ptr = new type(value);\
size_t adjusted = (size_t)((uint8_t*)(ptr) - ctx.memadjust());\
push(adjusted, ctx.stk(), ctx.SP());

#define deallocatecode(type)\
size_t tptr = *((size_t*)(&ctx.stk().at(ctx.SP() -= sizeof(size_t))));\
type * value = loadptr(type, tptr);\
delete value;

template<typename T>
static void allocateptr(context &ctx)
{
	allocatecode(T);
}

template<typename T>
static void deallocateptr(context &ctx)
{
	deallocatecode(T);
}

#define memoryptrcalls(type)\
template<>\
const syscallfunc& getsyscall2_memory<type>(const syscall2op &op)\
{\
	switch (op)\
	{\
	default: throw std::exception("null system call");\
	case syscall2op::Allocate: return (allocate_func<type> = &allocateptr<type>);\
	case syscall2op::Deallocate: return (deallocate_func<type> = &deallocateptr<type>);\
	}\
}

#endif // !MPASM_MPASM_MEMORYPTRCALLS_H