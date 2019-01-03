#include "stdafx.h"

In::IN Log::getin(wchar_t infile[], LOG log, Error::ERRORS& table)
{
	In::IN rc;
	int position = 0;
	bool flag_for_resh = false;
	uc simbol;
	rc.size = rc.ignor = 0;
	rc.text = new uc[IN_MAX_LEN_TEXT];
	rc.lines = 1;
	std::ifstream fin(infile);
	if (!fin.is_open()) throw ERROR_THROW(5);
	simbol = fin.get();
	while (!fin.eof())
	{
		switch (rc.code[simbol])
		{
		case rc.K: 
			while (rc.code[simbol] != rc.N)
			{
				simbol = fin.get();
			};  rc.size--; break;
		case rc.N: rc.text[rc.size] = '|'; rc.lines++;	position = 0; break;
		case rc.F: table.pushError(101, rc.lines, position); rc.size--; break; // ошибка 101
		case rc.T: case rc.P: case rc.R: case rc.O: case rc.S: rc.text[rc.size] = simbol; break;
		}
		position++;
		rc.size++;
		flag_for_resh = true;
		simbol = fin.get();
	}
	rc.text[rc.size] = 0x00;
	return rc;
}