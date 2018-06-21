#ifndef MPASM_MPASM_SYSCALL2MEMORY_H
#define MPASM_MPASM_SYSCALL2MEMORY_H

#include "syscall.h"
#include "ptrfuncs.h"

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
type value = *((type*)(&stk.at(SP - sizeof(type))));\
SP -= sizeof(type);\
auto ptr = new type(value);\
size_t adjusted = (size_t)((uint8_t*)(ptr) - memadjust);\
push(adjusted, stk, SP);

#define deallocatecode(type)\
size_t tptr = *((size_t*)(&stk.at(SP - sizeof(size_t))));\
type * value = (type*)((uint8_t*)(tptr) + memadjust);\
SP -= sizeof(size_t);\
delete value;

#define allocateparraycode(type)\
size_t length = *((size_t*)(&stk.at(SP -= sizeof(size_t))));\
type * ptr = new type[length];\
mparray<type> value(ptr, length);\
push(value, stk, SP);

#define deallocateparraycode(type)\
size_t * length = ((size_t*)(&stk.at(SP -= sizeof(size_t))));\
type * ptr = getmemfullptr(type, &stk[SP -= sizeof(size_t)]);\
delete[] ptr;\
ptr = nullptr;\
ptr = storeptr(type, ptr);

template<typename T>
static void allocateparray(std::vector<byte> &stk, size_t &SP, const size_t memadjust)
{
	allocateparraycode(T);
}

template<typename T>
static void deallocateparray(std::vector<byte> &stk, size_t &SP, const size_t memadjust)
{
	deallocateparraycode(T);
}

template<typename T>
static void allocateptr(std::vector<byte> &stk, size_t &SP, const size_t memadjust)
{
	allocatecode(T);
}

template<typename T>
static void deallocateptr(std::vector<byte> &stk, size_t &SP, const size_t memadjust)
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
