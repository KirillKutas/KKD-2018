#include "stdafx.h"

namespace LT
{
	LexTable Create(int size)
	{
		LexTable rc;
		rc.table = new Entry[size];
		rc.maxsize = size;
		rc.size = 0;
		std::memset(rc.table, 0xff, sizeof(Entry)*size);
		return rc;
	}
	void Add(LexTable& lextable, Entry entry)
	{
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}
	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}
	void Delete(LexTable& lextable)
	{
		delete lextable.table;
	}
}