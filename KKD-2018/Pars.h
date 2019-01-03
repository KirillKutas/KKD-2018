#pragma once

#include "stdafx.h"
#define IF_LIB ""

namespace P
{
	struct LEX
	{
		LT::LexTable Lextable;
		IT::IdTable Idtable;
	};

	In::element deleterp(In::IN in);
	void add(char* &buff, int &temp, In::element &ml, char current);
	In::element split(In::element el, In::IN in);
	LEX Par(In::IN in, Error::ERRORS& table, Parm::PARM parm, bool &flib, Log::LOG log);
	void output_LT(Log::LOG log, LT::LexTable lextable);
	void output_IT(Log::LOG log, IT::IdTable idtable);
}
