#include "stdafx.h"
#include "Library.h"

namespace libr
{
	void lib(Log::LOG log)
	{
		*log.stream <<
			"using System;\n"\
			"using System.Collections.Generic;\n"\
			"using System.Linq;\n"\
			"using System.Text;\n"\
			"using System.Threading.Tasks;\n"\
			"namespace GenerationCode\n"\
			"{\n"\
			"class Lib\n"\
			"{\n"\
			"public double sqr(int x)"\
			"{\n"\
			"return Math.Sqrt(x); \n"\
			"}\n"\
			"public int doub(int x)\n"\
			"{\n"\
			"return x*x;\n"\
			"}\n"\
			"}\n"\
			"}\n";
	}
}