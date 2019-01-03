#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"
#define UP 			"using System;\n"\
			"using System.Collections.Generic;\n"\
			"using System.Linq;\n"\
			"using System.Text;\n"\
			"using System.Threading.Tasks;\n"


namespace codegen
{
	void CodeGen(LT::LexTable& LT, IT::IdTable& IT, Log::LOG &out, bool flib);
}