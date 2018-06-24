/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_ICOMMAND_H
#define MPASM_MPASM_ICOMMAND_H

class context;

#include "bytecode.h"

class icommand
{
public:
	virtual bool operator()(DT dt, OP op, ML mla, ML mlb, context &ctx) const = 0;
};

#endif