
#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	Log::LOG log = Log::INITLOG; // ����� ��� ������ ���������
	Log::LOG loghtml = Log::INITLOG; // ����� ��� ����� ��������� ����
	Log::LOG logsint = Log::INITLOG; // ����� ��� ������ ��������������� �������
	Log::LOG loglib = Log::INITLOG; // ���� ����������� ����������
	try
	{
		bool flib = false;
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "����:", " ��� ������", "");

		Error::ERRORS table = Error::createTable(MAX_NUMBER_OF_ERRORS);
		In::IN in = Log::getin(parm.in, log, table);
		Log::WriteIn(log, in);
		P::LEX tables = P::Par(in, table, parm, flib, log);
		if (flib) parm.LIBR = true;
		Log::WriteParm(log, parm);
		Log::WriteLog(log);

		if (parm.SA_log) // �������������� ������
		{
			logsint = Log::getlog(parm.outsint);
			MFST::Do_Sentence_Analysis(logsint, tables, table);
		}
		if(table.size == 0)
		{
			if (parm.CG_log) // ��������� ����
			{
				if (flib) // lib.connect
				{
					loglib = Log::getlog(PARM_LIB_DEFAULT_EXT);
					libr::lib(loglib);
				}
				loghtml = Log::getlog(parm.outhtml);
				codegen::CodeGen(tables.Lextable, tables.Idtable, loghtml, flib);
			}
			if (parm.PN_log) PN::DoPolishNotation(tables.Lextable, tables.Idtable); // �������� ������
			if (!table.sinterrs)
			{
				if (parm.LT_log) P::output_LT(log, tables.Lextable); // ����� � ���
				if (parm.IT_log) P::output_IT(log, tables.Idtable); // ����� � ���
			}
			else *log.stream << "\n------� ���� ������ ��������������� ����������� �������� ������.------\n\n";
		}
		else
		{
			*log.stream << "\n------ ������ ������ ------\n\n";
			for (int i = 0; i < table.size; i++) Log::WriteError(log, table.errors[i]);
		}

		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		std::cout << "\t\t\t------����������� ������------\n\n" << "��� ������: " << e.id << ". " << e.message << std::endl << std::endl;
	}
	system("pause");
	return 0;
}