#pragma once
#define PARM_IN	L"-in:" // ключ для файла исходного кода
#define PARM_OUT L"-out:" // ключ для файла объектного кода
#define PARM_LOG_LT L"-LT" 
#define PARM_LOG_IT L"-IT"
#define PARM_LOG_PN L"-PN"
#define PARM_LOG_SA L"-SA"
#define PARM_LOG_CG L"-CG"
#define PARM_LOG L"-log:" // ключ для файла журнала
#define PARM_MAX_SIZE 200 // макс. длина строки параметра
#define PARM_OUT_DEFAULT_EXT L".out" // расширение файла объектного кода по умолчанию
#define PARM_OUTHTML_DEFAULT_EXT L".cs"
#define PARM_LOG_DEFAULT_EXT L".log" // расширение файла для протокола по умолчанию
#define PARM_SINT_DEFAULT_EXT L"s.txt" 
#define PARM_LIB_DEFAULT_EXT L"Lib.cs"


namespace Parm // обработка входных параметров
{
	struct PARM
	{
		bool LT_log = false; // вывод таблицы лексем
		bool IT_log = false; // вывод таблицы идентификаторов
		bool PN_log = false; // перевод выражений в польскую запись
		bool SA_log = false; // вывод синтаксического анализа
		bool CG_log = false; // генерация кода
		bool LIBR = false;
		wchar_t in[PARM_MAX_SIZE]; // -in	имя файла исходного кода
		wchar_t out[PARM_MAX_SIZE];
		wchar_t outhtml[PARM_MAX_SIZE]=L"Program";
		wchar_t outsint[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
	};

	PARM getparm(int argc, _TCHAR* argv[]);
	int search(wchar_t id, int argc, _TCHAR* argv[]);
}
#pragma once
