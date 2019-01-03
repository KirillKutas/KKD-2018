#pragma once
#define ID_MAXSIZE 10 // ������������ ���������� �������� � ��������������
#define TI_MAXSIZE 4096 // ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT 0x00000000 // �������� �� ��������� ��� int
#define	TI_STR_DEFAULT 0x00 // �������� �� ��������� ��� str
#define TI_NULLIDX 0xffffffff // ��� �������� ������� ���������������
#define	TI_STR_MAXSIZE 255

namespace IT // ������� ���������������
{
	enum IDDATATYPE { DEFD = 0, INT = 1, STR = 2 }; // ���� ������ ���������������
	enum IDTYPE { DEFT = 0, V = 1, P = 2, F = 3, L = 4 }; // ���� ��������������� (����������, ��������, �������, �������)

	struct Entry //������ ��
	{
		int idxfirstLE; // ������ ������ ������ � ������� ������
		char id_buf[ID_MAXSIZE]; // �������������(��� ���. ���.)
		char id[ID_MAXSIZE*2]; // �������������
		char idvis[ID_MAXSIZE]; // ������� ��������� ��������������
		bool is_to = false;
		IDDATATYPE iddatatype; // ��� ������ (1-�����, 2-�������)
		IDTYPE idtype; // ��� ��������������
		union
		{
			int vint; // �������� int
			struct
			{
				uc len;// ���������� �������� � str
				char str[TI_STR_MAXSIZE - 1]; // ������� str
			} vstr; // �������� str
		} value; // �������� ��������������
		Entry() 
		{ 
			iddatatype = IT::DEFD; 
		    idtype = IT::DEFT; 
		    is_to = false; 
		    idxfirstLE = TI_NULLIDX;
		    memset(id, NULL, strlen(id)); 
		    memset(id_buf, NULL, strlen(id_buf)); 
		}
	};

	struct IdTable //��������� ������� ���������������
	{
		bool if_double_i = false;
		int IT_num = 0;
		bool f_main = false;
		bool f_parm = false;
		int maxsize; // ������� ��
		char literals[30][100];
		int size; // ������� ������ ��
		int litCount; // ���������� ���������
		Entry* table; //  ������ ����� ��
		int getidnum(char* c)
		{
			int k = size;
			while  (k >= 0  && strcmp(table[k].id_buf, c))
				k--;
			return k >= 0 ? k : -1;
		}
	};

	IdTable Create(int size); // ������� ��(������� ��)
	void Add(IdTable&idtable, Entry entry); // �������� ������ � ��(��������� ��, ������ ��)
	Entry GetEntry(IdTable& idtable, int n);// �������� ������ ��(��������� ��,����� ���������� ������)
	int IsId(IdTable& idtable,char id[ID_MAXSIZE], char* idvis);// �������: ����� ������ (���� ����), TI_NULLIDX (���� ���)
	void Delete(IdTable& idtable);
	int IsLiteral(IdTable& idtable, char *litrl);
}