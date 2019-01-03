#pragma once
#define PARM_IN	L"-in:" // ���� ��� ����� ��������� ����
#define PARM_OUT L"-out:" // ���� ��� ����� ���������� ����
#define PARM_LOG_LT L"-LT" 
#define PARM_LOG_IT L"-IT"
#define PARM_LOG_PN L"-PN"
#define PARM_LOG_SA L"-SA"
#define PARM_LOG_CG L"-CG"
#define PARM_LOG L"-log:" // ���� ��� ����� �������
#define PARM_MAX_SIZE 200 // ����. ����� ������ ���������
#define PARM_OUT_DEFAULT_EXT L".out" // ���������� ����� ���������� ���� �� ���������
#define PARM_OUTHTML_DEFAULT_EXT L".cs"
#define PARM_LOG_DEFAULT_EXT L".log" // ���������� ����� ��� ��������� �� ���������
#define PARM_SINT_DEFAULT_EXT L"s.txt" 
#define PARM_LIB_DEFAULT_EXT L"Lib.cs"


namespace Parm // ��������� ������� ����������
{
	struct PARM
	{
		bool LT_log = false; // ����� ������� ������
		bool IT_log = false; // ����� ������� ���������������
		bool PN_log = false; // ������� ��������� � �������� ������
		bool SA_log = false; // ����� ��������������� �������
		bool CG_log = false; // ��������� ����
		bool LIBR = false;
		wchar_t in[PARM_MAX_SIZE]; // -in	��� ����� ��������� ����
		wchar_t out[PARM_MAX_SIZE];
		wchar_t outhtml[PARM_MAX_SIZE]=L"Program";
		wchar_t outsint[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
	};

	PARM getparm(int argc, _TCHAR* argv[]);
	int search(wchar_t id, int argc, _TCHAR* argv[]);
}
#pragma once
