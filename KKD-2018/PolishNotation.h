#pragma once
#include "LT.h"
#include "IT.h"
namespace PN
{
	void PolishNotation(int& lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
	void DoPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable);
}