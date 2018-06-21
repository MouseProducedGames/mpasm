#include "stdafx.h"
#include "syscall2memory.h"

#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "dthelper.h"
#include "mparray.h"

memoryptrcalls(float32_t);
memoryptrcalls(float64_t);
memoryptrcalls(int8_t);
memoryptrcalls(int16_t);
memoryptrcalls(int32_t);
memoryptrcalls(int64_t);
memoryptrcalls(uint8_t);
memoryptrcalls(uint16_t);
memoryptrcalls(uint32_t);
memoryptrcalls(uint64_t);

memoryptrcalls(float32_t*);
memoryptrcalls(float64_t*);
memoryptrcalls(int8_t*);
memoryptrcalls(int16_t*);
memoryptrcalls(int32_t*);
memoryptrcalls(int64_t*);
memoryptrcalls(uint8_t*);
memoryptrcalls(uint16_t*);
memoryptrcalls(uint32_t*);
memoryptrcalls(uint64_t*);

memoryparraycalls(float32_t);
memoryparraycalls(float64_t);
memoryparraycalls(int8_t);
memoryparraycalls(int16_t);
memoryparraycalls(int32_t);
memoryparraycalls(int64_t);
memoryparraycalls(uint8_t);
memoryparraycalls(uint16_t);
memoryparraycalls(uint32_t);
memoryparraycalls(uint64_t);