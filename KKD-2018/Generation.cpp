#include"stdafx.h"
#include"Generation.h"
#include <windows.h>

namespace codegen
{
	struct Func 
	{
		char name[10];
	}; Func func[100];
	void CodeGen(LT::LexTable& LT, IT::IdTable& IT, Log::LOG &out, bool flib)
	{
		int currfunc = 0;
		bool checkMain = false;
		bool isFunc = false; 
		bool isName = false;
		bool isPrint = false;
		bool isInt = false;
		int count = 0;
        *out.stream << UP;
		*out.stream << "namespace GenerationCode\n"\
			"{\n";

		*out.stream << "class Func\n"\
			"{\n";

		char d[10] = "doub";
		char s[10] = "sqr";


		for (int i = 0; i < LT.size; i++)
		{
			switch (LT.table[i].lexema)
			{
				case LEX_MAIN:
				{
					*out.stream << "}\n";
					*out.stream << "class Program\n"\
						"{\n";
					*out.stream << "static void Main(string[] args)\n";
					checkMain = true;
					break;
				}
				case LEX_LEFTTHESIS:
				{
					*out.stream << LEX_LEFTTHESIS;
					break;
				}
				case LEX_RIGHTTHESIS:
				{
					*out.stream << LEX_RIGHTTHESIS;
					isFunc = false;
					break;
				}
				case LEX_LEFTBRACE:
				{
					*out.stream << std::endl << "{" << std::endl;
					if (checkMain)
					{
						*out.stream << "Lib lib = new Lib();\n"\
							"Func func = new Func();\n";
					}
					checkMain = false;
					break;
				}
				case LEX_RETURN:
				{
					*out.stream << "return ";
					break;
				}
				case LEX_BRACELET:
				{
					*out.stream << "}\n" << std::endl;
					break;
				}
				case LEX_PLUS:
				{
					*out.stream << " " << LT.table[i].pn << " ";
					break;
				}
				case LEX_SEMICOLON:
				{
					if (isPrint)
					{
						isInt = false;
						*out.stream << ")";
					}
					*out.stream << LEX_SEMICOLON << std::endl; 
					isPrint = false;

					break;
				}
				case LEX_FUNCTION:
				{
					*out.stream << "public ";
					if (LT.table[i - 1].lexema == 't')
					{
						*out.stream << "int ";
						isInt = true;
					}
					if (LT.table[i - 1].lexema == 's')
					{
						*out.stream << "string ";
						isInt = false;
					}
					isFunc = true;
					isName = true;
					break;
				}
				case LEX_IDENTIFIER:
				{
					if (isPrint && IT.table[LT.table[i - 2].idxTI].iddatatype == IT::STR)
					{
					    *out.stream << IT.table[LT.table[i].idxTI].id_buf;
						break;
					}
					if (LT.table[i - 1].lexema == 't')
					{
						*out.stream << "int ";
						isInt = true;
					}
					if (LT.table[i - 1].lexema == 's')
					{
						*out.stream << "string ";
						isInt = false;
					}
					for (int x = 0; x < 100; x++)
					{
						if (!strcmp(func[x].name, IT.table[LT.table[i].idxTI].id_buf))
							*out.stream << "func.";
					}

					if (!strcmp(d, IT.table[LT.table[i].idxTI].id_buf)|| !strcmp(s, IT.table[LT.table[i].idxTI].id_buf))
						*out.stream << "lib.";
					*out.stream << IT.table[LT.table[i].idxTI].id_buf; // name
					if (isName) 
					{
						strcpy(func[count].name, IT.table[LT.table[i].idxTI].id_buf);
						count++;
						isName = false;
					}
					break;
				}
				case LEX_LITERAL:
				{
					if (IT.table[LT.table[i].idxTI].iddatatype == IT::INT)
						*out.stream << IT.table[LT.table[i].idxTI].value.vint;
					if (IT.table[LT.table[i].idxTI].iddatatype == IT::STR)
						*out.stream << "\"" << IT.table[LT.table[i].idxTI].value.vstr.str << "\"";
					break;
				}
				case LEX_WRITE:
				{
					*out.stream << IT.table[LT.table[++i].idxTI].id_buf << " = ";
					if (isInt)
					{
						*out.stream << "Int32.Parse(Console.ReadLine())";
						isInt = false;
					}
					else
					{
						*out.stream << "Console.ReadLine()";
					}
					continue;
					break;
				}
				case LEX_PRINT:
				{
					isPrint = true;
					*out.stream << "Console.WriteLine(";
					break;
				}
				case LEX_COMMA:
					*out.stream << ", ";
					break;
				case LEX_RAVNO:
				{
					*out.stream << " = ";
					break;
				}
			}
		}
		*out.stream << "}\n"\
			"}\n";
	}
}