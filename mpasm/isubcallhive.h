/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_IMEMORYCALLHIVE_H
#define MPASM_MPASM_IMEMORYCALLHIVE_H

#include "stdafx.h"

class context;

template<typename T>
class isubcallhive
{
public:
	virtual bool operator()(uint64_t subcall, context &ctx) const = 0;
};

#endif // !MPASM_MPASM_IMEMORYCALLHIVE_H
