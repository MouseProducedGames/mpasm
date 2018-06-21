#ifndef MPASM_MPASM_PACCESS_H
#define MPASM_MPASM_PACCESS_H

#define getmemfullptr(type, ptr) (type*)((uint8_t*)(*((uint64_t*)ptr)) + ctx.memadjust())
#define getmempartialptr(type, ptr) (type*)((uint8_t*)(&ptr) - ctx.memadjust())

#define storeptr(type, ptr) (type*)((uint8_t*)(ptr) - ctx.memadjust())
#define loadptr(type, ptr) (type*)((uint8_t*)(ptr) + ctx.memadjust())

#define getmemloc(type, value) value = getmemfullptr(type, &ctx.inst()[memloc])
#define setmemloc(type, value) *getmemfullptr(type, &ctx.inst()[memloc]) = static_cast<type>(*value)

#define getstk(type) ((type*)(&ctx.stk()[ctx.SP() - sizeof(type)]))
#define setstk(type, value) *((type*)(&ctx.stk()[ctx.SP() - sizeof(type)])) = static_cast<type>(*value)

#define popstk(type) ((type*)(&ctx.stk()[ctx.SP() -= sizeof(type)]))

#endif // !MPASM_MPASM_PACCESS_H
