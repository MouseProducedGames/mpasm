/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

// mpasm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "bytecode.h"
#include "run_context.h"
#include "runtime/runtimecommandmap.h"

template<typename T>
T pop(std::vector<byte> &stk)
{
	T output = ((T)(stk.at(stk.size() - sizeof(T))));
	stk.resize(stk.size() - sizeof(T));
	return output;
}

// Used in the full, non-test version.
#ifndef TESTCODE
int main(int argc, char* argv[])
#else
// Not used in the test code version.
int main(int, char*)
#endif // !TESTCODE
{
#ifndef TESTCODE
	if (argc <= 0)
	{
		// ERROR_BAD_ARGUMENTS
		return 0xA0;
	}
	std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
#else
	std::ifstream file("pahello.mpasm", std::ios::binary | std::ios::ate);
#endif // !TESTCODE

	if (file.good() == false)
	{
		// ERROR_FILE_NOT_FOUND
		return 0x2;
	}

	auto fsize = file.tellg();
	size_t tfsize = static_cast<size_t>(fsize);
	std::unique_ptr<byte[]> fbytes(new byte[(size_t)tfsize]);
	file.seekg(std::ios::beg);
	file.read((char*)fbytes.get(), fsize);
	file.close();
	
	const size_t staticDataLoc = (size_t)(*((psize*)fbytes.get() + 0));
	const size_t staticDataSize = (size_t)(*((psize*)fbytes.get() + 1));
	const size_t programLoc = (size_t)(*((psize*)fbytes.get() + 2));
	const size_t programSize = (size_t)(*((psize*)fbytes.get() + 3));

	if (staticDataSize > tfsize ||
		programSize > tfsize ||
		staticDataLoc + staticDataSize + programSize != tfsize
		)
	{
		// ERROR_INSTRUCTION_MISALIGNMENT
		return 0x225;
	}

	std::unique_ptr<byte[]> mem(new byte[static_cast<size_t>(staticDataSize)]);
	memcpy(
		mem.get(),
		&fbytes.get()[static_cast<size_t>(staticDataLoc)],
		static_cast<size_t>(staticDataSize)
	);
	const size_t memadjust = (size_t)mem.get();
	std::vector<uint8_t> inst;
	inst.reserve(static_cast<size_t>(programSize));
	inst.resize(static_cast<size_t>(programSize));
	size_t IP = 0;
	memcpy(&inst.at(0), &fbytes.get()[static_cast<size_t>(programLoc)], static_cast<size_t>(programSize));
	std::vector<byte> stk;

	size_t SP = stk.size();
	stk.reserve(4096);
	stk.resize(4096);
	std::unique_ptr<icommand> commandmap(new runtimecommandmap());
	context(*commandmap.get(), inst, IP, stk, SP, memadjust);

	return 0;
}
