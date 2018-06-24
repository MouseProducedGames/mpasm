/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_RUNTIMECONSOLECALLHIVE_H
#define MPASM_MPASM_RUNTIMECONSOLECALLHIVE_H

#include "stdafx.h"

#include <conio.h>
#include <iostream>

#include "isubcallhive.h"

template<typename T>
class runtimeconsolecallhive : public isubcallhive<T>
{
public:
	bool operator()(uint64_t subcall, context &ctx) const override;
};

#endif // !MPASM_MPASM_RUNTIMECONSOLECALLHIVE_H
