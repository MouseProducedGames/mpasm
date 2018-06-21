#ifndef MPASM_MPASM_PACCESS_H
#define MPASM_MPASM_PACCESS_H

#define getmemfullptr(type, ptr) (type*)((uint8_t*)(*((uint64_t*)ptr)) + memadjust)
#define getmempartialptr(type, ptr) (type*)((uint8_t*)(&ptr) - memadjust)

#define storeptr(type, ptr) (type*)((uint8_t*)(ptr) - memadjust)
#define loadptr(type, ptr) (type*)((uint8_t*)(ptr) + memadjust)

#define getmemloc(type, value) value = getmemfullptr(type, &inst[memloc])
#define setmemloc(type, value) *getmemfullptr(type, &inst[memloc]) = static_cast<type>(*value)

#define getstk(type) ((type*)(&stk[SP - sizeof(type)]))
#define setstk(type, value) *((type*)(&stk[SP - sizeof(type)])) = static_cast<type>(*value)

#define popstk(type) ((type*)(&stk[SP -= sizeof(type)]))

#endif // !MPASM_MPASM_PACCESS_H
