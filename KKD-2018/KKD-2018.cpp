
#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	Log::LOG log = Log::INITLOG; // поток для записи протокола
	Log::LOG loghtml = Log::INITLOG; // поток для этапа генерации кода
	Log::LOG logsint = Log::INITLOG; // поток для вывода синтаксического анализа
	Log::LOG loglib = Log::INITLOG; // файл стандартной библиотеки
	try
	{
		bool flib = false;
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест:", " Без ошибок", "");

		Error::ERRORS table = Error::createTable(MAX_NUMBER_OF_ERRORS);
		In::IN in = Log::getin(parm.in, log, table);
		Log::WriteIn(log, in);
		P::LEX tables = P::Par(in, table, parm, flib, log);
		if (flib) parm.LIBR = true;
		Log::WriteParm(log, parm);
		Log::WriteLog(log);

		if (parm.SA_log) // синтаксический анализ
		{
			logsint = Log::getlog(parm.outsint);
			MFST::Do_Sentence_Analysis(logsint, tables, table);
		}
		if(table.size == 0)
		{
			if (parm.CG_log) // генерация кода
			{
				if (flib) // lib.connect
				{
					loglib = Log::getlog(PARM_LIB_DEFAULT_EXT);
					libr::lib(loglib);
				}
				loghtml = Log::getlog(parm.outhtml);
				codegen::CodeGen(tables.Lextable, tables.Idtable, loghtml, flib);
			}
			if (parm.PN_log) PN::DoPolishNotation(tables.Lextable, tables.Idtable); // польская запись
			if (!table.sinterrs)
			{
				if (parm.LT_log) P::output_LT(log, tables.Lextable); // вывод в лог
				if (parm.IT_log) P::output_IT(log, tables.Idtable); // вывод в лог
			}
			else *log.stream << "\n------В ходе работы синтаксического анализатора возникли ошибки.------\n\n";
		}
		else
		{
			*log.stream << "\n------ Список ошибок ------\n\n";
			for (int i = 0; i < table.size; i++) Log::WriteError(log, table.errors[i]);
		}

		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		std::cout << "\t\t\t------Критическая ошибка------\n\n" << "Код ошибки: " << e.id << ". " << e.message << std::endl << std::endl;
	}
	system("pause");
	return 0;
}