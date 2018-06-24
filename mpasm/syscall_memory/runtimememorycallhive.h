/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef RUNTIMEMEMORYCALLHIVE_H
#define RUNTIMEMEMORYCALLHIVE_H

#include "stdafx.h"

#include "isubcallhive.h"
#include "memory_ops.h"

template<typename T>
class runtimemorycallhive : public isubcallhive<T>
{
public:
	bool operator()(uint64_t subcall, context &ctx) const override;
};

#endif // !RUNTIMEMEMORYCALLHIVE_H
