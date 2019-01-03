#include "stdafx.h"
#define IN_ID TOTAL_KA-3 // TOTAL_KA == ���-�� ���������


#define SQUARE L"square"
#define DOUBLE1 L"double"

namespace P
{
	START_FSATable // ������ ��������� (in FST.h)
		INTEGER, STRING, FUNCTION, DECLARE, RETURN, PRINT, WRITE, MAIN, SEMICOLON, COMMA, LEFTBRACE, BRACELET, LEFTTHESIS, RIGHTTHESIS, PLUS, MINUS, STAR, DIRSLASH, RAVNO, LITERAL_1, LITERAL_2, IDENTIFIER, FINISH_FSATable

		void add(char* &buff, int &temp, In::element &ml, char current) // �������� � ���������
	{
		buff[temp++] = current; // ���������� ������� ������
		buff[temp] = '\0'; // ����� ������
		temp = NULL; // ��������
		ml.mtxt[ml.msize] = new char[strlen(buff) + 1];
		strcpy_s(ml.mtxt[ml.msize++], strlen(buff) + 1, buff); // ������
	}
	In::element split(In::element el, In::IN in) // ����������
	{
		In::element ml;
		ml.msize = 0;
		ml.mtxt = new char*[MAX_EL];
		int i(0), temp(0);
		char* buff = new char[MAX_EL];
		char current, next;
		bool r = true;
		while (el.txt[i] != 0x00)
		{
			bool I = true;
			current = el.txt[i]; next = el.txt[i + 1];
			if (in.code[current] == in.R)
			{
				if (r == false) { // ����� ��������� " �� 2-�� ���, �� ���������� ����� �� " �� " � ���������
					add(buff, temp, ml, current);
					I = false;
				}
				r = !r;
			}
			if (r)
			{ // T - ����������� ������
				if (in.code[current] == in.T) // ���������� �����
				{
					switch (in.code[next]) // ���� ��������� ������: ���������, ������ ��� | , ��:
					{
					case in.S: case in.O: case in.P: add(buff, temp, ml, current); I = false; break; // ���������� � ���������
					}
				}
				switch (in.code[current]) // ���� ������� ��������� ��� |, ��:
				{
				case in.O: I = false; break;
				case in.S: case in.P: add(buff, temp, ml, current); I = false; break; // ���������� � ���������
				}
			}
			if (I) buff[temp++] = current; // ������ ��������
			i++;
		}
		return ml;
	}
	In::element deleterp(In::IN in) // �������� ������ ��������
	{
		In::element el; // ������������ ���������
		int i(0), n(-1);
		el.size = -1;
		el.txt = new char[in.size];
		bool r = true, IF_DEL_SPACE;
		char current, next, prev;
		for (int i(0); i <= in.size; i++)
		{
			IF_DEL_SPACE = false;
			current = in.text[i]; next = in.text[i + 1]; // ��������� current - ������� ������, next - ���������
			in.code[current] == in.R ? r = !r : r;  // R - ' ; ����� r == true, r = !true => r = false ; ���������� �������� �� ������ ������� � ' '
			if (r)
			{
				switch (in.code[current]) // ��������, ����� �� ������ ������
				{
				case in.O:  // O - ������
					switch (in.code[next])
					{
					case in.O:							   // ������� �� ��������� ������
					case in.S:	IF_DEL_SPACE = true; break;// ������ ������ ����� �����������
					}											// S - ����������, P - | (������ ��������� ������). 							        	 
					if (in.code[el.txt[el.size]] == in.S || el.size < 0 || in.code[el.txt[el.size]] == in.P) IF_DEL_SPACE = true; //������ ������ ����� ���������� || ������ ������ � ������ ������ ������ || ������ ������ � ������ ����� (�� �������� ��� 1-��)
					break;
				case in.P: if (in.code[next] == in.P)		IF_DEL_SPACE = true;	// ������ ������ |
					break;
				}
			}
			if (!IF_DEL_SPACE) el.txt[++el.size] = current;  // ���������� ������ � ���������
		}
		el.txt[++el.size] = 0x00;

		return el;
	}
	bool checkExpression(FST::FSA fsa, LT::Entry &LT_struct, IT::IdTable &idtable, IT::Entry &IT_struct, In::element ml, int i, std::stack<int>&PIN, Error::ERRORS& table)
	{
		fsa.setFSA(ml.mtxt[i]);
		bool rc = FST::execute(fsa.fst);
		bool check_int = false;
		if (rc)
		{
			LT_struct.lexema = fsa.lexema; // ������ ������������ �������
			LT_struct.pn = fsa.PN;
			if (fsa.lexema == LEX_FUNCTION) idtable.f_parm = true;
			if (fsa.lexema == LEX_RIGHTTHESIS) idtable.f_parm = false;
			if (fsa.lexema == LEX_IDENTIFIER) // ���� �������������:
			{
				int k = -1; // if new id
				if (PIN.empty())
				{
					k = idtable.getidnum(ml.mtxt[i]); // ���� ������ <=> ����� ����� �� ����������� ����������� 2-�� ���
				}
				if (k >= 0)
				{ // ���� ����� �� ���
					LT_struct.idxTI = k; // ���������� ������ �� ��
					idtable.if_double_i = true; // ���� ������ true, ����� �� ��������� � ��
					if (strcmp(ml.mtxt[i + 1], "=") == 0)
					{
						for (int i = 0; i < idtable.size; i++)
						{
							if (strcmp(idtable.table[i].id_buf, fsa.fst.string) == 0 && idtable.table[i].idtype == IT::F)
							{
								table.pushError(104, LT_struct.sn); // ������ 104
								break;
							}
						}
					}
				}
				else if (!PIN.empty()) // ���. �������� ����� �������� ������ �����������
				{ // ���� ������ �� �� ����
					while (PIN.size())
					{
						switch (PIN.top()) // ������� ������� ������
						{
						case LT::PIN_I: IT_struct.iddatatype = IT::INT; IT_struct.value.vint = TI_INT_DEFAULT; break;
						case LT::PIN_S: IT_struct.iddatatype = IT::STR; IT_struct.value.vstr.len = TI_STR_DEFAULT; break;
						case LT::PIN_F: IT_struct.idtype = IT::F; IT_struct.is_to = true; break;
						case LT::PIN_M: /*idtable.f_main = true;*/ break;
						}
						PIN.pop(); // ���������� �� ����� 
					}
					IT_struct.idxfirstLE = LT_struct.sn; // ���������� � �� ������ ������ ������� �������������� � ��
					LT_struct.idxTI = idtable.size; // ������� ������ �� == ����������� ������, �� ���� ����� ����� ��������� �� �� ��
					if (IT_struct.idtype == IT::F) idtable.f_main = false; // for main function
					if (IT_struct.idtype == IT::DEFT && !idtable.f_main) // ��� �� ������ <=> ����� ���������� 
					{
						int k = idtable.size;
						while (idtable.table[k].idtype != IT::F) k--;
						strcpy(IT_struct.id, idtable.table[k].id);
						if (idtable.f_parm)
						{
							IT_struct.idtype = IT::P;
							IT_struct.is_to = true;
						}
						else
						{
							IT_struct.idtype = IT::V;
							if (!strcmp(ml.mtxt[i - 2], "declare")) IT_struct.is_to = true;
						}
					}

					if (idtable.f_main)
					{
						strcpy(IT_struct.id, "main");
						IT_struct.idtype = IT::V;
						if (!strcmp(ml.mtxt[i - 2], "declare")) IT_struct.is_to = true;
					}
					strcpy(IT_struct.id_buf, ml.mtxt[i]);
					strcat(IT_struct.id, ml.mtxt[i]);
					if (IT_struct.id_buf[ID_MAXSIZE - 1] != '\0')
					{
						IT_struct.iddatatype = IT::DEFD;
						table.pushError(102, LT_struct.sn); // ������ 102
					}
					if (IT_struct.iddatatype == IT::DEFD) rc = false;
				}
			}
			else
			{
				if (fsa.lexema == LEX_LITERAL) // ���� �������
				{
					IT_struct.idtype = IT::L;
					IT_struct.is_to = true;
					if (fsa.CID == LT::LT_INT)
					{
						IT_struct.iddatatype = IT::INT;
						IT_struct.value.vint = atoi(ml.mtxt[i]); // ���������� �������� �������� � ���������
					}
					else if (fsa.CID == LT::LT_STR)
					{
						IT_struct.iddatatype = IT::STR;
						IT_struct.value.vstr.len = strlen(ml.mtxt[i]) - 2; // ���������� ����� ������ ��� " "
						int y(0);
						for (y; y < IT_struct.value.vstr.len; y++) // ���������� ����� ��� " "
							IT_struct.value.vstr.str[y] = ml.mtxt[i][y + 1];
						IT_struct.value.vstr.str[y] = '\0';
					}
					if (IT_struct.value.vstr.len>255) table.pushError(105, LT_struct.sn); // ������ 105
					LT_struct.idxTI = idtable.size;
					IT_struct.idxfirstLE = LT_struct.sn;
					char*c = new char[ID_MAXSIZE];
					memset(IT_struct.id, NULL, ID_MAXSIZE);
					strcpy(IT_struct.id, "L");
					strcat(IT_struct.id, _itoa(idtable.IT_num++, c, 10));
					delete[] c;
				}
				else if (fsa.lexema == LEX_MAIN)
				{
					idtable.f_main = true;
				}
				else if (fsa.CID != LT::PIN_DEF)
				{
					PIN.push(fsa.CID); // ������� � ���� 
				}
				if (fsa.lexema == LEX_LEFTBRACE && !PIN.empty()) PIN.pop();
			}
		}
		return rc;
	}
	void output_LT(Log::LOG log, LT::LexTable lextable)
	{
		bool flag_for_output = false;
		(*log.stream) << "\n ������� ������ : \n";
		for (int k = 0; k < lextable.size; k++)
		{

			if (lextable.table[k].sn != lextable.table[k - 1].sn)
			{
				*log.stream << std::endl;
				if (lextable.table[k].lexema == LEX_BRACELET) flag_for_output = false;
				lextable.table[k].sn < 10 ? (*log.stream) << "0" << lextable.table[k].sn << " : " : (*log.stream) << lextable.table[k].sn << " : ";
				if (flag_for_output) *log.stream << "\t";
				if (lextable.table[k].lexema == LEX_LEFTBRACE) flag_for_output = true;
			}
			*log.stream << lextable.table[k].lexema;
			if (lextable.table[k].lexema == 'i' || lextable.table[k].lexema == 'l') // ������������ ������� � �������
				*log.stream << "{" << lextable.table[k].idxTI << "}";
		}
	}
	void output_IT(Log::LOG log, IT::IdTable idtable)
	{
		(*log.stream) << "\n\n ������� ��������������� : \n";
		(*log.stream) << std::setw(3) << std::left << "�" << std::setw(2) << std::left << ":" << std::setw(15) << std::left << "������������� "\
			<< std::setw(15) << std::left << "��� ������" << std::setw(15) << std::left << "��� ����-��" << std::setw(15) << std::left << "��������(�.�.)"\
			<< std::setw(15) << std::left << "�����" << "��������" << std::endl;
		for (int k = 0; k < idtable.size; k++)
		{
			switch (idtable.table[k].iddatatype)
			{
			case IT::INT:
				switch (idtable.table[k].idtype)
				{
				case IT::F: (*log.stream) << std::setw(2) << std::left << k << std::setw(2) << std::left << " : " << std::setw(15) << std::left << idtable.table[k].id_buf << std::setw(15) << std::left\
					<< "int" << std::setw(15) << std::left << "F " << "������: " << std::setw(7) << std::left << idtable.table[k].idxfirstLE << std::endl;  break;

				case IT::V: (*log.stream) << std::setw(2) << std::left << k << std::setw(2) << std::left << " : " << std::setw(15) << std::left << idtable.table[k].id_buf << std::setw(15) << std::left\
					<< "int" << std::setw(15) << std::left << "V " << "������: " << std::setw(7) << std::left << idtable.table[k].idxfirstLE << std::endl;  break;

				case IT::P: (*log.stream) << std::setw(2) << std::left << k << std::setw(2) << std::left << " : " << std::setw(15) << std::left << idtable.table[k].id_buf << std::setw(15) << std::left\
					<< "int" << std::setw(15) << std::left << "P " << "������: " << std::setw(7) << std::left << idtable.table[k].idxfirstLE << std::endl; break;

				case IT::L: (*log.stream) << std::setw(2) << std::left << k << std::setw(2) << std::left << " : " << std::setw(15) << std::left << idtable.table[k].id << std::setw(15) << std::left\
					<< "int" << std::setw(15) << std::left << "L " << "������: " << std::setw(22) << std::left << idtable.table[k].idxfirstLE << idtable.table[k].value.vint << std::endl; break;
				}
				break;

			case IT::STR:
				switch (idtable.table[k].idtype)
				{
				case IT::F: (*log.stream) << std::setw(2) << std::left << k << std::setw(2) << std::left << " : " << std::setw(15) << std::left << idtable.table[k].id_buf << std::setw(15) << std::left\
					<< "str" << std::setw(15) << std::left << "F " << "������: " << std::setw(7) << std::left << idtable.table[k].idxfirstLE << std::endl;  break;

				case IT::V: (*log.stream) << std::setw(2) << std::left << k << std::setw(2) << std::left << " : " << std::setw(15) << std::left << idtable.table[k].id_buf << std::setw(15) << std::left\
					<< "str" << std::setw(15) << std::left << "V " << "������: " << std::setw(7) << std::left << idtable.table[k].idxfirstLE << std::endl;  break;

				case IT::P: (*log.stream) << std::setw(2) << std::left << k << std::setw(2) << std::left << " : " << std::setw(15) << std::left << idtable.table[k].id_buf << std::setw(15) << std::left\
					<< "str" << std::setw(15) << std::left << "P " << "������: " << std::setw(7) << std::left << idtable.table[k].idxfirstLE << std::endl;  break;

				case IT::L: (*log.stream) << std::setw(2) << std::left << k << std::setw(2) << std::left << " : " << std::setw(15) << std::left << idtable.table[k].id << std::setw(15) << std::left\
					<< "str" << std::setw(15) << std::left << "L " << "������: " << std::setw(7) << std::left << idtable.table[k].idxfirstLE << std::setw(15) << std::left << (int)idtable.table[k].value.vstr.len << idtable.table[k].value.vstr.str << std::endl;  break;
				}
				break;
			}
		}
	}
	LEX Par(In::IN in, Error::ERRORS& table, Parm::PARM parm, bool &flib, Log::LOG log)
	{
		LEX Tables;
		In::element el = deleterp(in);
		In::element ml = split(el, in);
		/*if (strcmp(ml.mtxt[0], IF_LIB) == 0)*/ flib = true;
		int i(NULL), FSA_size(i);
		LT::Entry LT_struct;
		Tables.Lextable = LT::Create(LT_MAXSIZE);
		IT::Entry IT_struct;
		Tables.Idtable = IT::Create(ARR);
		bool check = false;
		bool flag_for_main = false;
		std::stack<int>PIN;
		LT_struct.sn = 1;
		if (flib)
		{


			IT::Entry collab;
			collab.idxfirstLE = 0;
			strcpy(collab.id_buf, "square"); strcpy(collab.id, "square");
			collab.iddatatype = IT::IDDATATYPE(2); collab.idtype = IT::IDTYPE(3);
			collab.is_to = true;
			IT::Add(Tables.Idtable, collab);
			IT::Entry length;
			length.idxfirstLE = 0;
			strcpy(length.id_buf, "double"); strcpy(length.id, "double");
			length.iddatatype = IT::IDDATATYPE(1); length.idtype = IT::IDTYPE(3);
			length.is_to = true;
			IT::Add(Tables.Idtable, length);
		}
		for (int i = flib ? 2 : 0; i < ml.msize; i++)
		{
			bool flag_for_elem = false;
			Tables.Idtable.if_double_i = false;
			if (in.code[ml.mtxt[i][NULL]] == in.P) LT_struct.sn++;
			else
			{
				while (!check && FSA_size < TOTAL_KA)
				{

					if (checkExpression(FSATable[FSA_size], LT_struct, Tables.Idtable, IT_struct, ml, i, PIN, table)) // ��������� �� ���������
					{																						   // � ������� � ��������� �� � ��
						LT::Add(Tables.Lextable, LT_struct); // ������ � ��
						if (FSA_size >= IN_ID && !Tables.Idtable.if_double_i) // ������ � ��
							if (IT_struct.is_to)
							{
								IT::Add(Tables.Idtable, IT_struct);
							}
							else table.pushError(103, LT_struct.sn); // ������ 103
							check = true;
							flag_for_elem = true;
					}
					FSA_size++;
				}
				if (!flag_for_elem) table.pushError(100, LT_struct.sn); // ������ 100
			}
			check = false;
			IT_struct = IT::Entry();
			FSA_size = NULL;
		}
		LT_struct.lexema = '$';
		LT::Add(Tables.Lextable, LT_struct);
		return Tables;
	}
}
