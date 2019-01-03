#include "stdafx.h"

namespace Parm
{ // ID - подстрока
	int search(wchar_t* s_id, int argc, _TCHAR* argv[])
	{
		int id = -1;
		for (int i(1); i < argc; i++)
		{
			if (wcsstr(argv[i], s_id) != 0) // wcsstr - если в строке подстрока
				id = i;
		}
		return id;
	}

	PARM getparm(int argc, _TCHAR* argv[]) // argc - кол. передаваемых параметров, argv - массив на указателей элементов этих параметров
	{
		PARM Parm;
		int id; // положение

		for (int i(1); i < argc; i++)
			if (wcslen(argv[i]) > PARM_MAX_SIZE) throw ERROR_THROW(3)
			if ((id = search(PARM_IN, argc, argv)) < 0) throw ERROR_THROW(2)
			else wcscpy_s(Parm.in, argv[id] + wcslen(PARM_IN));

		if ((id = search(PARM_OUT, argc, argv)) < 0)
		{
			wcscpy_s(Parm.out, Parm.in);
			wcscat_s(Parm.out, PARM_OUT_DEFAULT_EXT); // wcscat - соединение строк
		}
		else wcscpy_s(Parm.out, argv[id] + wcslen(PARM_OUT));

		if ((id = search(PARM_LOG, argc, argv)) < 0)
		{
			wchar_t sa[200];
			wcsncpy_s(sa, Parm.in, 4);
			wcscpy_s(Parm.log, sa);
			wcscat_s(Parm.log, PARM_LOG_DEFAULT_EXT);
			wcscat_s(Parm.outhtml, PARM_OUTHTML_DEFAULT_EXT);
			wcscpy_s(Parm.outsint, sa);
			wcscat_s(Parm.outsint, PARM_SINT_DEFAULT_EXT);
		}
		else {
			wcscpy_s(Parm.log, argv[id] + wcslen(PARM_LOG));
			wcscpy_s(Parm.outhtml, argv[id] + wcslen(PARM_LOG));
			wcscpy_s(Parm.outsint, argv[id] + wcslen(PARM_LOG));
		}

		if ((id = search(PARM_LOG_IT, argc, argv)) > 0) Parm.IT_log = true;
		if ((id = search(PARM_LOG_LT, argc, argv)) > 0) Parm.LT_log = true;
		if ((id = search(PARM_LOG_PN, argc, argv)) > 0) Parm.PN_log = true;
		if ((id = search(PARM_LOG_SA, argc, argv)) > 0) Parm.SA_log = true;
		if ((id = search(PARM_LOG_CG, argc, argv)) > 0) Parm.CG_log = true;
		return Parm;
	}
	int search(wchar_t id, int argc, _TCHAR * argv[])
	{
		return 0;
	}
}

/*
wcscpy - копирование
wcscat - соединение строк
wcslen - длина
wcsstr - если в строке подстрока
*/