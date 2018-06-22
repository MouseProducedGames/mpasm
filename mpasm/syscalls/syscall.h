#ifndef MPASM_MPASM_SYSCALL_H
#define MPASM_MPASM_SYSCALL_H

#include "stdafx.h"
#include <vector>

#include "bytecode.h"
#include "mparray.h"
#include "run_context.h"
#include "syscallid.h"

/* Default setting is Console/Terminal.
* If no Console/Terminal is available on the hardware, then provide a null
* Console/Terminal.
*/
extern syscallid IShortCall;

typedef void (*syscallfunc)(context &ctx);

template<typename T>
const syscallfunc &getcall(
	const syscallid &syscall,
	const uint64_t &subcall
);

template<typename T>
const syscallfunc &getquickshortcall(
	const uint64_t &subcall
);

template<typename T>
const syscallfunc &getsyscall(
	const syscallid &id,
	context &ctx,
	size_t &memloc
);

template<typename T>
const syscallfunc &getshortcall(
	context &ctx,
	size_t &memloc
);

#endif // !MPASM_MPASM_SYSCALL_H