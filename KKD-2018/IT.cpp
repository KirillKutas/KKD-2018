#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable idTable;
		idTable.maxsize = ID_MAXSIZE;
		idTable.size = 0;
		idTable.litCount = 0;
		idTable.table = new Entry[size];
		return idTable;
	}
	void Add(IdTable& idtable, Entry entry)
	{
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}
	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char* idvis)
	{
		char ident[ID_MAXSIZE];
		strncpy_s(ident, ID_MAXSIZE, id, ID_MAXSIZE - 1);
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, ident) == NULL && strcmp(idtable.table[i].idvis, idvis) == NULL)
				return i;
		}
		return -1;
	}
	int IsLiteral(IdTable &idtable, char *litrl)//��� � ���
	{
		for (int k = 0; k < idtable.litCount; k++) //�������� �� ����. ���� � �� ������ = ���-�� ���
		{
			if (!strcmp(idtable.literals[k], litrl)) //����� = �� ���� ����� ��� 
			{
				return k;
			}
		}
		return -1;
	}
	void Delete(IdTable& idtable)
	{
		delete idtable.table;
	}
}