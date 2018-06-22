#ifndef MPASM_MPASM_SYSCALL2MEMORY_H
#define MPASM_MPASM_SYSCALL2MEMORY_H

#include "syscall.h"
#include "ptrfuncs.h"
#include "run_context.h"

enum class syscall2op : uint64_t
{
	Allocate = 1,
	Deallocate
};

// extern syscallfunc allocate_i64_func;
// extern syscallfunc deallocate_i64_func;

template<typename T>
syscallfunc allocate_func;
template<typename T>
syscallfunc deallocate_func;

template<typename T>
syscallfunc allocateparray_func;
template<typename T>
syscallfunc deallocateparray_func;

#define allocatecode(type)\
type value = *((type*)(&ctx.stk().at(ctx.SP() - sizeof(type))));\
ctx.SP() -= sizeof(type);\
auto ptr = new type(value);\
size_t adjusted = (size_t)((uint8_t*)(ptr) - ctx.memadjust());\
push(adjusted, ctx.stk(), ctx.SP());

#define deallocatecode(type)\
size_t tptr = *((size_t*)(&ctx.stk().at(ctx.SP() - sizeof(size_t))));\
type * value = (type*)((uint8_t*)(tptr) + ctx.memadjust());\
ctx.SP() -= sizeof(size_t);\
delete value;

#define allocateparraycode(type)\
size_t length = *((size_t*)(&ctx.stk().at(ctx.SP() -= sizeof(size_t))));\
type * ptr = new type[length];\
mparray<type> value(storeptr(type, ptr), length);\
push(value, ctx.stk(), ctx.SP());

#define deallocateparraycode(type)\
/* We don't need the length of the array.
* However, we do need to pop it off the stack.
*/\
ctx.SP() -= sizeof(size_t); \
type * ptr = getmemfullptr(type, &ctx.stk()[ctx.SP() -= sizeof(size_t)]);\
delete[] ptr;\
ptr = nullptr;\
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

template<typename T>
const syscallfunc &getsyscall2_memory(const syscall2op &op);

#define memoryparraycalls(type)\
template<>\
const syscallfunc& getsyscall2_memory<mparray<type>>(const syscall2op &op)\
{\
	switch (op)\
	{\
	default: throw std::exception("null system call");\
	case syscall2op::Allocate: return (allocateparray_func<type*> = &allocateparray<type*>);\
	case syscall2op::Deallocate: return (deallocateparray_func<type*> = &deallocateparray<type*>);\
	}\
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

#endif // !MPASM_MPASM_SYSCALL1CONSOLE_H
