/*
* Copyright 2018 Mouse-Produced Games.
* Distributed under the terms of the GNU Lesser General Public Liceense (Version 3, 29 June 2007)
*/

#ifndef MPASM_MPASM_RUNTIMECOMMANDMAP_H
#define MPASM_MPASM_RUNTIMECOMMANDMAP_H

#include "stdafx.h"
#include "icommand.h"

#include "bytecode.h"

class runtimecommandmap : public icommand
{
public:
	bool operator()(DT dt, OP op, ML mla, ML mlb, context &ctx) const override;
};

#endif // !MPASM_MPASM_RUNTIMECOMMANDMAP_H
